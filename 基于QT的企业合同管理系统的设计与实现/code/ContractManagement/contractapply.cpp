#include "contractapply.h"
#include "ui_contractapply.h"
#include <QFileDialog>
#include "contract.h"
#include <QDateTime>
#include <QMessageBox>
#include <QTextStream>
#include "database.h"

ContractApply::ContractApply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContractApply)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);  //初始化为模板合同界面
    ui->typeComboBox->setCurrentIndex(3);   //初始化选择无模板
    ui->dateEdit->setDate(QDate::currentDate());    //设置当前日期

    db = DataBase::instance();  //获取数据库实例
}

ContractApply::~ContractApply()
{
    delete ui;
}

//点击模板按钮
void ContractApply::on_tempBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);  //切换到模板合同界面
}

//点击上传照片按钮
void ContractApply::on_uploadBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);  //切换到选择照片界面
}

//点击选择照片按钮
void ContractApply::on_selectBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择合同照片", QString(), "图片 (*.png *.jpg)"); //弹出文件对话框并返回已选择的文件
    if(!fileName.isEmpty()){
        ui->pathLabel->setText(fileName);   //显示文件路径

        QImage image(fileName);
        QImage new_image = image.scaled(ui->pixLabel->size(), Qt::KeepAspectRatio); //缩放照片到合适大小
        ui->pixLabel->setPixmap(QPixmap::fromImage(new_image)); //显示照片

        file_name = fileName;   //附件为照片文件
    }
}

//点击模板选择框
void ContractApply::on_typeComboBox_currentIndexChanged(int index)
{
    if(index == TEMPLATE_NONE){
        //若选择无
        ui->textEdit->clear();  //清空合同编辑栏
        ui->textEdit->setReadOnly(true);    //合同编辑栏设置为只读
    }else{
        //若选择任意模板
        ui->textEdit->setReadOnly(false);   //合同编辑栏设置为可编辑

        QFile file(QString("template/template_%1.html").arg(index));    //找到模板文件
        if(file.open(QIODevice::ReadOnly)){ //打开模板文件
            QTextStream ts(&file);
            ui->textEdit->setText(ts.readAll());    //将模板加载到合同编辑栏中
        }
    }
}

//点击重置按钮
void ContractApply::on_resetBtn_clicked()
{
    //重置界面
    ui->typeComboBox->setCurrentIndex(3);
    ui->textEdit->clear();
    ui->textEdit->setReadOnly(true);
    ui->nameEdit->clear();
    ui->phoneEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->checkBox->setChecked(false);

    ui->pathLabel->clear();
    ui->pixLabel->clear();
    ui->pixLabel->setText("合同预览");

    file_name.clear();
}

//点击申请按钮
void ContractApply::on_applyBtn_clicked()
{
    ContractItem contract;  //定义一个合同实例

    if(ui->tempBtn->isChecked()){   //若选择模板合同
        contract.type = TEMPLATE_CONTRACT;  //获取合同类型为模板合同
        contract.templateType = ui->typeComboBox->currentIndex();   //获取模板类型
        if(contract.templateType == TEMPLATE_NONE){
            //若未选择模板,提示并返回
            QMessageBox::warning(this, "申请合同", "请选择一个可用的合同模板!");
            return;
        }
        if(ui->textEdit->toPlainText().isEmpty()){
            //若合同内容输入为空,提示并返回
            QMessageBox::warning(this, "申请合同", "合同内容不能为空!");
            ui->textEdit->setFocus();
            return;
        }
    }else{
        contract.type = PICTURE_CONTRACT;   //获取合同类型为照片合同

        if(file_name.isEmpty()){
            //若附件不存在,则提示并返回
            QMessageBox::warning(this, "申请合同", "请选择一个合同照片!");
            return;
        }
    }

    contract.name = ui->nameEdit->text();   //获取申请人
    if(contract.name.isEmpty()){
        //若申请人为空,提示并返回
        QMessageBox::warning(this, "申请合同", "申请人不能为空!");
        ui->nameEdit->setFocus();
        return;
    }

    contract.phone = ui->phoneEdit->text(); //获取联系方式
    if(contract.phone.isEmpty()){
        //若联系方式为空,提示并返回
        QMessageBox::warning(this, "申请合同", "联系方式不能为空!");
        ui->phoneEdit->setFocus();
        return;
    }

    contract.date = ui->dateEdit->date();   //获取日期
    contract.needSeal = ui->checkBox->isChecked();  //获取是否需要公章

    contract.id = QDateTime::currentDateTime().toString("yyyy_MM_dd_hhmmss");   //生成合同id
    if(!QDir().mkpath(QString("apply/" + contract.id))){    //创建申请目录
        QMessageBox::warning(this, "申请合同", "合同上传失败!");
        return;
    }

    //判断合同类型
    switch(contract.type){
    case TEMPLATE_CONTRACT:{    //模板合同
        //生成合同内容附件
        QString fileName = QString("apply/") + contract.id + "/contract.html";
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this, "申请合同", "合同内容上传失败!");
            return;
        }
        QTextStream ts(&file);
        ts << ui->textEdit->toHtml();   //将合同内容写入到附件中
        file.close();

        contract.fileName = fileName;   //获取合同附件路径
        break;
    }
    case PICTURE_CONTRACT:{ //照片合同
        //生成照片附件
        QString fileName = QString("apply/%1/%2").arg(contract.id).arg(QFileInfo(file_name).fileName());
        if(!QFile::copy(file_name, fileName)){  //将选择的照片拷贝到附件处
            QMessageBox::warning(this, "申请合同", "合同照片上传失败!");
            return;
        }

        contract.fileName = fileName;   //获取附件路径
        break;
    }
    default:
        break;
    }

    if(db->apply(contract)){    //数据库操作申请合同
        QMessageBox::information(this, "申请合同", "合同申请提交成功!");
        on_resetBtn_clicked();
    }else{
        QMessageBox::warning(this, "申请合同", "合同申请提交失败!");
    }
}














