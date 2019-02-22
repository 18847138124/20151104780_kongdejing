#ifndef CHECK_H
#define CHECK_H

#include <QWidget>

namespace Ui {
class Check;
}

class ContractCheck;
class Finish;
class TemplateManage;
class AdminLogin;

//审核端界面
class Check : public QWidget
{
    Q_OBJECT

public:
    explicit Check(QWidget *parent = 0);
    ~Check();

private slots:
    void loginState();  //界面切换到登录状态
    void logoutState(); //界面切换到登出状态

    void on_checkBtn_clicked();

    void on_finishBtn_clicked();

    void on_templateBtn_clicked();

    void on_loginBtn_clicked();

    void on_logoutBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::Check *ui;

    ContractCheck *contractCheck;   //合同审核界面
    Finish *finish; //已完成合同界面
    TemplateManage *templateManage; //模板管理界面
    AdminLogin *login;  //登录界面

    bool is_login;  //是否已登录
};

#endif // CHECK_H
