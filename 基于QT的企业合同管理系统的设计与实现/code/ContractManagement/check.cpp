#include "check.h"
#include "ui_check.h"
#include "contractcheck.h"
#include "finish.h"
#include "templatemanage.h"
#include "adminlogin.h"
#include <QMessageBox>

Check::Check(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Check),
    is_login(false)
{
    ui->setupUi(this);

    contractCheck = new ContractCheck(this);    //初始化合同审核界面
    finish = new Finish(this);  //初始化已完成界面
    templateManage = new TemplateManage(this);  //初始化模板管理界面
    login = new AdminLogin(this);   //初始化登录界面
    connect(login, SIGNAL(loggedIn()), SLOT(loginState())); //绑定登录界面的登录信号到槽

    //将各界面添加到stackedwidget
    ui->stackedWidget->addWidget(contractCheck);
    ui->stackedWidget->addWidget(finish);
    ui->stackedWidget->addWidget(templateManage);
    ui->stackedWidget->addWidget(login);

    logoutState();  //设置为登出状态
}

Check::~Check()
{
    delete ui;
}

//切换界面到登录状态
void Check::loginState()
{
    ui->userLabel->setText("你好, 管理员");
    ui->loginBtn->hide();   //隐藏登录按钮
    ui->logoutBtn->show();  //显示登出按钮
    ui->stackedWidget->setCurrentWidget(contractCheck); //切换到合同申请界面

    is_login = true;    //设置状态为已登录
}

//界面切换到登出状态
void Check::logoutState()
{
    ui->userLabel->setText("未登录");
    ui->logoutBtn->hide();  //隐藏登出按钮
    ui->loginBtn->show();   //显示登录按钮
    ui->stackedWidget->setCurrentWidget(login); //切换到登录界面

    is_login = false;   //设置状态为未登录
}

//点击合同审核
void Check::on_checkBtn_clicked()
{
    //判断是否已登录
    if(!is_login){
        //若未登录则提示并切换到登录界面
        QMessageBox::information(this, "合同审核", "请先登录管理员账户才能申请合同!");
        ui->stackedWidget->setCurrentWidget(login);
    }else{
        ui->stackedWidget->setCurrentWidget(contractCheck); //切换到审核界面
        contractCheck->loadApplyContacts(); //加载所有申请的合同
    }
}

//点击已完成按钮
void Check::on_finishBtn_clicked()
{
    //判断是否已经登录
    if(!is_login){
        //若未登录则提示并切换到登录界面
        QMessageBox::information(this, "已完成合同", "请先登录管理员账户才能查看已完成合同!");
        ui->stackedWidget->setCurrentWidget(login);
    }else{
        ui->stackedWidget->setCurrentWidget(finish);    //切换到已完成界面
        finish->loadFinish();   //加载已完成合同
    }
}

//点击模板管理按钮
void Check::on_templateBtn_clicked()
{
    //判断是否已经登录
    if(!is_login){
        //若未登录则提示并切换到登录界面
        QMessageBox::information(this, "模板管理", "请先登录管理员账户才能进行模板编辑!");
        ui->stackedWidget->setCurrentWidget(login);
    }else{
        ui->stackedWidget->setCurrentWidget(templateManage);    //切换到模板管理
    }
}

//点击登录按钮
void Check::on_loginBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(login); //切换到登录界面
}

//点击登出
void Check::on_logoutBtn_clicked()
{
    int r = QMessageBox::question(this, "退出登录", "是否退出登录?"); //询问是否登出
    if(r == QMessageBox::Yes)   //若选择是
        logoutState();  //登出
}

//点击退出
void Check::on_exitBtn_clicked()
{
    int r = QMessageBox::question(this, "退出系统", "是否退出合同管理系统?"); //询问是否退出
    if(r == QMessageBox::Yes)   //若选择是
        qApp->quit();   //退出程序
}
