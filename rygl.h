#ifndef RYGL_H
#define RYGL_H

#include <QWidget>
#include "info.h"
#include "sqlitedatabase.h"
#include "add_user_dlg.h"
namespace Ui {
class rygl;
}

class rygl : public QWidget
{
    Q_OBJECT

public:
    explicit rygl(QWidget *parent = 0);
    ~rygl();
    void showtabel();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::rygl *ui;
    SqliteDatabase *m_db;
    info m_info;
    add_user_dlg m_add;

};

#endif // RYGL_H
