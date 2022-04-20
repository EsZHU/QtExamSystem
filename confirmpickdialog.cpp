#include "confirmpickdialog.h"
#include "ui_confirmpickdialog.h"


ConfirmPickDialog::ConfirmPickDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmPickDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("确认抽取页面");
    confirm = 0;
    ui->confirmLabel->setText("");
    connect(ui->cancelButton, &QPushButton::clicked, [=](){this->close();});
    connect(ui->confirmButton, &QPushButton::clicked, [=]()mutable{confirm = 1;confirmCBF();this->close();});
}

ConfirmPickDialog::~ConfirmPickDialog()
{
    delete ui;
}

bool ConfirmPickDialog::confirmPick(std::function<void ()> func, QString text)
{
    confirmCBF = func;
    ui->confirmLabel->setText("所抽考人为【" + text + "】，点击确认不可修改，您确定要抽取吗？");
}
