#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
}

info::~info()
{
    delete ui;
}

void info::show_info(UserInfo info)
{

}

UserInfo info::get_info()
{

}

void info::add_user()
{

}

void info::on_save_clicked()
{

}

void info::on_cle_clicked()
{
    this->close();
}
