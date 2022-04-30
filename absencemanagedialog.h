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
    void confirmAdd();
    void confirmDelete();
//    void confirmAbsentButton();
//    void confirmBackButton();

private:
    Ui::AbsenceManageDialog *ui;
    QMap<int,QVector<person>> m_absPers;
    QMap<int,QVector<person>> m_workPers;
    QMap<int,QVector<person>> m_allPers;
    QVector<department> m_depts;
    SqliteDatabase* database;
    QMap<int, QString> m_state;
};

#endif // ABSENCEMANAGEDIALOG_H
