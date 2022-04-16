#include "changedptdialog.h"
#include "ui_changedptdialog.h"

ChangeDptDialog::ChangeDptDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeDptDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("改变部门名称页面");
    database = new SqliteDatabase();
    refresh();
}

ChangeDptDialog::~ChangeDptDialog()
{
    delete ui;
}

void ChangeDptDialog::refresh()
{
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        QString beforeDptName = ui->beforeNameLabel->text();
        QString afterDptName = ui->afterNameLabel->text();
        if(beforeDptName == "" || afterDptName == ""){
            ui->hintLabel->setText("您的输入不能为空！");
        } else if(database->manageChangingDept(beforeDptName, afterDptName) == 1 && beforeDptName != "" && afterDptName != ""){ // 前者存在 后者不存在 == 1
            ui->hintLabel->setText("成功修改【" + beforeDptName + "】处室为【" + afterDptName + "】");
        } else if(database->manageChangingDept(beforeDptName, afterDptName) == 0 && beforeDptName != "" && afterDptName != ""){ // 前者不存在 == 0
            ui->hintLabel->setText("【" + beforeDptName + "】不存在！修改失败");
        } else if(database->manageChangingDept(beforeDptName, afterDptName) == 2 && beforeDptName != "" && afterDptName != ""){ // 前者存在 后者存在 == 2
            ui->hintLabel->setText("【" + afterDptName + "】已存在！修改失败");
        }
    });
}
