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
#include "searchpersondialog.h"
#include <QComboBox>

namespace Ui {
class PersonManageDialog;
}

class PersonManageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PersonManageDialog(QWidget *parent = nullptr);
    ~PersonManageDialog();
    void newSetTableWidgetValue();
    void setTabWidgetValue();
    void getData();
    void setTableText();
    void addPersonButton();
    void deletePersonButton();
    void changePersonButton();
    void searchPersonButton();
    void submitStatePage();

private:
    Ui::PersonManageDialog *ui;
    QMap<int,QVector<person>> m_pers;
    QVector<department> m_depts;
    SqliteDatabase* database;
    QVector<QString> stateType;
    QVector<QString> tabTitleVec;
    QVector<QTableWidget*> personShowTable;
    QStringList headList;
};

#endif // PERSONMANAGEDIALOG_H
