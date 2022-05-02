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
        addState();
    });
    connect(ui->deleteButton, &QPushButton::clicked, [=](){
        deleteState();
    });
    connect(ui->editButton, &QPushButton::clicked, [=](){
        editState();
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

void AbsenceManageDialog::addState()
{
    m_state = database->getState();


    StateEditDialog* stateEditDialog = new StateEditDialog("添加状态页面", [&](QString content){
        int exist = 0;
        qDebug() << content;
        qDebug() << "addName" << content;
        if(content != ""){
            for(auto state: m_state){
                if(state == content){
                    exist = 1;
                    qDebug() << "一存在";
                    //                ui->hintLabel->setText("已存在！重新输入");
                }
            }
            if(exist == 0){
                int addRow = stateTable->rowCount();
                stateTable->insertRow(addRow);//添加一行
                stateTable->setItem(addRow, 0, new QTableWidgetItem(content));
                stateTable->item(addRow,0)->setTextAlignment(Qt::AlignCenter);
                stateTable->item(addRow, 0)->setFont(QFont("song", 18));
                database->manageAddState(content);
            }
        } else if(content == ""){
            qDebug() << "不能为空";
            //        ui->hintLabel->setText("输入栏不能为空");
        }
    });
    stateEditDialog->show();
}

void AbsenceManageDialog::deleteState()
{
    m_state = database->getState();
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
    m_state = database->getState();
    if(stateTable->currentRow() != -1){ // 没有选中时=-1
        QString editName, afterName;
        int rowIndex = stateTable->currentRow(), stateNum, ableEdit = 1;
        editName = stateTable->item(rowIndex, 0)->text();

        for(auto state: m_state){
            if(state == editName){
                stateNum = m_state.key(state);
                break;
            }
        }

        if(stateNum == 1 || stateNum == 2){ // 在岗和请假不允许
            ableEdit = 0;
        }

        if(ableEdit){
            StateEditDialog* stateEditDialog = new StateEditDialog("编辑状态页面", editName, [&, rowIndex, editName](QString content) mutable{
                // qDebug() << "content" << content;
                afterName = content;
                // qDebug() << "afterName" << afterName << "rowIndex" << rowIndex << "editName" << editName;
                stateTable->setItem(rowIndex, 0, new QTableWidgetItem(afterName));
                stateTable->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);
                stateTable->item(rowIndex, 0)->setFont(QFont("song", 18));

                database->manageEditState(editName, afterName);

            });
            stateEditDialog->show();
        }
    }
}
