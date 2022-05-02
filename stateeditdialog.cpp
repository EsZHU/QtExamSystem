#include "stateeditdialog.h"
#include "ui_stateeditdialog.h"

StateEditDialog::StateEditDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StateEditDialog)
{

    ui->setupUi(this);
    connect(ui->cancelButton, &QPushButton::clicked, [=](){
        this->close();
    });
}

StateEditDialog::~StateEditDialog()
{
    delete ui;
}

void StateEditDialog::setEditLine(QString editState)
{
    ui->lineEdit->setText(editState);
}
