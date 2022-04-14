#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QWidget>
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
    explicit AddPersonDialog(QWidget* pmd, QWidget *parent = nullptr);
    ~AddPersonDialog();
    void addPersonButton();

private:
    Ui::AddPersonDialog *ui;
    SqliteDatabase* database;
    QVector<department> m_depts;
    QWidget* m_pmd;
};

#endif // ADDPERSONDIALOG_H
