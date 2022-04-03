#include "labelplus.h"
#include "ui_labelplus.h"

LabelPlus::LabelPlus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelPlus)
{
    ui->setupUi(this);
}

LabelPlus::~LabelPlus()
{
    delete ui;
}

void LabelPlus::setLabelText(QString strKey, QString strValue)
{
    ui->labelKey->setText(strKey);
    ui->labelValue->setText(strValue);
}
