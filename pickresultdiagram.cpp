#include "pickresultdiagram.h"
#include "ui_pickresultdiagram.h"

PickResultDiagram::PickResultDiagram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PickResultDiagram)
{
    ui->setupUi(this);
//    LabelPlus* singleRow;
//    singleRow = new LabelPlus(this->ui->widget);
    connect(ui->closeButton, &QPushButton::clicked, [=](){this->close();});
}

PickResultDiagram::~PickResultDiagram()
{
    delete ui;
}

void PickResultDiagram::refresh(QVector<selectRecord> pickResult, QString curTime)
{
    QTableWidget *tableWidget = new QTableWidget(ui->resultWidget);
    tableWidget->resize(this->width(), this->height());
    tableWidget->setColumnCount(3); //设置列数为3
    QStringList header;
    header << "选择时间"<< "部门名称" << "选择人员";
    tableWidget->setHorizontalHeaderLabels(header);
    int row = 0;
    int col;
    for (const auto& it : pickResult) {
        col = 0;
        tableWidget->insertRow(row);
        tableWidget->setItem(row, col++, new QTableWidgetItem(curTime));
        tableWidget->setItem(row, col++, new QTableWidgetItem(it.deptName));
        tableWidget->setItem(row, col++, new QTableWidgetItem(it.choosenPersons));
    }

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();
}
