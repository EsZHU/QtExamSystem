#include "historyshow.h"
#include "ui_historyshow.h"

HistoryShow::HistoryShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryShow)
{
    ui->setupUi(this);
    confirmHisDelete();
    hisDetScopeInit();
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
//    int row = 0;
    int col;
    for(const auto &his : hisResult){
        col = 0;
        tableWidget->insertRow(0); // 之前0的位置是row，倒序显示历史记录，现在正序
        qDebug() << his.curTime;
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

//    ui->buttonBox(standardButtons::Ok)->setText("确定");
    //            msgb.addButton(QMessageBox::Yes)->setText("确定");
}

void HistoryShow::confirmHisDelete()
{
    connect(ui->deleteConfirmButton, &QPushButton::clicked, [=](){
        qDebug() << "confirmDelete";
        auto *confirmDlg = new ConfirmHisDeleteDialog();
        confirmDlg->setModal(true); // 模态框
        confirmDlg->show();
    });
}

void HistoryShow::hisDetScopeInit()
{

    hisDetScope hisDet;

    hisDet.id = 1;
    hisDet.scope = "一年前";
    m_scopeVect.push_back(hisDet);

    hisDet.id = 2;
    hisDet.scope = "半年前";
    m_scopeVect.push_back(hisDet);

    hisDet.id = 3;
    hisDet.scope = "一个月前";
    m_scopeVect.push_back(hisDet);

    hisDet.id = 4;
    hisDet.scope = "一周前";
    m_scopeVect.push_back(hisDet);

    hisDet.id = 5;
    hisDet.scope = "全部";
    m_scopeVect.push_back(hisDet);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("关闭");

//    for(int i = 0; i < 5; i++){
//        qDebug() << scopeVect[i].id << scopeVect[i].scope;
//    }
}
