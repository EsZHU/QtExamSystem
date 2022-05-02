QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    absencemanagedialog.cpp \
    addpersondialog.cpp \
    changedptdialog.cpp \
    changepersondialog.cpp \
    changeperwarning.cpp \
    confirmhisdeletedialog.cpp \
    confirmpickdialog.cpp \
    confirmsthdialog.cpp \
    customtabbar.cpp \
    deletepersondialog.cpp \
    deletesuccessdialog.cpp \
    dptmanagedialog.cpp \
    eachrow.cpp \
    historyshow.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindownew.cpp \
    personmanagedialog.cpp \
    pickresultdiagram.cpp \
    randomaccess.cpp \
    searchpersondialog.cpp \
    singlerow.cpp \
    sqlitedatabase.cpp \
    stackedwidgetdialog.cpp \
    stateeditdialog.cpp

HEADERS += \
    CustomTabStyle.h \
    absencemanagedialog.h \
    addpersondialog.h \
    changedptdialog.h \
    changepersondialog.h \
    changeperwarning.h \
    confirmhisdeletedialog.h \
    confirmpickdialog.h \
    confirmsthdialog.h \
    customtabbar.h \
    defs.h \
    deletepersondialog.h \
    deletesuccessdialog.h \
    dptmanagedialog.h \
    eachrow.h \
    historyshow.h \
    mainwindow.h \
    mainwindownew.h \
    personmanagedialog.h \
    pickresultdiagram.h \
    randomaccess.h \
    searchpersondialog.h \
    singlerow.h \
    sqlitedatabase.h \
    stackedwidgetdialog.h \
    stateeditdialog.h

FORMS += \
    absencemanagedialog.ui \
    addpersondialog.ui \
    changedptdialog.ui \
    changepersondialog.ui \
    changeperwarning.ui \
    confirmhisdeletedialog.ui \
    confirmpickdialog.ui \
    confirmsthdialog.ui \
    deletepersondialog.ui \
    deletesuccessdialog.ui \
    dptmanagedialog.ui \
    historyshow.ui \
    mainwindow.ui \
    mainwindownew.ui \
    personmanagedialog.ui \
    pickresultdiagram.ui \
    searchpersondialog.ui \
    singlerow.ui \
    stackedwidgetdialog.ui \
    stateeditdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/qss.qrc
