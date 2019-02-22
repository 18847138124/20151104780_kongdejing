#ifndef CHECKDIALOG_H
#define CHECKDIALOG_H

#include <QDialog>
#include "contract.h"

namespace Ui {
class CheckDialog;
}

//合同审核对话框
class CheckDialog : public QDialog
{
    Q_OBJECT

public:
    //审核对话框返回状态
    enum ResultCode{
        Pass = Accepted,    //通过
        NoPass = 10,    //不通过
        Cancel = Rejected   //取消
    };

    explicit CheckDialog(const ContractItem &contract, QWidget *parent = 0);
    ~CheckDialog();

private slots:
    void on_yesBtn_clicked();

    void on_noBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::CheckDialog *ui;
};

#endif // CHECKDIALOG_H
