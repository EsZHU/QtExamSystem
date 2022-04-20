#include "mainwindownew.h"
#include "ui_mainwindownew.h"
#include "defs.h"

MainWindowNew::MainWindowNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowNew)
{
    ui->setupUi(this);
    this->setWindowTitle("中共河南省委机构编制委员会办公室随机抽人系统");
    database = new SqliteDatabase();
    getData();
    bindLindAndStack();
}

MainWindowNew::~MainWindowNew()
{
    delete ui;
}

void MainWindowNew::getData()
{
    m_depts = database->getDeptData();
    m_workPers = database->getWorkPerData();
}

void MainWindowNew::bindLindAndStack()
{
    // 处室姓名
    int i = 0, deptId = 1;
    int perNum;
    QString deptName;
    for(auto dept: m_depts){
        deptName = dept.deptName;

        ui->dptListWidget->insertItem(i++, tr(dept.deptName.toStdString().data()));

        stackedWidgetDialog = new class stackedWidgetDialog();

        perNum = m_workPers[deptId].size();
        stackedWidgetDialog->setAvailablePerLabel(perNum);

        stackedWidgetDialog->initPerTable(m_workPers, deptId);

        stackedWidgetDialog->chooseRandomPerButton(deptId, m_workPers, perNum, deptName);
        stackedWidgetDialog->cancelRandomPerButton(m_workPers, deptId);
        stackedWidgetDialog->confirmRanPerButton();

        ui->dptStackedWidget->addWidget(stackedWidgetDialog);
        deptId++;
    }

    QHBoxLayout *mainLayout=new QHBoxLayout(this);//进行布局
    mainLayout->setSpacing(5);//设定各个控件之间的距离为5
    mainLayout->addWidget(ui->dptListWidget);
    mainLayout->addWidget(ui->dptStackedWidget,0,Qt::AlignHCenter);
    mainLayout->setStretchFactor(ui->dptListWidget,1);//设定可伸缩控件
    mainLayout->setStretchFactor(ui->dptStackedWidget,3);

    connect(ui->dptListWidget,SIGNAL(currentRowChanged(int)),ui->dptStackedWidget,SLOT(setCurrentIndex(int)));
}
