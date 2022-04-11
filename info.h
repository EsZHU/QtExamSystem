#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include "sqlitedatabase.h"
namespace Ui {
class info;
}

class info : public QDialog
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = 0);
    ~info();

    void show_info(UserInfo info);
    UserInfo get_info();
    void add_user();

private slots:
    void on_save_clicked();

    void on_cle_clicked();

private:
    Ui::info *ui;
    SqliteDatabase *m_db;
};

#endif // INFO_H
