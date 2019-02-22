#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QWidget>

namespace Ui {
class AdminLogin;
}

//管理员登录界面
class AdminLogin : public QWidget
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = 0);
    ~AdminLogin();

signals:
    void loggedIn();    //登录成功信号

private slots:
    void on_resetBtn_clicked();

    void on_loginBtn_clicked();

private:
    Ui::AdminLogin *ui;
};

#endif // ADMINLOGIN_H
