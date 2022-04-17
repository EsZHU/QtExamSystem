#include "singlerow.h"
#include "ui_singlerow.h"

SingleRow::SingleRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleRow)
{
    ui->setupUi(this);
//    setFixedSize(QSize(fontMetrics().horizontalAdvance(text()) + 35, 30));
    database = new SqliteDatabase();

}

SingleRow::~SingleRow()
{
    delete ui;
}

void SingleRow::refresh(int deptId)
{
    int curDptWorkPerNum = database->getDptPerWorkNum(deptId);
    ui->perNumLabel->setText(QString::number(curDptWorkPerNum));
}

void SingleRow::setDeptLabel(QString dept)
{
    ui->deptLabel->setText(dept);
}

QPushButton* SingleRow::chooseButton()
{
    return ui->chooseButton;
}

QLineEdit *SingleRow::lineEdit()
{
    return ui->chosenPerEdit;
}

int SingleRow::spinBoxNum()
{
    return ui->spinBox->value();
}

void SingleRow::setLineEdit(QString str)
{
    ui->chosenPerEdit->setText(str);
//    connect(ui->chosenPerEdit, &QLineEdit::textChanged, [=](){
//        setFixedSize(sizeHint());
    //    });
}

QPushButton *SingleRow::cancelButton()
{
    return ui->cancelButton;
}

