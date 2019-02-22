#include "templatemanage.h"
#include "ui_templatemanage.h"
#include "contract.h"
#include <QFile>
#include <QTextStream>
#include "edittemplatedialog.h"

TemplateManage::TemplateManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateManage)
{
    ui->setupUi(this);

    ui->typeComboBox->setCurrentIndex(TEMPLATE_NONE);   //初始化为选择无模板
}

TemplateManage::~TemplateManage()
{
    delete ui;
}

//加载模内容
void TemplateManage::loadText()
{
    on_typeComboBox_currentIndexChanged(ui->typeComboBox->currentIndex());
}

//下拉框选择改变
void TemplateManage::on_typeComboBox_currentIndexChanged(int index)
{
    if(index == TEMPLATE_NONE){ //选择无模板
        ui->textEdit->clear();  //清空内容显示框
    }else{
        //选择任意模板
        QString fileName = QString("template/template_%1.html").arg(index); //找到模板内容文件
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)){ //打开文件
            QTextStream ts(&file);
            ui->textEdit->setHtml(ts.readAll());    //读取内容
        }else{
            //未找到则清空内容
            ui->textEdit->clear();
        }
    }
}

//点击编辑模板按钮
void TemplateManage::on_pushButton_clicked()
{
    int index = ui->typeComboBox->currentIndex();   //获取当前模板
    if(index != TEMPLATE_NONE){ //若不是无模板
        EditTemplateDialog dialog(index, this); //弹出编辑模板对话框
        if(dialog.exec() == QDialog::Accepted){ //编辑结束
            loadText();     //加载内容
        }
    }
}




