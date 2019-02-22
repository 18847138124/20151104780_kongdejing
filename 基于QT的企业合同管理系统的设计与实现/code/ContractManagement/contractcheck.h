#ifndef CONTRACTCHECK_H
#define CONTRACTCHECK_H

#include <QWidget>
#include "contract.h"

namespace Ui {
class ContractCheck;
}

class DataBase;

//合同审核界面
class ContractCheck : public QWidget
{
    Q_OBJECT

public:
    explicit ContractCheck(QWidget *parent = 0);
    ~ContractCheck();

    void loadApplyContacts();   //加载已申请的合同

private slots:
    void on_checkBtn_clicked();

private:
    void createPdf(const ContractItem &contract);   //合同附件生成pdf

    Ui::ContractCheck *ui;

    DataBase *db;   //数据库

    QList<ContractItem> contracts;  //当前已申请的合同列表
};

#endif // CONTRACTCHECK_H
