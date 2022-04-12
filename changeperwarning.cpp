#include "changeperwarning.h"
#include "ui_changeperwarning.h"

ChangePerWarning::ChangePerWarning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePerWarning)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [=](){this->close();});
    this->setWindowTitle("错误提示");
}

ChangePerWarning::~ChangePerWarning()
{
    delete ui;
}
