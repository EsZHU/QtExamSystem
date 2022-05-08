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
    database = new SqliteDatabase();
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
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    this->setWindowTitle("历史记录");
    ui->tableWidget->setColumnCount(3); //设置列数为3
    QStringList header;
    header << "选择时间" << "处室" << "选择人员";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    int col;
    for(const auto &his : hisResult){
        col = 0;
        ui->tableWidget->insertRow(0); // 之前0的位置是row，倒序显示历史记录，现在正序
        //        qDebug() << his.curTime;
        ui->tableWidget->setItem(0, col++, new QTableWidgetItem(his.curTime.toString("yyyy.MM.dd hh:mm:ss")));
        for (const auto& dep : departs) {
            if(dep.id == his.deptId){
                ui->tableWidget->setItem(0, col++, new QTableWidgetItem(dep.deptName));
                break;
            }
        }
        ui->tableWidget->setItem(0, col++, new QTableWidgetItem(his.ranNames));
        //        row++;
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}

void HistoryShow::confirmHisDelete()
{
    connect(ui->deleteConfirmButton, &QPushButton::clicked, [=](){ // 点击确认删除弹出[确认]弹窗
        QString scopeStr = ui->comboBox->currentText(); // 获取所选择的[删除范围]上文字

        ConfirmHisDeleteDialog* confirmHisDeleteDialog = new ConfirmHisDeleteDialog([=](){
            m_his.clear();
            m_depts.clear();
            m_his = database->getHisData();
            m_depts = database->getDeptData();
            refresh(m_his, m_depts);
        }, scopeStr);
        confirmHisDeleteDialog->show();
        confirmHisDeleteDialog->setWindowModality(Qt::ApplicationModal);
    });
}
