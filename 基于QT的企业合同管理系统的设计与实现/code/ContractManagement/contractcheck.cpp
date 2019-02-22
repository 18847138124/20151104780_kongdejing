#include "contractcheck.h"
#include "ui_contractcheck.h"
#include "database.h"
#include "checkdialog.h"
#include <QPdfWriter>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QPainter>
#include <QTextDocument>
#include <QDebug>
#include <QMessageBox>

ContractCheck::ContractCheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContractCheck)
{
    ui->setupUi(this);

    db = DataBase::instance();  //获取数据库操作实例

    loadApplyContacts();    //加载所有申请的合同
}

ContractCheck::~ContractCheck()
{
    delete ui;
}

//加载申请的合同
void ContractCheck::loadApplyContacts()
{
    contracts = db->getApplyContracts();    //数据库获取所有申请的合同

    ui->table->setRowCount(contracts.size());   //设置表格行数

    //遍历获取到的合同
    for(int i = 0; i < contracts.size(); i++){
        ContractItem c = contracts.at(i);
        //在表格中显示合同的部分内容
        ui->table->setItem(i, 0, new QTableWidgetItem(c.id));   //显示合同id
        ui->table->setItem(i, 1, new QTableWidgetItem(c.name)); //显示申请人
        //显示合同类型
        QString type;
        switch(c.type){
        case TEMPLATE_CONTRACT:
            type = "模板合同";
            break;
        case PICTURE_CONTRACT:
            type = "拍照合同";
            break;
        default:
            break;
        }

        ui->table->setItem(i, 2, new QTableWidgetItem(type));

        QString seal;
        //显示是否需要公章
        if(c.needSeal)
            seal = "需要";
        else
            seal = "不需要";

        ui->table->setItem(i, 3, new QTableWidgetItem(seal));
    }
}

//点击审核按钮
void ContractCheck::on_checkBtn_clicked()
{
    QList<QTableWidgetItem *> items = ui->table->selectedItems();   //获取在表格中所有选中的合同项
    if(items.isEmpty())
        return;

    QTableWidgetItem *item = items.at(0);   //获取选中的第一项
    if(item != 0){
        int r = ui->table->row(item);   //获取选中项的行号
        if(r >= 0 && r < contracts.size()){
            ContractItem contract = contracts.at(r);    //获取选中项合同信息
            CheckDialog dialog(contract, this); //弹出审核合同对话框
            //判断对话框返回值
            switch(dialog.exec()){
            case CheckDialog::Pass:
                //若通过
                createPdf(contract);    //生成合同pdf
                db->changeContractStatus(contract.id, CONTRACT_STATUS_FINISH);  //将该合同数据修改为已完成
                QMessageBox::information(this, "合同完成", "合同审核通过并生成PDF,可在已完成合同中查看并打印!");
                loadApplyContacts();
                break;
            case CheckDialog::NoPass:
                //若未通过
                db->changeContractStatus(contract.id, CONTRACT_STATUS_NOPASS);  //将合同数据修改为未通过
                loadApplyContacts();
                break;
            case CheckDialog::Cancel:
                break;
            default:
                break;
            }
        }
    }
}

//根据合同内容生成pdf
void ContractCheck::createPdf(const ContractItem &contract)
{
    if(contract.type == TEMPLATE_CONTRACT){ //模板合同
        QFile file(contract.fileName);  //合同内容附件
        if(file.open(QIODevice::ReadOnly)){
            QTextStream ts(&file);
            QString text = ts.readAll();    //读取附件中的合同内容
            file.close();

            QDir().mkpath(QString("finish/%1").arg(contract.id));
            QPdfWriter pdfWriter(QString("finish/%1/contract.pdf").arg(contract.id));
            pdfWriter.setPageSize(QPageSize(QPageSize::A4));    //设置pdf为A4
            pdfWriter.setResolution(100);
            QSize size = pdfWriter.pageLayout().pageSize().sizePixels(100); //获取页面大小
            QPainter painter(&pdfWriter);
            QTextDocument doc;
            doc.setPageSize(size);  //设置文档大小
            doc.setHtml(text);  //设置文档内容
            doc.drawContents(&painter); //输出页面到pdf

            //加盖电子签章
            painter.drawPixmap(size.width() - 350, size.height() - 350,
                               150, 150, QPixmap(":/images/qianzhang.png"));
        }
    }else{  //照片合同
        QImage img(contract.fileName);  //附件照片

        QDir().mkpath(QString("finish/%1").arg(contract.id));
        QPdfWriter pdfWriter(QString("finish/%1/contract.pdf").arg(contract.id));
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));    //设置pdf为A4
        pdfWriter.setResolution(100);
        QPainter painter(&pdfWriter);
        QSize size = pdfWriter.pageLayout().pageSize().sizePixels(100); //获取页面大小

        painter.drawImage(0, 0, img.scaled(size.width() - 30, size.height() - 30, Qt::KeepAspectRatio));    //输出图片到pdf
        painter.drawPixmap(size.width() - 350, size.height() - 350,
                           150, 150, QPixmap(":/images/qianzhang.png"));    //加盖电子签章
    }
}













