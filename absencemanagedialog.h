#ifndef ABSENCEMANAGEDIALOG_H
#define ABSENCEMANAGEDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include "defs.h"
#include "sqlitedatabase.h"

namespace Ui {
class AbsenceManageDialog;
}

class AbsenceManageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AbsenceManageDialog(QWidget *parent = nullptr);
    ~AbsenceManageDialog();
    void getData();
    void refresh();
    void confirmAbsentButton();
    void confirmBackButton();

private:
    Ui::AbsenceManageDialog *ui;
    QMap<int,QVector<person>> m_absPers;
    QMap<int,QVector<person>> m_workPers;
    QVector<department> m_depts;
    SqliteDatabase* database;
};

#endif // ABSENCEMANAGEDIALOG_H
