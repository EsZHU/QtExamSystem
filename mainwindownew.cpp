#include "mainwindownew.h"
#include "ui_mainwindownew.h"

MainWindowNew::MainWindowNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowNew)
{
    ui->setupUi(this);
    this->setWindowTitle("中共河南省委机构编制委员会办公室随机抽人系统");
    database = new SqliteDatabase();
    getData();
    bindLindAndStack();


//    ui->dptListWidget->insertItem(0,tr("Window1"));//在新建的QListWidget插入3个条目
//    ui->dptListWidget->insertItem(1,tr("Window2"));
//    ui->dptListWidget->insertItem(2,tr("Window3"));

//    QLabel* label1=new QLabel(tr("WindowTest1"));//作为堆栈窗口所需的三层窗口
//    QLabel* label2=new QLabel(tr("WindowTest2"));
//    QLabel* label3=new QLabel(tr("WindowTest3"));

//    ui->dptStackedWidget->addWidget(label1);
//    ui->dptStackedWidget->addWidget(label2);
//    ui->dptStackedWidget->addWidget(label3);

//    QHBoxLayout *mainLayout=new QHBoxLayout(this);//进行布局
//    mainLayout->setSpacing(5);//设定各个控件之间的距离为5
//    mainLayout->addWidget(ui->dptListWidget);
//    mainLayout->addWidget(ui->dptStackedWidget,0,Qt::AlignHCenter);
//    mainLayout->setStretchFactor(ui->dptListWidget,1);//设定可伸缩控件
//    mainLayout->setStretchFactor(ui->dptStackedWidget,3);

//    connect(ui->dptListWidget,SIGNAL(currentRowChanged(int)),ui->dptStackedWidget,SLOT(setCurrentIndex(int)));
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
    for(auto dept: m_depts){
        ui->dptListWidget->insertItem(i++, tr(dept.deptName.toStdString().data()));

        stackedWidgetDialog = new class stackedWidgetDialog();

//        perNum = m_pers[deptId++].size();
        perNum = m_workPers[deptId].size();
        stackedWidgetDialog->setAvailablePerLabel(perNum);

        stackedWidgetDialog->initPerTable(m_workPers, deptId);

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
