#include "dptmanagedialog.h"
#include "ui_dptmanagedialog.h"

DptManageDialog::DptManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DptManageDialog)
{
    database = new SqliteDatabase();
    m_depts = database->getDeptData();
    m_allPers = database->getEveryPerData();
    ui->setupUi(this);
    this->setWindowTitle("部门管理页面");
    connect(ui->addDptButton, &QPushButton::clicked, [=](){
        addDept();
        //        addDptDialog = new AddDptDialog();
        //        addDptDialog->setWindowModality(Qt::ApplicationModal);
        //        addDptDialog->show();
    });
    connect(ui->deleteDptButton, &QPushButton::clicked, [=](){
        deleteDept();
        //        delDptDialog = new DelDptDialog();
        //        delDptDialog->setWindowModality(Qt::ApplicationModal);
        //        delDptDialog->show();
    });
    connect(ui->changeDptButton, &QPushButton::clicked, [=](){
        editDept();
        //        changeDptDialog = new ChangeDptDialog();
        //        changeDptDialog->setWindowModality(Qt::ApplicationModal);
        //        changeDptDialog->show();
    });
    refresh();
}

DptManageDialog::~DptManageDialog()
{
    delete ui;
}

void DptManageDialog::refresh()
{
    // 初始化窗口
    ui->tableWidget->setColumnCount(1); //设置列数为1
    QStringList header;
    header << "部门列表";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setFont(QFont("song", 18));
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    for(auto dept: m_depts){
//        qDebug() << dept.deptName;
        deptVec.push_back(dept.deptName);
    }

    int row = 0;

    for(const auto &dept : deptVec){
        ui->tableWidget->insertRow(row); // 之前0的位置是row，倒序显示历史记录，现在正序
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(dept));
        ui->tableWidget->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(row,0)->setFont(QFont("song", 18));
        row++;
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    ui->tableWidget->resizeColumnsToContents();
}

void DptManageDialog::addDept()
{
    m_depts = database->getDeptData();

    StateEditDialog* stateEditDialog = new StateEditDialog("添加部门页面", [&](QString content){
            int exist = 0;
            //        qDebug() << content;
            //        qDebug() << "addName" << content;
            if(content != ""){
            for(auto dept: m_depts){
            if(dept.deptName == content){
            exist = 1;
            qDebug() << "已存在";
            // ui->hintLabel->setText("已存在！重新输入");
}
}
            if(exist == 0){
            int addRow = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(addRow);//添加一行
            ui->tableWidget->setItem(addRow, 0, new QTableWidgetItem(content));
            ui->tableWidget->item(addRow,0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->item(addRow, 0)->setFont(QFont("song", 18));
            database->manageAddDept(content);
}
} else if(content == ""){
            qDebug() << "不能为空";
            // ui->hintLabel->setText("输入栏不能为空");
}
});
    stateEditDialog->show();
}

void DptManageDialog::deleteDept()
{
    m_depts = database->getDeptData();
    if(ui->tableWidget->currentRow() != -1){ // 没有选中时=-1
        int stateNum, ableDel = 1;
        QString delName;
        int rowIndex = ui->tableWidget->currentRow();
        delName = ui->tableWidget->item(rowIndex, 0)->text();

        for(auto dept: m_depts){
            if(dept.deptName == delName){
                stateNum = dept.id;
                break;
            }
        }

        for(auto dept: m_depts){
            if(dept.deptName == delName){
                // 遍历所有人，看看是否使用当前要删的部门，如果在用，就不允许删除
                for(int j = 1; j <= m_depts.size(); j++){
                    if(!ableDel)
                        break;
                    for(auto per: m_allPers[j]){
                        if(!ableDel) break;
                        if(per.deptId == stateNum){ // 不让
                            qDebug() << "使用中，不允许删除";
                            ableDel = 0;
                            break;
                        }
                    }
                }
                if(ableDel){
                    if (rowIndex!=-1)
                    {
                        ui->tableWidget->removeRow(rowIndex);
                    }
                    database->manageDelDept(delName);
                }
            }
        }
    }
}

void DptManageDialog::editDept()
{
    m_depts = database->getDeptData();
    if(ui->tableWidget->currentRow() != -1){ // 没有选中时=-1
        QString editName;
        int rowIndex = ui->tableWidget->currentRow(), stateNum;
        editName = ui->tableWidget->item(rowIndex, 0)->text();

        for(auto dept: m_depts){
            if(dept.deptName == editName){
                stateNum = dept.id;
                break;
            }
        }

        StateEditDialog* stateEditDialog = new StateEditDialog("编辑部门页面", editName, [&, rowIndex, editName](QString content) mutable{
//             qDebug() << "content" << content;
//             qDebug() << "content" << content << "rowIndex" << rowIndex << "editName" << editName;
            ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(content));
            ui->tableWidget->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->item(rowIndex, 0)->setFont(QFont("song", 18));

            database->manageChangingDept(editName, content);
        });
        stateEditDialog->show();

    }
}
