#include "deldptdialog.h"
#include "ui_deldptdialog.h"

DelDptDialog::DelDptDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelDptDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("删除处室页面");
    database = new SqliteDatabase();
    refresh();
}

DelDptDialog::~DelDptDialog()
{
    delete ui;
}

void DelDptDialog::refresh()
{
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        QString dptDelName = ui->nameLabel->text();

        if(database->manageDelDept(dptDelName) && dptDelName != ""){ // 删除成功
            ui->hintLabel->setText("成功删除【" + dptDelName + "】处室");
        } else if(dptDelName != ""){
            ui->hintLabel->setText("【" + dptDelName + "】不存在");
        } else if (dptDelName == "") {
            ui->hintLabel->setText("您的输入不能为空！");
        }
    });
}
