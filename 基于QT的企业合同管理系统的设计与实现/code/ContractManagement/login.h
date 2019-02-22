#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class DataBase;

//登录界面
class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

signals:
    void loggedIn(const QString &user); //登录成功信号

private slots:
    void on_resetBtn_clicked();

    void on_loginBtn_clicked();

private:
    Ui::Login *ui;

    DataBase *db;   //数据库
};

#endif // LOGIN_H
