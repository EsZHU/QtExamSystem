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
    connect(ui->confirmAdd, &QPushButton::clicked, [=](){
        confirmAdd();
    });
    connect(ui->confirmDelete, &QPushButton::clicked, [=](){
        confirmDelete();
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
    QTableWidget* stateTable = new QTableWidget(ui->absenceTableWidget);
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
    int exist = 0;
    int stateNum, i = 0, ableDel = 1;
    QString delName = ui->askBackNameLabel->text();
    for(auto state: m_state){
        i++;
        if(state == delName){
            qDebug() << state <<delName;
            stateNum = m_state.key(state);
            break;
        }
    }
    qDebug() <<delName << stateNum;
    if(delName != ""){
        for(auto state: m_state){
            if(state == delName){
                exist = 1;
                // 遍历所有人，看看是否使用当前要删的状态，如果在用，就不允许删除
                for(int j = 1; j <= m_depts.size(); j++){
                    if(!ableDel)
                        break;
                    for(auto per: m_allPers[j]){
                        if(!ableDel) break;
                        if(per.absent == stateNum){ // 不让
                            ableDel = 0;
                            ui->hintLabelTwo->setText("不能删除当前状态");
                            break;
                        }
                    }
                }
                if(ableDel)
                    database->manageDeleteState(delName);
            }
        }
        if(exist == 0){
            ui->hintLabelTwo->setText("不存在！重新输入");
        }
    } else if(delName == ""){
        ui->hintLabel->setText("输入栏不能为空");
    }
}
