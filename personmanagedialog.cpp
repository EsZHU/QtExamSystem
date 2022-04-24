#include "personmanagedialog.h"
#include "ui_personmanagedialog.h"

PersonManageDialog::PersonManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonManageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("人员管理界面");
    connect(ui->closeButton, &QPushButton::clicked, [=](){this->close();});
    connect(ui->submitButton, &QPushButton::clicked, [=](){
        submitStatePage();
    });
    getData();
    newSetTableWidgetValue();
//    setTabWidgetValue();
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

void PersonManageDialog::newSetTableWidgetValue()
{
    QVector<QTableWidget*> personShowTable;
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
            classBox->addItem("在岗");
            classBox->addItem("请假");
            classBox->addItem("休假");
            classBox->addItem("离职");
            classBox->addItem("病假");
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
    stateType.push_back("在岗");
    stateType.push_back("请假");
    stateType.push_back("休假");
    stateType.push_back("离职");
    stateType.push_back("病假");
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

        //        setTabWidgetValue();
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

}
