#ifndef CHANGEDPTDIALOG_H
#define CHANGEDPTDIALOG_H

#include <QWidget>
#include "sqlitedatabase.h"

namespace Ui {
class ChangeDptDialog;
}

class ChangeDptDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeDptDialog(QWidget *parent = nullptr);
    ~ChangeDptDialog();
    void refresh();

private:
    Ui::ChangeDptDialog *ui;
    SqliteDatabase* database;
};

#endif // CHANGEDPTDIALOG_H
