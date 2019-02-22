#-------------------------------------------------
#
# Project created by QtCreator 2018-12-05T00:26:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ContractManagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    welcome.cpp \
    apply.cpp \
    register.cpp \
    login.cpp \
    database.cpp \
    contractapply.cpp \
    check.cpp \
    contractcheck.cpp \
    finish.cpp \
    templatemanage.cpp \
    adminlogin.cpp \
    checkdialog.cpp \
    edittemplatedialog.cpp

HEADERS  += \
    welcome.h \
    apply.h \
    register.h \
    login.h \
    database.h \
    contractapply.h \
    contract.h \
    check.h \
    contractcheck.h \
    finish.h \
    templatemanage.h \
    adminlogin.h \
    checkdialog.h \
    edittemplatedialog.h

FORMS    += \
    welcome.ui \
    apply.ui \
    register.ui \
    login.ui \
    contractapply.ui \
    check.ui \
    contractcheck.ui \
    finish.ui \
    templatemanage.ui \
    adminlogin.ui \
    checkdialog.ui \
    edittemplatedialog.ui

RESOURCES += \
    res.qrc
