QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    absencemanagedialog.cpp \
    addpersondialog.cpp \
    confirmhisdeletedialog.cpp \
    confirmsthdialog.cpp \
    customtabbar.cpp \
    deletesuccessdialog.cpp \
    dptmanagedialog.cpp \
    helpdialog.cpp \
    historyshow.cpp \
    main.cpp \
    mainwindownew.cpp \
    personmanagedialog.cpp \
    randomaccess.cpp \
    searchpersondialog.cpp \
    sqlitedatabase.cpp \
    stateeditdialog.cpp

HEADERS += \
    CustomTabStyle.h \
    aboutdialog.h \
    absencemanagedialog.h \
    addpersondialog.h \
    confirmhisdeletedialog.h \
    confirmsthdialog.h \
    customtabbar.h \
    defs.h \
    deletesuccessdialog.h \
    dptmanagedialog.h \
    helpdialog.h \
    historyshow.h \
    mainwindownew.h \
    personmanagedialog.h \
    randomaccess.h \
    searchpersondialog.h \
    sqlitedatabase.h \
    stateeditdialog.h

FORMS += \
    aboutdialog.ui \
    absencemanagedialog.ui \
    confirmhisdeletedialog.ui \
    confirmsthdialog.ui \
    deletesuccessdialog.ui \
    dptmanagedialog.ui \
    helpdialog.ui \
    historyshow.ui \
    mainwindownew.ui \
    personmanagedialog.ui \
    searchpersondialog.ui \
    stateeditdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/qss.qrc
