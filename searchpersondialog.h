#ifndef SEARCHPERSONDIALOG_H
#define SEARCHPERSONDIALOG_H

#include <QWidget>
#include "deletesuccessdialog.h"
#include "defs.h"
#include "sqlitedatabase.h"

namespace Ui {
class SearchPersonDialog;
}

class SearchPersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPersonDialog(QWidget *parent = nullptr);
    ~SearchPersonDialog();
    void searchPersonButton();

private:
    Ui::SearchPersonDialog *ui;
    DeleteSuccessDialog* delDlg;
    SqliteDatabase* database;
    QVector<department> m_depts;
};

#endif // SEARCHPERSONDIALOG_H
