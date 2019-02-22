#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include "contract.h"

//数据库操作类
class DataBase
{
private:
    DataBase();

public:
    //登录操作返回状态定义
    enum LoginState{
        LoginNoUser = 0,    //用户不存在
        LoginPasswordWrong, //密码错误
        LoginSuccess    //登录成功
    };

    static DataBase *instance();    //获取该类实例

    bool hasUser(const QString &user);  //判断是否有user用户
    void userRegister(const QString &user, const QString &psw); //用户注册
    LoginState login(const QString &user, const QString &psw);  //用户登录
    bool apply(const ContractItem &contract);   //申请合同
    QList<ContractItem> getApplyContracts() const;  //获取申请的合同列表
    void changeContractStatus(const QString &contractID, int status);   //修改合同状态
    QList<ContractItem> getContracts(int status) const; //获取某状态的合同列表

private:
    void createTables();    //建立表

    QSqlDatabase db;    //数据库
};

#endif // DATABASE_H
