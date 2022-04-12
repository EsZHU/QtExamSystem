#include "changepersondialog.h"
#include "ui_changepersondialog.h"

ChangePersonDialog::ChangePersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePersonDialog)
{
    ui->setupUi(this);
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){this->close();});
    this->setWindowTitle("修改人员界面");

    confirmButton();
}

ChangePersonDialog::~ChangePersonDialog()
{
    delete ui;
}

void ChangePersonDialog::confirmButton()
{
    // 您输入的改变前的信息不正确！请重新核对后重新输入！
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        // if不满足条件
        {
            ChangePerWarning* warnDlg = new ChangePerWarning();
            warnDlg->setWindowModality(Qt::ApplicationModal);
            warnDlg->show();
        }
    });
}
