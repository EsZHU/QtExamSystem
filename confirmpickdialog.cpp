#include "confirmpickdialog.h"
#include "ui_confirmpickdialog.h"


ConfirmPickDialog::ConfirmPickDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmPickDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("确认抽取页面");
    confirm = 0;
    connect(ui->cancelButton, &QPushButton::clicked, [=](){this->close();});
    connect(ui->confirmButton, &QPushButton::clicked, [=]()mutable{confirm = 1;confirmCBF();this->close();});
}

ConfirmPickDialog::~ConfirmPickDialog()
{
    delete ui;
}

bool ConfirmPickDialog::confirmPick(std::function<void ()> func)
{
    confirmCBF = func;
}

//bool ConfirmPickDialog::confirmPick()
//{
//    int yes;
//    connect(ui->confirmButton, &QPushButton::clicked, [=]() mutable{
//        yes = 1;
//    });
//    connect(ui->cancelButton, &QPushButton::clicked, [=](){
//        this->close();
//    });
//}

//bool ConfirmPickDialog::confirmPick(std::function<void> func)
//{
//    func();
//}
