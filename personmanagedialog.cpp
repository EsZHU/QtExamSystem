#include "personmanagedialog.h"
#include "ui_personmanagedialog.h"

PersonManageDialog::PersonManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonManageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("人员管理界面");
    ui->lineEdit->setText("在岗");
    ui->lineEdit_2->setText("请假");
    ui->lineEdit_3->setText("休假");
    ui->lineEdit_4->setText("离职");
    ui->lineEdit_5->setText("病假");
    stateManageMethod();
    connect(ui->changeButton, &QPushButton::clicked, [=](){
        stateManageMethod();
        newSetTableWidgetValue();
    });
    connect(ui->closeButton, &QPushButton::clicked, [=](){this->close();});
    connect(ui->submitButton, &QPushButton::clicked, [=](){
        qDebug() << "start test";
        submitStatePage();
    });
    getData();
    newSetTableWidgetValue();
    database = new SqliteDatabase();
    addPersonButton();
    deletePersonButton();
    changePersonButton();
    searchPersonButton();
}

PersonManageDialog::~PersonManageDialog()
{
    delete ui;
}

void PersonManageDialog::stateManageMethod()
{
    stateType.push_back(ui->lineEdit->text());
    stateType.push_back(ui->lineEdit_2->text());
    stateType.push_back(ui->lineEdit_3->text());
    stateType.push_back(ui->lineEdit_4->text());
    stateType.push_back(ui->lineEdit_5->text());
}

void PersonManageDialog::newSetTableWidgetValue()
{
//    QVector<QTableWidget*> personShowTable;
    for(auto dept: m_depts){
        QTableWidget* table = new QTableWidget(ui->tabWidget);

        if(nullptr != table)
            table->setRowCount(0);
        table->insertColumn(2);

        headList << "名字" << "状态";
        table->setColumnCount(2);
        table->setHorizontalHeaderLabels(headList);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        headList.append("");

        for (auto &per : m_pers[dept.id]) {
            int col = 0;
            int row = table->rowCount();
            table->insertRow(row);
            QTableWidgetItem *firstPerName=new QTableWidgetItem();//创建一个Item
            firstPerName->setText(per.perName);//设置内容
            table->setItem(row,col++,firstPerName);//把这个Item加到第一行第二列中

            QComboBox *classBox = new QComboBox;
            int num = 0;
            classBox->addItem(stateType[num++]);
            classBox->addItem(stateType[num++]);
            classBox->addItem(stateType[num++]);
            classBox->addItem(stateType[num++]);
            classBox->addItem(stateType[num++]);
            table->setCellWidget(row, col++, classBox);
            QString currentState = stateType[per.absent];
            classBox->setCurrentText(currentState);
        }

        personShowTable.push_back(table); // 表格初始化
        ui->tabWidget->addTab(table, tabTitleVec[dept.id-1]); // 处室初始化
    }
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
}

void PersonManageDialog::getData()
{
    m_pers = database->getEveryPerData();
    m_depts = database->getDeptData();
//    stateType.push_back("在岗");
//    stateType.push_back("请假");
//    stateType.push_back("休假");
//    stateType.push_back("离职");
//    stateType.push_back("病假");
    for(auto dept: m_depts){
        tabTitleVec.push_back(dept.deptName);
    }
}

void PersonManageDialog::addPersonButton()
{
    connect(ui->addPersonButton, &QPushButton::clicked, [=](){
        AddPersonDialog* addPerDlg = new AddPersonDialog(this);
        addPerDlg->setWindowModality(Qt::ApplicationModal);
        addPerDlg->show();
    });
}

void PersonManageDialog::deletePersonButton()
{
    connect(ui->deleteButton, &QPushButton::clicked, [=](){
        DeletePersonDialog* delPerDlg = new DeletePersonDialog();
        delPerDlg->setWindowModality(Qt::ApplicationModal);
        delPerDlg->show();
    });
}

void PersonManageDialog::changePersonButton()
{
    connect(ui->changePersonButton, &QPushButton::clicked, [=](){
        ChangePersonDialog* changePerDlg = new ChangePersonDialog();
        changePerDlg->setWindowModality(Qt::ApplicationModal);
        changePerDlg->show();
    });
}

void PersonManageDialog::searchPersonButton()
{
    connect(ui->searchPersonButton, &QPushButton::clicked, [=](){
        SearchPersonDialog* searchPerDlg = new SearchPersonDialog();
        searchPerDlg->setWindowModality(Qt::ApplicationModal);
        searchPerDlg->show();
    });
}

void PersonManageDialog::submitStatePage()
{
    int deptId = 1;
    int stateType;
    for(auto &table: personShowTable){ // 遍历每一个表格/一个处室一个表
        for(int i = 0; i < table->rowCount(); i++){ // 遍历每一行的状态量/重写m_pers的absent值
            auto combox = reinterpret_cast<QComboBox*>(table->cellWidget(i, 1));
            stateType = combox->currentIndex();
//            qDebug() << deptId << i;
            m_pers[deptId][i].absent = stateType;
        }
        deptId++;
    }

    int dept = 1;
//    for(auto per : m_pers){
//        for(auto p: per){
//            qDebug() << p.perName << p.absent;
//        }
//    }
    database->writeSqlPerState(m_pers);
}
