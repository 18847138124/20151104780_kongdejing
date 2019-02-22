#include "edittemplatedialog.h"
#include "ui_edittemplatedialog.h"
#include <QFile>
#include <QTextStream>
#include <QFontDialog>
#include <QColorDialog>
#include <QMessageBox>
#include "contract.h"
#include <QDir>

EditTemplateDialog::EditTemplateDialog(int templateType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTemplateDialog),
    template_type(templateType)
{
    ui->setupUi(this);

    //显示模板类型
    switch(templateType){
    case TEMPLATE_BUSINESS:
        ui->titleLabel->setText("模板编辑:买卖合同");
        break;
    case TEMPLATE_LEASE:
        ui->titleLabel->setText("模板编辑:借款合同");
        break;
    case TEMPLATE_BORROW:
        ui->titleLabel->setText("模板编辑:租赁合同");
        break;
    default:
        break;
    }

    QString fileName = QString("template/template_%1.html").arg(templateType);  //模板内容文件
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream ts(&file);
        ui->textEdit->setText(ts.readAll());    //读取模板内容并加载到编辑框中
    }

    on_textEdit_cursorPositionChanged();    //初始化格式显示
}

EditTemplateDialog::~EditTemplateDialog()
{
    delete ui;
}

//当编辑栏中光标位置改变
void EditTemplateDialog::on_textEdit_cursorPositionChanged()
{
    showFont(); //显示字体
    showColor();    //显示字体颜色

    //显示对齐方式
    switch(ui->textEdit->alignment()){
    case Qt::AlignLeft:
    case Qt::AlignJustify:
        ui->leftBtn->setChecked(true);
        break;
    case Qt::AlignCenter:
        ui->centerBtn->setChecked(true);
        break;
    case Qt::AlignRight:
        ui->rightBtn->setChecked(true);
        break;
    default:
        break;
    }
}

//显示字体
void EditTemplateDialog::showFont()
{
    ui->fontEdit->setText(ui->textEdit->currentFont().family());    //显示字体名
    ui->pointEdit->setText(QString::number(ui->textEdit->currentFont().pointSize()));   //显示字体大小
}

//显示字体颜色
void EditTemplateDialog::showColor()
{
    QColor color = ui->textEdit->textColor();
    ui->colorBtn->setStyleSheet(QString("background-color:rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue()));
}

//点击修改字体
void EditTemplateDialog::on_fontBtn_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->currentFont(), this, "字体");    //弹出字体对话框并获取选择的字体
    if(ok){
        ui->textEdit->setCurrentFont(font); //设置字体到编辑框
        showFont(); //显示字体
    }
}

//点击修改字体颜色
void EditTemplateDialog::on_colorBtn_clicked()
{
    QColor color = QColorDialog::getColor(ui->textEdit->textColor(), this, "字体颜色"); //弹出颜色对话框并获取选择的颜色
    if(color.isValid()){
        ui->textEdit->setTextColor(color);  //设置字体颜色到编辑框
        showColor();    //显示字体颜色
    }
}

//点击左对齐
void EditTemplateDialog::on_leftBtn_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);  //设置编辑框当前格式为左对齐
}

//点击中对齐
void EditTemplateDialog::on_centerBtn_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);    //设置编辑框当前格式为中对齐
}

//点击右对齐
void EditTemplateDialog::on_rightBtn_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignRight); //设置编辑框当前格式为右对齐
}

//点击保存
void EditTemplateDialog::on_saveBtn_clicked()
{
    int ret = QMessageBox::question(this, "模板编辑", "是否将编辑的内容保存到模板中?");   //询问是否保存
    if(ret == QMessageBox::Yes){
        QDir().mkpath("template/");
        QString fileName = QString("template/template_%1.html").arg(template_type); //模板内容文件
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)){
            QTextStream ts(&file);
            ts << ui->textEdit->toHtml();   //将编辑框中的内容输出到文件
            accept();
        }else{
            QMessageBox::critical(this, "模板编辑", "模板保存失败!");
        }
    }
}

//点击取消
void EditTemplateDialog::on_cancelBtn_clicked()
{
    reject();   //关闭对话框
}
