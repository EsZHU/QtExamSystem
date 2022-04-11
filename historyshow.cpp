#include "historyshow.h"
#include "ui_historyshow.h"

HistoryShow::HistoryShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryShow)
{
    ui->setupUi(this);
    connect(ui->closeButton, &QPushButton::clicked, [=](){this->close();});
    confirmHisDelete();
//    hisDetScopeInit();
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
    QTableWidget *tableWidget = new QTableWidget(ui->widget);
    tableWidget->resize(ui->widget->width(), ui->widget->height());
    tableWidget->setColumnCount(3); //设置列数为3
    QStringList header;
    header << "选择时间" << "处室" << "选择人员";
    tableWidget->setHorizontalHeaderLabels(header);
    int col;
    for(const auto &his : hisResult){
        col = 0;
        tableWidget->insertRow(0); // 之前0的位置是row，倒序显示历史记录，现在正序
//        qDebug() << his.curTime;
        tableWidget->setItem(0, col++, new QTableWidgetItem(his.curTime.toString("yyyy.MM.dd hh:mm:ss")));
        for (const auto& dep : departs) {
            if(dep.id == his.deptId){
                tableWidget->setItem(0, col++, new QTableWidgetItem(dep.deptName));
                break;
            }
        }
        tableWidget->setItem(0, col++, new QTableWidgetItem(his.ranNames));
//        row++;
    }
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();
}

void HistoryShow::confirmHisDelete()
{
    connect(ui->deleteConfirmButton, &QPushButton::clicked, [=](){ // 点击确认删除弹出[确认]弹窗
        QString scopeStr = ui->comboBox->currentText(); // 获取所选择的[删除范围]上文字

        auto *confirmDlg = new ConfirmHisDeleteDialog(); // [确认]弹窗
        confirmDlg->setModal(true); // 模态框
        confirmDlg->show();

        confirmDlg->confirmDlgTrue(scopeStr);

//        if(confirmDlg->confirmDlgTrue(scopeNum)){
//            qDebug() << confirmDlg->confirmDlgTrue(scopeNum);
//        }
//        qDebug() << confirmDlg->confirmDlgTrue(scopeNum);
    });
}
