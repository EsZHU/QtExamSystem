#ifndef PERSONMANAGEDIALOG_H
#define PERSONMANAGEDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include <CustomTabStyle.h>
#include <customtabbar.h>
#include "defs.h"
#include "sqlitedatabase.h"
#include "addpersondialog.h"
#include "deletepersondialog.h"
#include "changepersondialog.h"

namespace Ui {
class PersonManageDialog;
}

class PersonManageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PersonManageDialog(QWidget *parent = nullptr);
    ~PersonManageDialog();
    void setTabWidgetValue();
    void getData();
    void setTableText();
    void addPersonButton();
    void deletePersonButton();
    void changePersonButton();

private:
    Ui::PersonManageDialog *ui;
    QMap<int,QVector<person>> m_pers;
    SqliteDatabase* database;
};

#endif // PERSONMANAGEDIALOG_H
