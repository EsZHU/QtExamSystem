#ifndef PERSONMANAGEDIALOG_H
#define PERSONMANAGEDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include <CustomTabStyle.h>
#include <customtabbar.h>
#include "defs.h"
#include "sqlitedatabase.h"
#include "addpersondialog.h"
#include "searchpersondialog.h"
#include <QComboBox>
#include <QHeaderView>
#include "confirmsthdialog.h"

namespace Ui {
class PersonManageDialog;
}

class PersonManageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PersonManageDialog(QWidget *parent = nullptr);
    ~PersonManageDialog();
//    void stateManageMethod();
    void newSetTableWidgetValue();
    void setTabWidgetValue();
    void getData();
    void setTableText();
    void addPersonButton();
    void deletePersonButton();
    void changePersonButton();
    void searchPersonButton();
    void submitStatePage();

    void initWidget();
    void refreshWidget();

private:
    Ui::PersonManageDialog *ui;
    QMap<int,QVector<person>> m_pers;
    QVector<department> m_depts;
    SqliteDatabase* database;
    QVector<QString> stateType;
    QVector<QString> tabTitleVec;
    QMap<int, QTableWidget*> personShowTable;
    QStringList headList;
    QMap<int, QString> m_state;

    int getDeptId(int index);
    void selectFirstPerson(int deptId);
};

#endif // PERSONMANAGEDIALOG_H
