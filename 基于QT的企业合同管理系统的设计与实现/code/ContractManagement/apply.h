#ifndef APPLY_H
#define APPLY_H

#include <QWidget>

namespace Ui {
class Apply;
}

class Register;
class Login;
class ContractApply;

//申请端界面
class Apply : public QWidget
{
    Q_OBJECT

public:
    explicit Apply(QWidget *parent = 0);
    ~Apply();

public slots:
    void logoutState(); //界面切换到登出状态
    void loginState(const QString &user);   //界面切换到登录状态

private slots:
    void on_applyBtn_clicked();

    void on_loginBtn_clicked();

    void on_logoutBtn_clicked();

    void on_registBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::Apply *ui;

    Register *regist;   //注册界面
    Login *login;   //登录界面
    ContractApply *contract_apply;  //合同申请界面

    bool is_login;  //是否登录
};

#endif // APPLY_H
