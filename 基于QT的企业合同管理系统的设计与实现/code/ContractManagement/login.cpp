#include "login.h"
#include "ui_login.h"
#include "database.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    db = DataBase::instance();  //获取数据库实例
}

Login::~Login()
{
    delete ui;
}

//点击重置按钮
void Login::on_resetBtn_clicked()
{
    //重置界面
    ui->userEdit->clear();
    ui->pswEdit->clear();

    ui->userEdit->setFocus();
}

//点击登录按钮
void Login::on_loginBtn_clicked()
{
    QString user = ui->userEdit->text();    //获取输入的用户名
    if(user.isEmpty()){
        QMessageBox::warning(this, "用户登录", "请输入用户名!");
        ui->userEdit->setFocus();
        return;
    }

    QString psw = ui->pswEdit->text();  //获取输入的密码
    if(psw.isEmpty()){
        QMessageBox::warning(this, "用户登录", "请输入密码!");
        ui->pswEdit->setFocus();
        return;
    }

    DataBase::LoginState state = db->login(user, psw);  //数据库操作登录
    //判断返回值
    switch(state){
    case DataBase::LoginNoUser:
        QMessageBox::warning(this, "用户登录", "该用户名不存在!");
        ui->userEdit->setFocus();
        ui->userEdit->selectAll();
        return;
    case DataBase::LoginPasswordWrong:
        QMessageBox::warning(this, "用户登录", "密码错误!");
        ui->pswEdit->setFocus();
        ui->pswEdit->selectAll();
        return;
    case DataBase::LoginSuccess:
        QMessageBox::information(this, "用户登录", "登录成功!");
        on_resetBtn_clicked();
        emit loggedIn(user);
        break;
    default:
        return;
    }
}
















