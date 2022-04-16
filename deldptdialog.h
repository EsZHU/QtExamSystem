#ifndef DELDPTDIALOG_H
#define DELDPTDIALOG_H

#include <QWidget>
#include "sqlitedatabase.h"

namespace Ui {
class DelDptDialog;
}

class DelDptDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DelDptDialog(QWidget *parent = nullptr);
    ~DelDptDialog();
    void refresh();

private:
    Ui::DelDptDialog *ui;
    SqliteDatabase* database;
};

#endif // DELDPTDIALOG_H
