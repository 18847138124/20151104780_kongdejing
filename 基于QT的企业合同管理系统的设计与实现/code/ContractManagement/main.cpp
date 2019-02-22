#include "apply.h"
#include <QApplication>
#include "welcome.h"
#include "check.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Welcome dialog; //欢迎界面
    if(dialog.exec() == QDialog::Accepted){
        //判断对话框中选择的类型
        switch(dialog.type()){
        case Welcome::Apply:    //申请端
        {
            Apply w;
            w.show();
            return a.exec();
        }
        case Welcome::Check:    //审核端
        {
            Check w;
            w.show();
            return a.exec();
        }
        default:
            return 0;
        }
    }else{
        return 0;
    }
}
