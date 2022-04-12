#include "addpersondialog.h"
#include "ui_addpersondialog.h"

AddPersonDialog::AddPersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPersonDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("增加人员界面");
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){this->close();});
}

AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}
