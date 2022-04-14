#ifndef DELETEPERSONDIALOG_H
#define DELETEPERSONDIALOG_H

#include <QWidget>
#include "sqlitedatabase.h"
#include "defs.h"
#include "deletesuccessdialog.h"
#include "personmanagedialog.h"

namespace Ui {
class DeletePersonDialog;
}

class DeletePersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DeletePersonDialog(QWidget *parent = nullptr);
    ~DeletePersonDialog();
    void deletePersonButton();

private:
    Ui::DeletePersonDialog *ui;
    SqliteDatabase* database = new SqliteDatabase();
    QVector<department> m_depts;
    DeleteSuccessDialog* delDlg;
};

#endif // DELETEPERSONDIALOG_H
