#include "historyshow.h"
#include "ui_historyshow.h"

HistoryShow::HistoryShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryShow)
{
    ui->setupUi(this);
}

HistoryShow::~HistoryShow()
{
    delete ui;
}

QWidget HistoryShow::hisShow()
{

}

void HistoryShow::refresh(QVector<hisRecord> hisResult, QVector<department> departs)
{
    this->setWindowTitle("历史记录");
    QTableWidget *tableWidget = new QTableWidget(this);
    tableWidget->resize(this->width(), this->height());
    tableWidget->setColumnCount(3); //设置列数为3
    QStringList header;
    header << "选择时间" << "处室" << "选择人员";
    tableWidget->setHorizontalHeaderLabels(header);
    int row = 0;
    int col;
    for(const auto &his : hisResult){
        col = 0;
        tableWidget->insertRow(row);
        tableWidget->setItem(row, col++, new QTableWidgetItem(his.curTime));
        for (const auto& dep : departs) {
            if(dep.id == his.deptId){
                tableWidget->setItem(row, col++, new QTableWidgetItem(dep.deptName));
                break;
            }
        }
        tableWidget->setItem(row, col++, new QTableWidgetItem(his.ranNames));
        row++;
    }
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();
}
