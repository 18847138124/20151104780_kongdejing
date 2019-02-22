#ifndef CONTRACT_H
#define CONTRACT_H

#include <QString>
#include <QDate>

//合同类型定义
#define TEMPLATE_CONTRACT   0   //模板合同
#define PICTURE_CONTRACT     1  //照片合同

//模板类型定义
#define TEMPLATE_BUSINESS   0   //买卖
#define TEMPLATE_LEASE      1   //租赁
#define TEMPLATE_BORROW     2   //借款
#define TEMPLATE_NONE       3   //无

//合同状态定义
#define CONTRACT_STATUS_APPLY   0   //申请中
#define CONTRACT_STATUS_FINISH  1   //已完成
#define CONTRACT_STATUS_NOPASS  2   //未通过

//合同结构体
struct ContractItem {
    QString id; //合同号
    int type;   //类型
    int templateType;   //模板类型
    QString fileName;   //附件文件路径
    QString name;   //申请人
    QString phone;  //联系方式
    QDate date; //日期
    bool needSeal;  //是否需要公章
};

#endif // CONTRACT_H
