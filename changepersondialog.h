#ifndef CHANGEPERSONDIALOG_H
#define CHANGEPERSONDIALOG_H

#include <QWidget>
#include "changeperwarning.h"
#include "deletesuccessdialog.h"
#include "sqlitedatabase.h"
#include "defs.h"

namespace Ui {
class ChangePersonDialog;
}

class ChangePersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePersonDialog(QWidget *parent = nullptr);
    ~ChangePersonDialog();
    void changePersonButton();

private:
    Ui::ChangePersonDialog *ui;
    DeleteSuccessDialog* delDlg;
    SqliteDatabase* database;
    QVector<department> m_depts;
};

#endif // CHANGEPERSONDIALOG_H
