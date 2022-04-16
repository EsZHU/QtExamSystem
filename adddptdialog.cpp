#include "adddptdialog.h"
#include "ui_adddptdialog.h"

AddDptDialog::AddDptDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDptDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("添加处室页面");
    refresh();
    database = new SqliteDatabase();
}

AddDptDialog::~AddDptDialog()
{
    delete ui;
}

void AddDptDialog::refresh()
{
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        QString dptChName = ui->nameLabel->text();
        if(database->manageAddDept(dptChName) && dptChName != ""){ // 添加成功
            ui->hintLabel->setText("成功添加【" + dptChName + "】处室");
        } else if(dptChName != ""){
            ui->hintLabel->setText("【" + dptChName + "】已经存在");
        } else if (dptChName == "") {
            ui->hintLabel->setText("您的输入不能为空！");
        }
    });
}
