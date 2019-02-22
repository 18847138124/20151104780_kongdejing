#ifndef WELCOME_H
#define WELCOME_H //防止声明冲突

#include <QDialog> //对话框
//命名空间
namespace Ui {
class Welcome;
}

//欢迎页面
class Welcome : public QDialog
{
    Q_OBJECT

public:
    //客户端类型
    //枚举两种
    enum ClientType {
        Apply,  //申请端
        Check   //审核端
    };

    //QWidge *parent表示父类窗口 =0表示它的标志位
    // explicit主要用于 "修饰 "构造函数. 指明构造函数只能显示使用,目的是为了防止不必要的隐式转化.
    //类的构造函数声明
    explicit Welcome(QWidget *parent = 0);
    ~Welcome();

    ClientType type();  //当前选择的类型

//槽函数
private slots:
    void on_enterBtn_clicked();//屏幕按钮会对enterBtn响应

private:
    Ui::Welcome *ui;//图形化界面设置
};

#endif // WELCOME_H
