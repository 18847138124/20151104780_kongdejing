#include "adminlogin.h"
#include "ui_adminlogin.h"
#include <QMessageBox>

AdminLogin::AdminLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

//点击重置按钮
void AdminLogin::on_resetBtn_clicked()
{
    ui->userEdit->clear();  //清空用户名输入栏
    ui->pswEdit->clear();   //清空密码输入栏

    ui->userEdit->setFocus();   //用户名输入栏获取焦点
}

//点击登录按钮
void AdminLogin::on_loginBtn_clicked()
{
    QString user = ui->userEdit->text();    //获取用户名输入

    //若用户名为空提示并返回
    if(user.isEmpty()){
        QMessageBox::warning(this, "管理员登录", "请输入管理员账户!");
        ui->userEdit->setFocus();
        return;
    }

    QString psw = ui->pswEdit->text();  //获取输入的密码字符串

    //若密码输入为空,提示并返回
    if(psw.isEmpty()){
        QMessageBox::warning(this, "管理员登录", "请输入密码!");
        ui->pswEdit->setFocus();
        return;
    }

    //判断用户名密码
    if(user == "admin" && psw == "admin"){
        //若用户名密码正确,登录成功
        QMessageBox::information(this, "用户登录", "登录成功!");
        on_resetBtn_clicked();
        emit loggedIn();
    }else{
        QMessageBox::warning(this, "管理员登录", "管理员账户或密码错误!");
    }
}
