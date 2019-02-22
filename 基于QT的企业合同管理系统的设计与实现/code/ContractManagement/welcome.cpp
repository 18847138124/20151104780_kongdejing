#include "welcome.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}

//返回当前选择的类型
Welcome::ClientType Welcome::type()
{
    if(ui->applyBtn->isChecked())
        return Apply;
    else
        return Check;
}

//点击进入按钮
void Welcome::on_enterBtn_clicked()
{
    accept();
}
