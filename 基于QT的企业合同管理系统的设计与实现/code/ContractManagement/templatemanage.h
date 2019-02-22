#ifndef TEMPLATEMANAGE_H
#define TEMPLATEMANAGE_H

#include <QWidget>

namespace Ui {
class TemplateManage;
}

//模板管理界面
class TemplateManage : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateManage(QWidget *parent = 0);
    ~TemplateManage();

    void loadText();    //加载模板内容

private slots:
    void on_typeComboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::TemplateManage *ui;
};

#endif // TEMPLATEMANAGE_H
