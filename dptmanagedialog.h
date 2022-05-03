#ifndef DPTMANAGEDIALOG_H
#define DPTMANAGEDIALOG_H

#include <QWidget>
#include "sqlitedatabase.h"
#include "stateeditdialog.h"

namespace Ui {
class DptManageDialog;
}

class DptManageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DptManageDialog(QWidget *parent = nullptr);
    ~DptManageDialog();
    void refresh();
    void addDept();
    void deleteDept();
    void editDept();

private:
    Ui::DptManageDialog *ui;
    QVector<department> m_depts;
    QVector<QString> deptVec;
    SqliteDatabase* database;
    QMap<int,QVector<person>> m_allPers;
};

#endif // DPTMANAGEDIALOG_H
