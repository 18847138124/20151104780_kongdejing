#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class DataBase;

//注册界面
class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

signals:
    void loggedIn();    //点击登录信号

private slots:
    void on_resetBtn_clicked();

    void on_okBtn_clicked();

    void on_loginBtn_clicked();

private:
    Ui::Register *ui;

    DataBase *db;   //数据库
};

#endif // REGISTER_H
