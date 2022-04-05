#ifndef ADD_USER_DLG_H
#define ADD_USER_DLG_H

#include <QDialog>
#include "sqlitedatabase.h"
namespace Ui {
class add_user_dlg;
}

class add_user_dlg : public QDialog
{
    Q_OBJECT

public:
    explicit add_user_dlg(QWidget *parent = 0);
    ~add_user_dlg();

private slots:
    void on_save_2_clicked();

    void on_cle_2_clicked();

private:
    Ui::add_user_dlg *ui;
    SqliteDatabase *m_db;
};

#endif // ADD_USER_DLG_H
