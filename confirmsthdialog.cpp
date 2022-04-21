#include "confirmsthdialog.h"
#include "ui_confirmsthdialog.h"

ConfirmSthDialog::ConfirmSthDialog(std::function<void ()> cb, QWidget *parent) :
    QWidget(parent), cbf(cb),
    ui(new Ui::ConfirmSthDialog)
{
    ui->setupUi(this);
    connect(ui->confirmButton, &QPushButton::clicked, [=](){
        cbf();
        this->close();
    });
    connect(ui->cancelButton, &QPushButton::clicked, [=](){this->close();});
}

ConfirmSthDialog::~ConfirmSthDialog()
{
    delete ui;
}

void ConfirmSthDialog::setLabelText(QString labelText)
{
    ui->hintLabel->setText(labelText);
}
