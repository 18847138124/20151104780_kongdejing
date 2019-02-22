#include "checkdialog.h"
#include "ui_checkdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

CheckDialog::CheckDialog(const ContractItem &contract, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckDialog)
{
    ui->setupUi(this);

    ui->idEdit->setText(contract.id);   //显示合同id

    //判断合同类型
    switch(contract.type){
    case TEMPLATE_CONTRACT:{
        ui->typeEdit->setText("模板合同");
        ui->stackedWidget->setCurrentIndex(0);  //切换到显示模板合同的界面

        //显示模板类型
        switch(contract.templateType){
        case TEMPLATE_BUSINESS:
            ui->templateEdit->setText("买卖合同");
            break;
        case TEMPLATE_LEASE:
            ui->templateEdit->setText("租赁合同");
            break;
        case TEMPLATE_BORROW:
            ui->templateEdit->setText("借款合同");
            break;
        default:
            break;
        }

        QFile file(contract.fileName);
        if(file.open(QIODevice::ReadOnly)){ //打开合同文件
            QTextStream ts(&file);
            QString text = ts.readAll();    //读取文件内容
            ui->textEdit->setHtml(text);    //内容显示到界面上
        }

        break;
    }
    case PICTURE_CONTRACT:{
        ui->typeEdit->setText("合同照片");
        ui->stackedWidget->setCurrentIndex(1);  //切换到显示照片合同的界面

        ui->pix_label->setPixmap(QPixmap(contract.fileName));   //显示照片图片

        break;
    }
    default:
        break;
    }

    ui->nameEdit->setText(contract.name);   //显示申请人
    ui->phoneEdit->setText(contract.phone); //显示联系方式
    ui->dateEdit->setText(contract.date.toString("yyyy-MM-dd"));    //显示日期
}

CheckDialog::~CheckDialog()
{
    delete ui;
}

//点击审核通过
void CheckDialog::on_yesBtn_clicked()
{
    int r = QMessageBox::question(this, "合同审核", "是否确定通过该合同?");
    if(r == QMessageBox::Yes){
        done(Pass);
    }
}

//点击不通过
void CheckDialog::on_noBtn_clicked()
{
    int r = QMessageBox::question(this, "合同审核", "是否确定不通过该合同?");
    if(r == QMessageBox::Yes){
        done(NoPass);
    }
}

//点击取消
void CheckDialog::on_cancelBtn_clicked()
{
    done(Cancel);
}
