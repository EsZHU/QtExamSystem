#include "personmanagedialog.h"
#include "ui_personmanagedialog.h"

PersonManageDialog::PersonManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonManageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("人员管理界面");
    connect(ui->closeButton, &QPushButton::clicked, [=](){this->close();});
    getData();
    setTabWidgetValue();
    database = new SqliteDatabase();
}

PersonManageDialog::~PersonManageDialog()
{
    delete ui;
}

void PersonManageDialog::setTabWidgetValue()
{
    QTableWidget* firstTB = new QTableWidget(ui->tabWidget);
//    firstTB = nullptr;
    QTableWidget* secondTB = new QTableWidget(ui->tabWidget);
    QTableWidget* thirdTB = new QTableWidget(ui->tabWidget);
    QTableWidget* forthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* fifthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* sixthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* seventhTB = new QTableWidget(ui->tabWidget);
    QTableWidget* eightTB = new QTableWidget(ui->tabWidget);
    QTableWidget* ninthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* tenthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* eleventhTB = new QTableWidget(ui->tabWidget);
    QTableWidget* twelfthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* thirteenthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* forteenthTB = new QTableWidget(ui->tabWidget);

    ui->tabWidget->addTab(firstTB, "办领导");
    ui->tabWidget->addTab(secondTB, "综合处");
    ui->tabWidget->addTab(thirdTB, "政策法规处");
    ui->tabWidget->addTab(forthTB, "机构改革处");
    ui->tabWidget->addTab(fifthTB, "党群政法行政机构编制管理处");
    ui->tabWidget->addTab(sixthTB, "政府行政机构编制管理处");
    ui->tabWidget->addTab(seventhTB, "市县行政机构编制管理处");
    ui->tabWidget->addTab(eightTB, "事业机构编制管理处");
    ui->tabWidget->addTab(ninthTB, "事业单位登记管理处");
    ui->tabWidget->addTab(tenthTB, "机构编制监督检查处");
    ui->tabWidget->addTab(eleventhTB, "人事处");
    ui->tabWidget->addTab(twelfthTB, "机关党委");
    ui->tabWidget->addTab(thirteenthTB, "省机构编制电子政务中心");
    ui->tabWidget->addTab(forteenthTB, "省机构编制研究中心");

    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);

    if(nullptr != firstTB)
        firstTB->setRowCount(0);
    firstTB->insertColumn(1);
    QStringList headList;
    headList.push_back("名字");
    firstTB->setColumnCount(1);
    firstTB->setHorizontalHeaderLabels(headList);
    headList.append("");

    qDebug() << m_pers[1].first().perName;
    for (auto &firstPer : m_pers[1]) {
        int row = firstTB->rowCount();
        firstTB->insertRow(row);
        QTableWidgetItem *firstPerName=new QTableWidgetItem();//创建一个Item
        firstPerName->setText(firstPer.perName);//设置内容
        firstTB->setItem(row,0,firstPerName);//把这个Item加到第一行第二列中

        qDebug() << firstPer.perName;
    }

    if(nullptr != secondTB)
        secondTB->setRowCount(0);
    secondTB->insertColumn(1);
    secondTB->setColumnCount(1);
    secondTB->setHorizontalHeaderLabels(headList);

    for (auto &secondPer : m_pers[2]) {
        int row = secondTB->rowCount();
        secondTB->insertRow(row);
        QTableWidgetItem *secondPerName=new QTableWidgetItem();//创建一个Item
        secondPerName->setText(secondPer.perName);//设置内容
        secondTB->setItem(row,0,secondPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != thirdTB)
        thirdTB->setRowCount(0);
    thirdTB->insertColumn(1);
    thirdTB->setColumnCount(1);
    thirdTB->setHorizontalHeaderLabels(headList);

    for (auto &thirdPer : m_pers[3]) {
        int row = thirdTB->rowCount();
        thirdTB->insertRow(row);
        QTableWidgetItem *thirdPerName=new QTableWidgetItem();//创建一个Item
        thirdPerName->setText(thirdPer.perName);//设置内容
        thirdTB->setItem(row,0,thirdPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != forthTB)
        forthTB->setRowCount(0);
    forthTB->insertColumn(1);
    forthTB->setColumnCount(1);
    forthTB->setHorizontalHeaderLabels(headList);

    for (auto &forthPer : m_pers[4]) {
        int row = forthTB->rowCount();
        forthTB->insertRow(row);
        QTableWidgetItem *forthPerName=new QTableWidgetItem();//创建一个Item
        forthPerName->setText(forthPer.perName);//设置内容
        forthTB->setItem(row,0,forthPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != fifthTB)
        fifthTB->setRowCount(0);
    fifthTB->insertColumn(1);
    fifthTB->setColumnCount(1);
    fifthTB->setHorizontalHeaderLabels(headList);

    for (auto &fifthPer : m_pers[5]) {
        int row = fifthTB->rowCount();
        fifthTB->insertRow(row);
        QTableWidgetItem *fifthPerName=new QTableWidgetItem();//创建一个Item
        fifthPerName->setText(fifthPer.perName);//设置内容
        fifthTB->setItem(row,0,fifthPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != sixthTB)
        sixthTB->setRowCount(0);
    sixthTB->insertColumn(1);
    sixthTB->setColumnCount(1);
    sixthTB->setHorizontalHeaderLabels(headList);

    for (auto &sixthPer : m_pers[6]) {
        int row = sixthTB->rowCount();
        sixthTB->insertRow(row);
        QTableWidgetItem *sixthPerName=new QTableWidgetItem();//创建一个Item
        sixthPerName->setText(sixthPer.perName);//设置内容
        sixthTB->setItem(row,0,sixthPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != seventhTB)
        seventhTB->setRowCount(0);
    seventhTB->insertColumn(1);
    seventhTB->setColumnCount(1);
    seventhTB->setHorizontalHeaderLabels(headList);

    for (auto &seventhPer : m_pers[7]) {
        int row = seventhTB->rowCount();
        seventhTB->insertRow(row);
        QTableWidgetItem *sevenPerName=new QTableWidgetItem();//创建一个Item
        sevenPerName->setText(seventhPer.perName);//设置内容
        seventhTB->setItem(row,0,sevenPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != eightTB)
        eightTB->setRowCount(0);
    eightTB->insertColumn(1);
    eightTB->setColumnCount(1);
    eightTB->setHorizontalHeaderLabels(headList);

    for (auto &eightPer : m_pers[8]) {
        int row = eightTB->rowCount();
        eightTB->insertRow(row);
        QTableWidgetItem *eightPerName=new QTableWidgetItem();//创建一个Item
        eightPerName->setText(eightPer.perName);//设置内容
        eightTB->setItem(row,0,eightPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != ninthTB)
        ninthTB->setRowCount(0);
    ninthTB->insertColumn(1);
    ninthTB->setColumnCount(1);
    ninthTB->setHorizontalHeaderLabels(headList);

    for (auto &ninthPer : m_pers[9]) {
        int row = ninthTB->rowCount();
        ninthTB->insertRow(row);
        QTableWidgetItem *ninthPerName=new QTableWidgetItem();//创建一个Item
        ninthPerName->setText(ninthPer.perName);//设置内容
        ninthTB->setItem(row,0,ninthPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != tenthTB)
        tenthTB->setRowCount(0);
    tenthTB->insertColumn(1);
    tenthTB->setColumnCount(1);
    tenthTB->setHorizontalHeaderLabels(headList);

    for (auto &tenthPer : m_pers[10]) {
        int row = tenthTB->rowCount();
        tenthTB->insertRow(row);
        QTableWidgetItem *tenthPerName=new QTableWidgetItem();//创建一个Item
        tenthPerName->setText(tenthPer.perName);//设置内容
        tenthTB->setItem(row,0,tenthPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != eleventhTB)
        eleventhTB->setRowCount(0);
    eleventhTB->insertColumn(1);
    eleventhTB->setColumnCount(1);
    eleventhTB->setHorizontalHeaderLabels(headList);

    for (auto &eleventhPer : m_pers[11]) {
        int row = eleventhTB->rowCount();
        eleventhTB->insertRow(row);
        QTableWidgetItem *elevenPerName=new QTableWidgetItem();//创建一个Item
        elevenPerName->setText(eleventhPer.perName);//设置内容
        eleventhTB->setItem(row,0,elevenPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != twelfthTB)
        twelfthTB->setRowCount(0);
    twelfthTB->insertColumn(1);
    twelfthTB->setColumnCount(1);
    twelfthTB->setHorizontalHeaderLabels(headList);

    for (auto &twelfthPer : m_pers[12]) {
        int row = twelfthTB->rowCount();
        twelfthTB->insertRow(row);
        QTableWidgetItem *twelfthPerName=new QTableWidgetItem();//创建一个Item
        twelfthPerName->setText(twelfthPer.perName);//设置内容
        twelfthTB->setItem(row,0,twelfthPerName);//把这个Item加到第一行第二列中
    }


    if(nullptr != thirteenthTB)
        thirteenthTB->setRowCount(0);
    thirteenthTB->insertColumn(1);
    thirteenthTB->setColumnCount(1);
    thirteenthTB->setHorizontalHeaderLabels(headList);

    for (auto &thirteenthPer : m_pers[13]) {
        int row = thirteenthTB->rowCount();
        thirteenthTB->insertRow(row);
        QTableWidgetItem *thirteenthPerName=new QTableWidgetItem();//创建一个Item
        thirteenthPerName->setText(thirteenthPer.perName);//设置内容
        thirteenthTB->setItem(row,0,thirteenthPerName);//把这个Item加到第一行第二列中
    }

    if(nullptr != forteenthTB)
        forteenthTB->setRowCount(0);
    forteenthTB->insertColumn(1);
    forteenthTB->setColumnCount(1);
    forteenthTB->setHorizontalHeaderLabels(headList);

    for (auto &forteenthPer : m_pers[14]) {
        int row = forteenthTB->rowCount();
        forteenthTB->insertRow(row);
        QTableWidgetItem *forteenthPerName=new QTableWidgetItem();//创建一个Item
        forteenthPerName->setText(forteenthPer.perName);//设置内容
        forteenthTB->setItem(row,0,forteenthPerName);//把这个Item加到第一行第二列中
    }

}

void PersonManageDialog::getData()
{
    m_pers = database->getPerData();
}
