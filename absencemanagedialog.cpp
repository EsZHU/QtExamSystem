#include "absencemanagedialog.h"
#include "ui_absencemanagedialog.h"

AbsenceManageDialog::AbsenceManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbsenceManageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("请假方式管理页面");
    database = new SqliteDatabase();
    getData();
    refresh();
    connect(ui->addButton, &QPushButton::clicked, [=](){
        confirmAdd();
    });
    connect(ui->deleteButton, &QPushButton::clicked, [=](){
        confirmDelete();
    });
    connect(ui->editButton, &QPushButton::clicked, [=](){

    });
}

AbsenceManageDialog::~AbsenceManageDialog()
{
    delete ui;
}

void AbsenceManageDialog::getData()
{
    m_absPers = database->getAbsentPerData();
    m_depts = database->getDeptData();
    m_workPers = database->getWorkPerData();
    m_state = database->getState();
    m_allPers = database->getEveryPerData();
}

void AbsenceManageDialog::refresh()
{
    stateTable = new QTableWidget(ui->absenceTableWidget);
    stateTable->resize(ui->absenceTableWidget->width(), ui->absenceTableWidget->height());
    stateTable->setColumnCount(1); //设置列数为1
    QStringList header;
    header << "请假方式";
    stateTable->setHorizontalHeaderLabels(header);

    QVector<QString> stateVec;

    for(auto state: m_state){
        stateVec.push_back(state);
    }

    int col;
    int row = 0;

    for(const auto &state : stateVec){
        col = 0;
        stateTable->insertRow(row); // 之前0的位置是row，倒序显示历史记录，现在正序
        stateTable->setItem(row, col++, new QTableWidgetItem(state));
        row++;
    }
    stateTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    stateTable->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    stateTable->resizeColumnsToContents();
}

void AbsenceManageDialog::confirmAdd()
{
    int exist = 0;
    QString addName = ui->askLeaveNameLabel->text();
    if(addName != ""){
        for(auto state: m_state){
            if(state == addName){
                exist = 1;
                ui->hintLabel->setText("已存在！重新输入");
            }
        }
        if(exist == 0){
            database->manageAddState(addName);
        }
    } else if(addName == ""){
        ui->hintLabel->setText("输入栏不能为空");
    }
}

void AbsenceManageDialog::confirmDelete()
{
//    qDebug() << stateTable->currentRow();
    if(stateTable->currentRow() != -1){ // 没有选中时=-1
        int stateNum, ableDel = 1;
        QString delName;
        int rowIndex = stateTable->currentRow();
        delName = stateTable->item(rowIndex, 0)->text();

        for(auto state: m_state){
            if(state == delName){
                stateNum = m_state.key(state);
                break;
            }
        }

        if(stateNum == 1 || stateNum == 2){ // 在岗和请假不允许删除
            ableDel = 0;
            //        qDebug() << "在岗和请假不允许删";
        }

        for(auto state: m_state){
            if(state == delName){
                // 遍历所有人，看看是否使用当前要删的状态，如果在用，就不允许删除
                for(int j = 1; j <= m_depts.size(); j++){
                    if(!ableDel)
                        break;
                    for(auto per: m_allPers[j]){
                        if(!ableDel) break;
                        if(per.absent == stateNum){ // 不让
                            ableDel = 0;
                            break;
                        }
                    }
                }
                if(ableDel){
                    if (rowIndex!=-1)
                    {
                        stateTable->removeRow(rowIndex);
                    }
                    database->manageDeleteState(delName);
                }
            }
        }
    }
}
