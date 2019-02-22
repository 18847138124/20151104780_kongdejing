#include "apply.h"
#include "ui_apply.h"
#include <QMessageBox>
#include <QApplication>
#include "register.h"
#include "login.h"
#include "contractapply.h"

Apply::Apply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Apply),
    is_login(false)
{
    ui->setupUi(this);

    regist = new Register(this);    //初始化用户注册界面
    connect(regist, SIGNAL(loggedIn()), SLOT(on_loginBtn_clicked()));   //绑定注册页面的登录信号,到切换到登录界面的槽
    login = new Login(this);    //初始化登录界面
    connect(login, SIGNAL(loggedIn(QString)), SLOT(loginState(QString)));   //绑定登录界面的登录信号,到登录槽
    contract_apply = new ContractApply(this);   //初始化合同申请界面

    //将各界面添加到stackedwidget中
    ui->stackedWidget->addWidget(regist);
    ui->stackedWidget->addWidget(login);
    ui->stackedWidget->addWidget(contract_apply);

    logoutState();  //切换界面为登出状态
}

Apply::~Apply()
{
    delete ui;
}

//界面切换到登出状态
void Apply::logoutState()
{
    ui->userLabel->setText("未登录");  //用户名标签显示未登录
    ui->logoutBtn->hide();  //隐藏登出按钮
    ui->loginBtn->show();   //显示登录按钮
    ui->stackedWidget->setCurrentWidget(login); //切换到登录界面

    is_login = false;   //登录状态设置为假
}

//界面切换到登录状态
void Apply::loginState(const QString &user)
{
    ui->userLabel->setText(QString("你好, %1").arg(user));    //显示用户名
    ui->loginBtn->hide();   //隐藏登录按钮
    ui->logoutBtn->show();  //显示登出按钮
    ui->stackedWidget->setCurrentWidget(contract_apply);    //设置当前界面为合同申请

    is_login = true;    //登录状态为真
}

//点击申请合同按钮
void Apply::on_applyBtn_clicked()
{
    //判断是否登录
    if(!is_login){
        //若未登录提示并切换到登录界面
        QMessageBox::information(this, "申请合同", "请先登录才能申请合同!");
        ui->stackedWidget->setCurrentWidget(login);
    }else{
        //若登录则切换到申请合同界面
        ui->stackedWidget->setCurrentWidget(contract_apply);
    }
}

//点击用户登录按钮
void Apply::on_loginBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(login); //切换到登录界面
}

//点击登出按钮
void Apply::on_logoutBtn_clicked()
{
    int r = QMessageBox::question(this, "退出登录", "是否退出登录?"); //询问是否登出
    if(r == QMessageBox::Yes)   //若选择是
        logoutState();      //登出
}

//点击注册按钮
void Apply::on_registBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(regist);    //切换到注册界面
}

//点击退出系统
void Apply::on_exitBtn_clicked()
{
    int r = QMessageBox::question(this, "退出系统", "是否退出合同管理系统?"); //询问是否退出
    if(r == QMessageBox::Yes)   //若选择是
        qApp->quit();   //退出程序
}
