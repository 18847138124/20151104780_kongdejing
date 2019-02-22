#include "finish.h"
#include "ui_finish.h"
#include "database.h"
#include "contract.h"
#include <QDesktopServices>
#include <QUrl>

Finish::Finish(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Finish)
{
    ui->setupUi(this);

    db = DataBase::instance();  //获取数据库操作实例
}

Finish::~Finish()
{
    delete ui;
}

//加载已完成合同列表
void Finish::loadFinish()
{
    contracts = db->getContracts(CONTRACT_STATUS_FINISH);   //获取已完成合同列表

    ui->table->setRowCount(contracts.size());   //设置表格行数
    //遍历已完成合同列表,反向显示到表格中
    for(int i = 0; i < contracts.size(); i++){
        int row = contracts.size() - 1 - i;
        ContractItem c = contracts.at(i);
        ui->table->setItem(row, 0, new QTableWidgetItem(c.id)); //显示合同id
        ui->table->setItem(row, 1, new QTableWidgetItem(c.name));   //显示申请人
        ui->table->setItem(row, 2, new QTableWidgetItem(c.phone));  //显示联系方式
        QString type;
        //显示合同类型
        if(c.type == TEMPLATE_CONTRACT){
            switch(c.templateType){
            case TEMPLATE_BUSINESS:
                type = "买卖合同";
                break;
            case TEMPLATE_LEASE:
                type = "租赁合同";
                break;
            case TEMPLATE_BORROW:
                type = "借款合同";
                break;
            default:
                break;
            }
        }else
            type = "合同照片";
        ui->table->setItem(row, 3, new QTableWidgetItem(type));
        ui->table->setItem(row, 4, new QTableWidgetItem(c.date.toString("yyyy-MM-dd")));    //显示日期
    }
}

//点击查看合同按钮
void Finish::on_openBtn_clicked()
{
    QList<QTableWidgetItem *> items = ui->table->selectedItems();   //获取已选中的表格项
    if(items.isEmpty())
        return;

    QTableWidgetItem *item = items.at(0);   //获取第一项
    if(item != 0){
        int r = contracts.size() - ui->table->row(item) - 1;    //找到该项的索引
        if(r >= 0 && r < contracts.size()){
            ContractItem contract = contracts.at(r);    //获取该项合同内容
            QString fileName = QString("finish/%1/contract.pdf").arg(contract.id);  //找到pdf路径
            QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));   //用系统默认软件打开pdf
        }
    }
}




















