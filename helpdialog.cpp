#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
