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
        //        confirmAdd();
        addState();
    });
    connect(ui->deleteButton, &QPushButton::clicked, [=](){
        deleteState();
    });
    connect(ui->editButton, &QPushButton::clicked, [=](){
        editState();
    });
    connect(ui->saveButton, &QPushButton::clicked, [=](){
        saveState();
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

    stateTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    stateTable->horizontalHeader()->setFont(QFont("song", 18));
    stateTable->setSelectionMode(QAbstractItemView::SingleSelection);

//    QVector<QString> stateVec;

    for(auto state: m_state){
        stateVec.push_back(state);
    }

    int row = 0;

    for(const auto &state : stateVec){
        stateTable->insertRow(row); // 之前0的位置是row，倒序显示历史记录，现在正序
        stateTable->setItem(row, 0, new QTableWidgetItem(state));
        stateTable->item(row,0)->setTextAlignment(Qt::AlignCenter);
        stateTable->item(row,0)->setFont(QFont("song", 18));
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

void AbsenceManageDialog::addState()
{
    deleteAble = 0;
    int addRow = stateTable->rowCount();
    stateTable->insertRow(addRow);//添加一行
    stateTable->setCurrentCell(addRow, 0);

//    QTableWidgetItem* item = stateTable->item(addRow,0); //获取每行第1列的单元格指针
//    item->setFlags(Qt::ItemIsEditable);//设置改item可修改

    stateTable->setEditTriggers(QAbstractItemView::DoubleClicked);
//    stateTable->item(addRow,0)->setTextAlignment(Qt::AlignCenter);
//    stateTable->item(addRow, 0)->setFont(QFont("song", 18));

}

void AbsenceManageDialog::deleteState()
{
//    qDebug() << "currentRow" << stateTable->currentRow() << "deleteAble" << deleteAble;
    if(stateTable->currentRow() != -1 && deleteAble){ // 没有选中时=-1
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

void AbsenceManageDialog::editState()
{
    deleteAble = 0;
    //    //# 设置QTableWidget可编辑
    //    ui->tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);
    //    //# 遍历表格的每一行
    //    for(int i=0; i<ui->tableWidget->columnCount()-1; i++)
    //    {
    //        QTableWidgetItem* item = ui->tableWidget->item(i,1); //获取每行第1列的单元格指针
    //        item->setFlags(Qt::ItemIsEnabled);//设置改item不可修改；
    //    }
    //    //    item->setFlags(Qt::ItemIsEnabled） 表格单元item不可编辑
    //    //    item->setFlags(Qt::ItemIsEditable)   表格单元item可编辑
}

void AbsenceManageDialog::saveState()
{
    // 满足要求后
    stateTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    deleteAble = 1;
}
