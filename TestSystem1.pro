QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addpersondialog.cpp \
    changepersondialog.cpp \
    changeperwarning.cpp \
    confirmhisdeletedialog.cpp \
    customtabbar.cpp \
    deletepersondialog.cpp \
    deletesuccessdialog.cpp \
    eachrow.cpp \
    historyshow.cpp \
    main.cpp \
    mainwindow.cpp \
    personmanagedialog.cpp \
    pickresultdiagram.cpp \
    randomaccess.cpp \
    searchpersondialog.cpp \
    singlerow.cpp \
    sqlitedatabase.cpp \
    rygl.cpp \
    info.cpp

HEADERS += \
    CustomTabStyle.h \
    addpersondialog.h \
    changepersondialog.h \
    changeperwarning.h \
    confirmhisdeletedialog.h \
    customtabbar.h \
    defs.h \
    deletepersondialog.h \
    deletesuccessdialog.h \
    eachrow.h \
    historyshow.h \
    mainwindow.h \
    personmanagedialog.h \
    pickresultdiagram.h \
    randomaccess.h \
    searchpersondialog.h \
    singlerow.h \
    sqlitedatabase.h \
    rygl.h \
    info.h

FORMS += \
    addpersondialog.ui \
    changepersondialog.ui \
    changeperwarning.ui \
    confirmhisdeletedialog.ui \
    deletepersondialog.ui \
    deletesuccessdialog.ui \
    historyshow.ui \
    mainwindow.ui \
    personmanagedialog.ui \
    pickresultdiagram.ui \
    searchpersondialog.ui \
    singlerow.ui \
    rygl.ui \
    info.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/qss.qrc
