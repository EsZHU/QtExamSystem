#include "stackedwidgetdialog.h"
#include "ui_stackedwidgetdialog.h"

stackedWidgetDialog::stackedWidgetDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stackedWidgetDialog)
{
    ui->setupUi(this);
    ui->chooseButton->setEnabled(false);
}

stackedWidgetDialog::~stackedWidgetDialog()
{
    delete ui;
}

void stackedWidgetDialog::setAvailablePerLabel(int perNum)
{
    ui->availablePerLabel->setText("可选人数为" + QString::number(perNum) + "人");
}

void stackedWidgetDialog::initPerTable(QMap<int,QVector<person>> pers, int deptId)
{
    perTable = new QTableWidget(ui->perShowWidget);
    QStringList strList;
    strList <<"姓名";
    perTable->setColumnCount(1);
    perTable->resize(ui->perShowWidget->width(), ui->perShowWidget->height());
    perTable->setHorizontalHeaderLabels(strList);
    int row;
    for(auto per : pers[deptId]){
        qDebug() << per.perName;
        row = perTable->rowCount();
        perTable->insertRow(row);
        perTable->setItem(row, 0, new QTableWidgetItem(per.perName));
        perTable->item(row,0)->setTextAlignment(Qt::AlignCenter);
    }
    perTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    perTable->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    perTable->horizontalHeader()->setDefaultSectionSize(200);
    perTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //    perTable->setFixedWidth(ui->perShowWidget->width()); // 不起作用
}

void stackedWidgetDialog::chooseRandomPerButton(int ranPerNum)
{

}
