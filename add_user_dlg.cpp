#include "add_user_dlg.h"
#include "ui_add_user_dlg.h"

add_user_dlg::add_user_dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_user_dlg)
{

}

add_user_dlg::~add_user_dlg()
{
    delete ui;
}

void add_user_dlg::on_save_2_clicked()
{

}

void add_user_dlg::on_cle_2_clicked()
{
    this->close();
}
