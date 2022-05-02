#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QWidget>
#include "defs.h"
#include "sqlitedatabase.h"
#include "deletesuccessdialog.h"
#include "personmanagedialog.h"

namespace Ui {
class AddPersonDialog;
}

class AddPersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddPersonDialog(QWidget *parent = nullptr);
    AddPersonDialog(QString deptName, VOID_FUNC_TYPE cb);
    ~AddPersonDialog();
    void addPersonButton(int addDeptId, QString addDeptName);

private:
    Ui::AddPersonDialog *ui;
    SqliteDatabase* database;
    QVector<department> m_depts;
    QWidget* m_pmd;
    DeleteSuccessDialog* delDlg;
    VOID_FUNC_TYPE cb;
};

#endif // ADDPERSONDIALOG_H
