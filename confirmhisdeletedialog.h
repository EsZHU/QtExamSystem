#ifndef CONFIRMHISDELETEDIALOG_H
#define CONFIRMHISDELETEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <sqlitedatabase.h>
#include "deletesuccessdialog.h"

namespace Ui {
class ConfirmHisDeleteDialog;
}

class ConfirmHisDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmHisDeleteDialog(QWidget *parent = nullptr);
    ~ConfirmHisDeleteDialog();
    void confirmDlgTrue(QString scopeType);

private:
    Ui::ConfirmHisDeleteDialog *ui;
    SqliteDatabase* database = nullptr;
};

#endif // CONFIRMHISDELETEDIALOG_H
