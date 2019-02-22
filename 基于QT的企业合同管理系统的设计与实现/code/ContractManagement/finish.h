#ifndef FINISH_H
#define FINISH_H

#include <QWidget>
#include "contract.h"

namespace Ui {
class Finish;
}

class DataBase;

//已完成合同界面
class Finish : public QWidget
{
    Q_OBJECT

public:
    explicit Finish(QWidget *parent = 0);
    ~Finish();

    void loadFinish();  //加载已完成合同列表

private slots:
    void on_openBtn_clicked();

private:
    Ui::Finish *ui;

    DataBase *db;   //数据库操作
    QList<ContractItem> contracts;  //已完成合同列表
};

#endif // FINISH_H
