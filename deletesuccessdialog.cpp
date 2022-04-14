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
}

DeleteSuccessDialog::~DeleteSuccessDialog()
{
    delete ui;
}

void DeleteSuccessDialog::showDeleteSuccess(QString scope)
{
    ui->deleteSuccessLabel->setText("恭喜您已经成功删除【" + scope + "】的历史记录");
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle("删除成功提醒");
    this->show();
}

void DeleteSuccessDialog::showManageAddSuccess(QString addName, QString deptName)
{
    ui->deleteSuccessLabel->setText("恭喜您成功添加【" + addName + "】至【" + deptName + "】部门");
    this->setWindowTitle("添加成功提醒");
}

void DeleteSuccessDialog::showManageDeleteSuccess(QString delName, QString deptName)
{
    ui->deleteSuccessLabel->setText("恭喜您成功从【" + deptName + "】删除【" + delName + "】");
    this->setWindowTitle("删除成功提醒");
}

void DeleteSuccessDialog::showManageDeleteFail(QString delName, QString deptName)
{
    ui->deleteSuccessLabel->setText("【" + deptName + "】不存在【" + delName + "】,请核对信息后重新选择");
    this->setWindowTitle("删除失败提醒");
}

void DeleteSuccessDialog::showManageChangeFail(QString delName, QString deptName)
{
    ui->deleteSuccessLabel->setText("【" + deptName + "】不存在【" + delName + "】,请核对信息后重新选择");
    this->setWindowTitle("修改失败提醒");
}

void DeleteSuccessDialog::showManageNotComplete()
{
    ui->deleteSuccessLabel->setText("您输入的信息不完整，请检查后重新输入");
    this->setWindowTitle("信息不完整提醒");
}

void DeleteSuccessDialog::showManageChangeSuccess(QString beName, QString beDept, QString afName, QString afDept)
{
    ui->deleteSuccessLabel->setText("恭喜您成功改变【"+beDept+"】的【"+beName+"】为【"+afDept+"】的【"+afName+"】");
    this->setWindowTitle("修改成功提醒");
}

void DeleteSuccessDialog::showManageSearchFail(QString searchName)
{
    ui->deleteSuccessLabel->setText("【" + searchName + "】不存在,请核对信息后重新搜索");
    this->setWindowTitle("搜索失败提醒");
}
