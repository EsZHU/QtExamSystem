#ifndef ADDDPTDIALOG_H
#define ADDDPTDIALOG_H

#include <QWidget>
#include "sqlitedatabase.h"

namespace Ui {
class AddDptDialog;
}

class AddDptDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddDptDialog(QWidget *parent = nullptr);
    ~AddDptDialog();
    void refresh();

private:
    Ui::AddDptDialog *ui;
    SqliteDatabase* database;
};

#endif // ADDDPTDIALOG_H
