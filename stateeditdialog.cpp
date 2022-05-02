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
    connect(ui->saveButton, &QPushButton::clicked, [=](){
        this->cb(ui->lineEdit->text());

        this->close();
    });
}

StateEditDialog::StateEditDialog(QString windowTitle, QString editName, FUNC_TYPE cb): StateEditDialog()
{
    this->setWindowTitle(windowTitle);
    ui->lineEdit->setText(editName);
    this->cb = cb;
}

StateEditDialog::StateEditDialog(QString windowTitle, FUNC_TYPE cb):StateEditDialog(windowTitle, "", cb){}

StateEditDialog::~StateEditDialog()
{
    delete ui;
}

void StateEditDialog::setEditLine(QString editState)
{
    ui->lineEdit->setText(editState);
}
