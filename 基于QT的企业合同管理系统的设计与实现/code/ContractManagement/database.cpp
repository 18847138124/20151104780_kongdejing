#include "database.h"
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

static const QString sc_dbName = "contract.db"; //数据库文件名

DataBase::DataBase()
{
    bool create = !QFile::exists(sc_dbName);    //判断文件是否存在

    db = QSqlDatabase::addDatabase("QSQLITE");  //加载sqlite驱动
    db.setDatabaseName(sc_dbName);  //设置数据库名
    if(!db.open()){ //打开数据库
        QMessageBox::critical(0, "database", "数据库打开失败");
        exit(2);
    }

    if(create)
        createTables(); //若第一次建立,建表
}

DataBase *DataBase::instance()
{
    static DataBase instance;
    return &instance;
}

//是否包含用户user
bool DataBase::hasUser(const QString &user)
{
    QSqlQuery query;

    //查询users表中是否存在user为指定用户名的项
    query.prepare("select * from users where user=:user");
    query.bindValue(":user", user);
    query.exec();

    if(query.next())
        return true;
    else
        return false;
}

//用户注册
void DataBase::userRegister(const QString &user, const QString &psw)
{
    //将用户名和密码写入到数据库的users表中
    QSqlQuery query;
    query.prepare("insert into users values(:user, :psw)");
    query.bindValue(":user", user);
    query.bindValue(":psw", psw);
    query.exec();
}

//用户登录
DataBase::LoginState DataBase::login(const QString &user, const QString &psw)
{
    QSqlQuery query;

    //查询users表中user为用户名的项
    query.prepare("select * from users where user=:user");
    query.bindValue(":user", user);
    query.exec();

    if(query.next()){
        //若存在
        QString password = query.value("password").toString();  //获取密码
        if(psw != password) //比较密码
            return LoginPasswordWrong;
        else
            return LoginSuccess;
    }else   //不存在
        return LoginNoUser;
}

//合同申请
bool DataBase::apply(const ContractItem &contract)
{
    //将合同内容写入到数据库的apply表中
    QSqlQuery query;
    query.prepare("insert into apply values(:id, :type, :template, :file, :name, :phone, :date, :seal, :status)");
    query.bindValue(":id", contract.id);
    query.bindValue(":type", contract.type);
    query.bindValue(":template", contract.templateType);
    query.bindValue(":file", contract.fileName);
    query.bindValue(":name", contract.name);
    query.bindValue(":phone", contract.phone);
    query.bindValue(":date", contract.date);
    query.bindValue(":seal", contract.needSeal);
    query.bindValue(":status", CONTRACT_STATUS_APPLY);

    return query.exec();
}

//获取申请的合同列表
QList<ContractItem> DataBase::getApplyContracts() const
{
    //查询数据库中apply表中status为已申请状态的项
    QSqlQuery query;
    query.prepare("select * from apply where status=:status");
    query.bindValue(":status", CONTRACT_STATUS_APPLY);
    query.exec();

    //逐条读取数据库项并赋值到列表中
    QList<ContractItem> contracts;
    while(query.next()){
        ContractItem contract;

        contract.id = query.value(0).toString();
        contract.type = query.value(1).toInt();
        contract.templateType = query.value(2).toInt();
        contract.fileName = query.value(3).toString();
        contract.name = query.value(4).toString();
        contract.phone = query.value(5).toString();
        contract.date = query.value(6).toDate();
        contract.needSeal = query.value(7).toBool();

        contracts.append(contract);
    }

    return contracts;
}

//修改合同为指定状态
void DataBase::changeContractStatus(const QString &contractID, int status)
{
    QSqlQuery query;
    query.prepare("update apply set status=:status where id=:id");
    query.bindValue(":status", status);
    query.bindValue(":id", contractID);
    query.exec();
}

//获取指定状态的合同列表
QList<ContractItem> DataBase::getContracts(int status) const
{
    QSqlQuery query;
    query.prepare("select * from apply where status=:status");
    query.bindValue(":status", status);
    query.exec();

    QList<ContractItem> contracts;
    while(query.next()){
        ContractItem contract;

        contract.id = query.value(0).toString();
        contract.type = query.value(1).toInt();
        contract.templateType = query.value(2).toInt();
        contract.fileName = query.value(3).toString();
        contract.name = query.value(4).toString();
        contract.phone = query.value(5).toString();
        contract.date = query.value(6).toDate();
        contract.needSeal = query.value(7).toBool();

        contracts.append(contract);
    }

    return contracts;
}

//建表
void DataBase::createTables()
{
    QSqlQuery query;

    //建立users表,存储所有用户
    query.exec("create table users(user varchar(21) primary key, "
               "password varchar(21) not null)");
    if(!query.isActive()){
        QString str = QString("数据库表users创建失败!") + "\n" + query.lastError().text();
        QMessageBox::critical(0, "database", str);
    }

    //建立apply表存储所有合同
    query.exec("create table apply(id varchar(25) primary key, "
               "type integer not null, "
               "template integer not null, "
               "file nvarchar(128) not null, "
               "name nvarchar(128) not null, "
               "phone nvarchar(128) not null, "
               "date date not null, "
               "seal bool not null, "
               "status integer not null)");
    if(!query.isActive()){
        QString str = QString("数据库表apply创建失败!") + "\n" + query.lastError().text();
        QMessageBox::critical(0, "database", str);
    }
}











