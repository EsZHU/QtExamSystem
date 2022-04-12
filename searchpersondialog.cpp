#include "searchpersondialog.h"
#include "ui_searchpersondialog.h"

SearchPersonDialog::SearchPersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPersonDialog)
{
    ui->setupUi(this);
}

SearchPersonDialog::~SearchPersonDialog()
{
    delete ui;
}
