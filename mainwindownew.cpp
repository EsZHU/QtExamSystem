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
    initMenu();
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

        ui->dptListWidget->insertItem(i, tr(("    "+dept.deptName.toStdString()).data()));
        auto currentItem = ui->dptListWidget->item(i++);

        stackedWidgetDialog = new class stackedWidgetDialog();

        perNum = m_workPers[deptId].size();
        stackedWidgetDialog->setAvailablePerLabel(perNum);

        stackedWidgetDialog->initPerTable(m_workPers, deptId);

        stackedWidgetDialog->chooseRandomPerButton(deptId, m_workPers, perNum, deptName);
        stackedWidgetDialog->cancelRandomPerButton(m_workPers, deptId);
        stackedWidgetDialog->confirmRanPerButton([=](){
            //            currentItem->setBackground(QColor(Qt::darkGreen));
            //            currentItem->setForeground(QColor(Qt::white));
            currentItem->setText(("√  "+dept.deptName.toStdString()).data());
        });

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

void MainWindowNew::initMenu()
{
    //    https://doc.qt.io/qt-5/qtwidgets-mainwindows-application-example.html
    QMenu *guanli = menuBar()->addMenu(tr("&管理"));

    QAction *newActDptManage = new QAction(tr("&部门管理"), this);
    connect(newActDptManage, &QAction::triggered, [=](){
        DptManageDialog* dptManangeDlg = new DptManageDialog();
        dptManangeDlg->show();
        dptManangeDlg->setWindowModality(Qt::ApplicationModal);
    });
    guanli->addAction(newActDptManage);

    QAction *newActPerManage = new QAction(tr("&人员管理"), this);
    connect(newActPerManage, &QAction::triggered, [=](){
        PersonManageDialog* perManageDialog = new PersonManageDialog();
        perManageDialog->show();
        perManageDialog->setWindowModality(Qt::ApplicationModal);
    });
    guanli->addAction(newActPerManage);

    QAction *newActAbsenceManage = new QAction(tr("&请假管理"), this);
    connect(newActAbsenceManage, &QAction::triggered, [=](){
        AbsenceManageDialog* absManageDialog = new AbsenceManageDialog();
        absManageDialog->show();
        absManageDialog->setWindowModality(Qt::ApplicationModal);
    });
    guanli->addAction(newActAbsenceManage);

    QMenu *lishi = menuBar()->addMenu(tr("&历史"));

    QAction *newActHistoryManage = new QAction(tr("&历史记录"), this);
    connect(newActHistoryManage, &QAction::triggered, [=](){
        HistoryShow* historyShowDialog = new HistoryShow();
        m_his = database->getHisData();
        //        hisDiagram->refresh(m_his, m_depts);
        historyShowDialog->refresh(m_his, m_depts);
        historyShowDialog->show();
        historyShowDialog->setWindowModality(Qt::ApplicationModal);
    });
    lishi->addAction(newActHistoryManage);
}
