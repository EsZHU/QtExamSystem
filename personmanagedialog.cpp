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
}

PersonManageDialog::~PersonManageDialog()
{
    delete ui;
}

void PersonManageDialog::newSetTableWidgetValue()
{
    //    QVector<QTableWidget*> personShowTable;
//    for(auto dept: m_depts){
//        QTableWidget* table = new QTableWidget(ui->tabWidget);

//        if(nullptr != table)
//            table->setRowCount(0);
//        table->insertColumn(2);

//        headList << "名字" << "状态";
//        table->setColumnCount(2);
//        table->setHorizontalHeaderLabels(headList);
//        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
//        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//        headList.append("");

//        for (auto &per : m_pers[dept.id]) {
//            int col = 0;
//            int row = table->rowCount();
//            table->insertRow(row);
//            QTableWidgetItem *firstPerName=new QTableWidgetItem();//创建一个Item
//            firstPerName->setText(per.perName);//设置内容
//            table->setItem(row,col,firstPerName);//把这个Item加到第一行第二列中
//            table->item(row,col)->setTextAlignment(Qt::AlignCenter);
//            table->item(row,col++)->setFont(QFont("song", 18));

//            QComboBox *classBox = new QComboBox;
//            for(auto state: m_state){
//                classBox->addItem(state);
//            }
//            table->setCellWidget(row, col++, classBox);
//            QString currentState = m_state[per.absent];
//            classBox->setCurrentText(currentState);
//        }

//        personShowTable.push_back(table); // 表格初始化
//        ui->tabWidget->addTab(table, tabTitleVec[dept.id-1]); // 处室初始化
//    }
//    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
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
    DeletePersonDialog* delPerDlg = new DeletePersonDialog();

}

void PersonManageDialog::changePersonButton()
{
    int curDeptNum = ui->tabWidget->currentIndex() + 1;
    ChangePersonDialog* changePerDlg = new ChangePersonDialog();
    changePerDlg->setWindowModality(Qt::ApplicationModal);
    changePerDlg->show();
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
            table->item(row,col++)->setFont(QFont("song", 18));

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
