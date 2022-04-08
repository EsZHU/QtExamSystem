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
    hisDeleteDialogInit();
}

ConfirmHisDeleteDialog::~ConfirmHisDeleteDialog()
{
    delete ui;
}

void ConfirmHisDeleteDialog::hisDeleteDialogInit()
{
    ui->buttonBox->button(QDialogButtonBox::Yes)->setText("确认删除");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消删除");
}
