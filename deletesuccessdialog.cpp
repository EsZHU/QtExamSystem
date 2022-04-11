#include "deletesuccessdialog.h"
#include "ui_deletesuccessdialog.h"

DeleteSuccessDialog::DeleteSuccessDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteSuccessDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        this->close();

    });
    this->setWindowTitle("删除成功提醒");
}

DeleteSuccessDialog::~DeleteSuccessDialog()
{
    delete ui;
}

void DeleteSuccessDialog::showDeleteSuccess(QString scope)
{
    ui->deleteSuccessLabel->setText("恭喜您已经成功删除【" + scope + "】的历史记录");
    this->setWindowModality(Qt::ApplicationModal);
    this->show();
}
