#ifndef EDITTEMPLATEDIALOG_H
#define EDITTEMPLATEDIALOG_H

#include <QDialog>

namespace Ui {
class EditTemplateDialog;
}

//模板编辑对话框
class EditTemplateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTemplateDialog(int templateType, QWidget *parent = 0);
    ~EditTemplateDialog();

private slots:
    void on_textEdit_cursorPositionChanged();

    void on_fontBtn_clicked();

    void on_colorBtn_clicked();

    void on_leftBtn_clicked();

    void on_centerBtn_clicked();

    void on_rightBtn_clicked();

    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    void showFont();    //显示字体
    void showColor();   //显示字体颜色

    Ui::EditTemplateDialog *ui;

    int template_type;  //模板类型
};

#endif // EDITTEMPLATEDIALOG_H
