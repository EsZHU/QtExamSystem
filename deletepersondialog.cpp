#include "deletepersondialog.h"
#include "ui_deletepersondialog.h"

DeletePersonDialog::DeletePersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeletePersonDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("删除人员界面");
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){this->close();});
}

DeletePersonDialog::~DeletePersonDialog()
{
    delete ui;
}
