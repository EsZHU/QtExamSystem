#include "personmanagedialog.h"
#include "ui_personmanagedialog.h"

PersonManageDialog::PersonManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonManageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("人员管理界面");
    ui->changePersonButton->setVisible(false);
    connect(ui->closeButton, &QPushButton::clicked, [=](){this->close();});
    connect(ui->submitButton, &QPushButton::clicked, [=](){
        submitStatePage();
    });
    getData();
    //    newSetTableWidgetValue();
    initWidget();
    refreshWidget();
    selectFirstPerson(getDeptId(0));

    database = new SqliteDatabase();
    connect(ui->addPersonButton, &QPushButton::clicked, [=](){
        addPersonButton();
    });
    connect(ui->deleteButton, &QPushButton::clicked, [=](){
        deletePersonButton();
    });
    connect(ui->changePersonButton, &QPushButton::clicked, [=](){
        changePersonButton();
    });
    connect(ui->searchPersonButton, &QPushButton::clicked, [=](){
        searchPersonButton();
    });
    connect(ui->tabWidget, &QTabWidget::currentChanged, [=](int index){
        selectFirstPerson(getDeptId(index));
    });
}

PersonManageDialog::~PersonManageDialog()
{
    delete ui;
}

void PersonManageDialog::newSetTableWidgetValue()
{

}


void PersonManageDialog::getData()
{
    m_pers = database->getEveryPerData();
    m_depts = database->getDeptData();
    m_state = database->getState();
    tabTitleVec.clear();
    for(auto dept: m_depts){
        tabTitleVec.push_back(dept.deptName);
    }
}

void PersonManageDialog::addPersonButton()
{
    // 待做：重名检测
    int curDeptNumMinus = ui->tabWidget->currentIndex();
    QString curDeptName = ui->tabWidget->tabBar()->tabText(curDeptNumMinus);
    qDebug() << "curDeptName"<< curDeptName << "curDeptNumMinus" << curDeptNumMinus;
    AddPersonDialog* addPerDlg = new AddPersonDialog(curDeptName, [=](){
        getData();
        refreshWidget();
    });
}

void PersonManageDialog::deletePersonButton()
{
    int curDeptNumMinus = ui->tabWidget->currentIndex();
    int deptId = getDeptId(curDeptNumMinus);

    auto table = personShowTable[deptId];
    auto currentRow = table->currentRow();
    qDebug() << currentRow;
    if(currentRow != -1){
        ConfirmSthDialog* confirmDeleteDialog = new ConfirmSthDialog([=](){
            auto pers = m_pers[deptId];
            //    qDebug() << table->rowCount();
            auto per = pers[currentRow];
            //        qDebug() << per.perName<<per.absent<<per.deptId<<per.id;

            if(database->manageDeletePerson(per.id, deptId)){
                getData();
                refreshWidget();
            }
        });
        confirmDeleteDialog->show();
        confirmDeleteDialog->setWindowModality(Qt::ApplicationModal);
        confirmDeleteDialog->setLabelText("删除后不可恢复，您确认删除？");
        confirmDeleteDialog->setWindowTitle("提示弹窗");
    }
}

void PersonManageDialog::changePersonButton()
{
    int curDeptNum = ui->tabWidget->currentIndex() + 1;
}

void PersonManageDialog::searchPersonButton()
{
    SearchPersonDialog* searchPerDlg = new SearchPersonDialog();
    searchPerDlg->setWindowModality(Qt::ApplicationModal);
    searchPerDlg->show();
}

void PersonManageDialog::submitStatePage()
{
    int deptId = 1;
    int stateType;
    for(auto &table: personShowTable){ // 遍历每一个表格/一个处室一个表
        for(int i = 0; i < table->rowCount(); i++){ // 遍历每一行的状态量/重写m_pers的absent值
            auto combox = reinterpret_cast<QComboBox*>(table->cellWidget(i, 1));
            int count = 0;
            for(auto state: m_state){
                count++;
                if(state == combox->currentText()){
                    stateType = m_state.key(state);
                    break;
                }
            }
            m_pers[deptId][i].absent = stateType;
        }
        deptId++;
    }

    database->writeSqlPerState(m_pers);
}

void PersonManageDialog::initWidget()
{
    for(auto dept: m_depts){
        QTableWidget* table = new QTableWidget(ui->tabWidget);

        if(nullptr != table)
            table->setRowCount(0);
        table->insertColumn(2);

        headList << "名字" << "状态";
        table->setColumnCount(2);
        table->setHorizontalHeaderLabels(headList);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->setFocus();
        table->setCurrentCell(0, 0);

        personShowTable[dept.id] = table; // 表格初始化
        ui->tabWidget->addTab(table, tabTitleVec[dept.id-1]); // 处室初始化
    }
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
}

void PersonManageDialog::refreshWidget()
{
    for(auto dept: m_depts){
        auto table = personShowTable[dept.id];
        table->clearContents();
        table->setRowCount(0);
        for (auto &per : m_pers[dept.id]) {
            int col = 0;
            int row = table->rowCount();
            table->insertRow(row);
            QTableWidgetItem *firstPerName=new QTableWidgetItem();//创建一个Item
            firstPerName->setText(per.perName);//设置内容
            table->setItem(row,col,firstPerName);//把这个Item加到第一行第二列中
            table->item(row,col)->setTextAlignment(Qt::AlignCenter);
            table->item(row,col++)->setFont(QFont("song", 16));

            QComboBox *classBox = new QComboBox;
            for(auto state: m_state){
                classBox->addItem(state);
            }
            table->setCellWidget(row, col++, classBox);
            QString currentState = m_state[per.absent];
            classBox->setCurrentText(currentState);
        }
    }
}

int PersonManageDialog::getDeptId(int index)
{
    int deptId = -1;
    QString curDeptName = ui->tabWidget->tabBar()->tabText(index);
    for(auto dept: m_depts){
        if(dept.deptName == curDeptName){
            deptId = dept.id;
            break;
        }
    }
    return deptId;
}

void PersonManageDialog::selectFirstPerson(int deptId)
{
    auto table = personShowTable[deptId];
    table->setFocus();
    table->setCurrentCell(0, 0);
}
