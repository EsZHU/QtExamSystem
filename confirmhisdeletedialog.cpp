#include "confirmhisdeletedialog.h"
#include "ui_confirmhisdeletedialog.h"

ConfirmHisDeleteDialog::ConfirmHisDeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmHisDeleteDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("您确认要删除吗？");
//    ui->label_3->setTextInteractionFlags(Qt::TextSelectableByMouse); // 可复制
    ui->confirmEdit->setPlaceholderText("我确定要删除指定范围内的历史记录");
}

ConfirmHisDeleteDialog::~ConfirmHisDeleteDialog()
{
    delete ui;
}
