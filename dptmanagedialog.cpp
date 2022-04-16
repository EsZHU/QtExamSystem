#include "dptmanagedialog.h"
#include "ui_dptmanagedialog.h"

DptManageDialog::DptManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DptManageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("部门管理页面");
    refresh();
}

DptManageDialog::~DptManageDialog()
{
    delete ui;
}

void DptManageDialog::refresh()
{
//    addDptDialog = new AddDptDialog(ui->dptWidget);

    connect(ui->addDptButton, &QPushButton::clicked, [=](){
        addDptDialog = new AddDptDialog();
        addDptDialog->setWindowModality(Qt::ApplicationModal);
        addDptDialog->show();
    });

    connect(ui->deleteDptButton, &QPushButton::clicked, [=](){
        delDptDialog = new DelDptDialog();
        delDptDialog->setWindowModality(Qt::ApplicationModal);
        delDptDialog->show();
    });

    connect(ui->changeDptButton, &QPushButton::clicked, [=](){
        changeDptDialog = new ChangeDptDialog();
        changeDptDialog->setWindowModality(Qt::ApplicationModal);
        changeDptDialog->show();
    });
}
