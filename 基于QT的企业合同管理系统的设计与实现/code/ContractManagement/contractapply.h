#ifndef CONTRACTAPPLY_H
#define CONTRACTAPPLY_H

#include <QWidget>

namespace Ui {
class ContractApply;
}

class DataBase;

//合同申请界面
class ContractApply : public QWidget
{
    Q_OBJECT

public:
    explicit ContractApply(QWidget *parent = 0);
    ~ContractApply();

private slots:
    void on_tempBtn_clicked();

    void on_uploadBtn_clicked();

    void on_selectBtn_clicked();

    void on_typeComboBox_currentIndexChanged(int index);

    void on_resetBtn_clicked();

    void on_applyBtn_clicked();

private:
    Ui::ContractApply *ui;

    DataBase *db;   //数据库指针
    QString file_name;  //附件文件路径
};

#endif // CONTRACTAPPLY_H
