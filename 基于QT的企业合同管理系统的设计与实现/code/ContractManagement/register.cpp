#include "register.h"
#include "ui_register.h"
#include "database.h"
#include <QMessageBox>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    db = DataBase::instance();  //获取数据库实例
}

Register::~Register()
{
    delete ui;
}

//点击重置按钮
void Register::on_resetBtn_clicked()
{
    //重置界面
    ui->userEdit->clear();
    ui->pswEdit->clear();
    ui->confirmPswEdit->clear();

    ui->userEdit->setFocus();
}

//点击注册按钮
void Register::on_okBtn_clicked()
{
    QString user = ui->userEdit->text();    //获取输入的用户名
    if(user.isEmpty()){
        QMessageBox::warning(this, "用户注册", "请输入用户名!");
        ui->userEdit->setFocus();
        return;
    }

    QString psw = ui->pswEdit->text();  //获取输入的密码
    if(psw.isEmpty()){
        QMessageBox::warning(this, "用户注册", "密码不能为空!");
        ui->pswEdit->setFocus();
        return;
    }

    QString confirm = ui->confirmPswEdit->text();   //获取输入的确认密码
    if(psw != confirm){
        QMessageBox::warning(this, "用户注册", "两次密码输入不一致!");
        ui->confirmPswEdit->setFocus();
        ui->confirmPswEdit->selectAll();
        return;
    }

    if(db->hasUser(user)){  //判断用户是否存在
        QMessageBox::warning(this, "用户注册", "用户名已存在!");
        ui->userEdit->setFocus();
        ui->userEdit->selectAll();
        return;
    }

    db->userRegister(user, psw);    //数据库操作注册用户
    QMessageBox::information(this, "用户注册", "用户注册成功!");

    on_resetBtn_clicked();
}

//点击登录按钮
void Register::on_loginBtn_clicked()
{
    emit loggedIn();
}








