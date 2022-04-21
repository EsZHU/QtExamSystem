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

    refreshDptListShow();
    //    bindLindAndStack();
    initMenu();
    showResultTable = new QTableWidget(ui->resultShowFrame);
    showResultTable->resize(ui->resultShowFrame->width(), ui->resultShowFrame->height());
    initResultShowTable();
    choosePickButton();
    cancelPickButton();
    isSurePickButton();

    ui->dptListWidget->setFocus();
    ui->dptListWidget->setCurrentRow(0);
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

void MainWindowNew::initResultShowTable()
{
    showResultTable->setEditTriggers(QTableWidget::NoEditTriggers);

    QStringList strList;
    strList << "抽取时间" << "抽取处室" << "抽取人名";
    showResultTable->clear();
    showResultTable->horizontalHeader()->setDefaultSectionSize(300);
    showResultTable->setRowCount(0);
    showResultTable->setColumnCount(3);
    showResultTable->setHorizontalHeaderLabels(strList);
    showResultTable->horizontalHeader()->setFont(QFont("song", 18));
}

void MainWindowNew::refreshDptListShow()
{
    auto currentIndex = ui->dptListWidget->currentRow();

    ui->dptListWidget->clear();
    ui->dptListWidget->setCurrentRow(0);
    // 刷新左边处室
    int i = 0;

    QString deptName;
    for(auto dept: m_depts){
        deptName = dept.deptName;
        auto is_picked = m_readPersonsMap.find(dept.id) != m_readPersonsMap.end();
        ui->dptListWidget->insertItem(i++,
                                      tr(((is_picked
                                           ? "√  "
                                           : "    ") + dept.deptName.toStdString())
                                         .data()));
    }

    ui->dptListWidget->setFocus();
    ui->dptListWidget->setCurrentRow(currentIndex);
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

void MainWindowNew::choosePickButton()
{
    connect(ui->chooseButton, &QPushButton::clicked, [=](){
        m_workPers = database->getWorkPerData();
        if(!~ui->dptListWidget->currentRow()) return;
        int deptId = ui->dptListWidget->currentRow() + 1;
        int ranPerNum = ui->spinBox->value();
        if(ranPerNum != 0){ // 人数不为0 才可以使确认按钮使能
            QVector<QString> strs =  database->getRanPerVector(ranPerNum, deptId, m_workPers);
            for(auto per: m_workPers[deptId]){
                qDebug() << per.absent << per.perName;
            }

            // current_date字符串结果为"2016.05.20 12:17:01.445 周五"
            QDateTime current_date_time =QDateTime::currentDateTime();
            QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

            QString names;
            bool flag = false;
            for(auto str: strs){
                if(!flag){
                    names += str;
                    flag = true;
                } else {
                    names += ", ";
                    names += str;
                }
            }
            m_readPersons.choosenPersons = names;
            m_readPersons.curTime = current_date_time;
            m_readPersons.deptId = deptId;

            for(auto dept: m_depts){
                if(dept.id == deptId){
                    m_readPersons.deptName = dept.deptName;
                }
            }

            auto add_one_record = [=](){
                m_readPersonsMap[deptId].choosenPersons = names;
                m_readPersonsMap[deptId].deptId = deptId;
                m_readPersonsMap[deptId].curTime = current_date_time;

                for(auto dept: m_depts){
                    if(dept.id == deptId){
                        m_readPersonsMap[deptId].deptName = dept.deptName;
                    }
                }
                refreshTable();
                refreshDptListShow();
            };

            if(m_readPersonsMap.find(deptId) != m_readPersonsMap.end()){
                // 已经抽取过这个处室的人
                ConfirmSthDialog* confirmCoverDialog = new ConfirmSthDialog([=](){
                    add_one_record();
                });
                confirmCoverDialog->show();
                confirmCoverDialog->setWindowModality(Qt::ApplicationModal);
                confirmCoverDialog->setLabelText("已经抽取过 您确定要覆盖？");
                confirmCoverDialog->setWindowTitle("提示弹窗");
            } else { // 没有抽过这个处室的人
                add_one_record();
            }
        }
    });
}

void MainWindowNew::cancelPickButton()
{
    connect(ui->cancelButton, &QPushButton::clicked, [=](){
        int deptId = ui->dptListWidget->currentRow() + 1;
        qDebug() << deptId;
        if(m_readPersonsMap.find(deptId) != m_readPersonsMap.end()){
            // 已经抽取过这个处室的人
            ConfirmSthDialog* confirmCoverDialog = new ConfirmSthDialog([=](){
                m_readPersonsMap.remove(deptId);
                refreshTable();
                refreshDptListShow();
            });
            confirmCoverDialog->show();
            confirmCoverDialog->setWindowModality(Qt::ApplicationModal);
            confirmCoverDialog->setLabelText("您确定要取消这个处室的抽选结果吗？");
            confirmCoverDialog->setWindowTitle("提示弹窗");
        }
    });
}

void MainWindowNew::isSurePickButton()
{
    connect(ui->confirmButton, &QPushButton::clicked, [=](){
        if(m_readPersonsMap.empty()) return;

        QVector<selectRecord> pickResultVec;

        for(const auto& deptChoosenPersons: m_readPersonsMap) {
            database->writePickHis(deptChoosenPersons.curTime, deptChoosenPersons.deptId, deptChoosenPersons.choosenPersons);
        }

        ui->chooseButton->setEnabled(false);
        ui->cancelButton->setEnabled(false);
        ui->confirmButton->setEnabled(false);
    });

}

void MainWindowNew::refreshTable()
{
    showResultTable->clearContents();
    showResultTable->setRowCount(0);

    for(const auto& pers: m_readPersonsMap){
        int col = 0;
        int row = showResultTable->rowCount();
        showResultTable->insertRow(row);
        showResultTable->setItem(row, col, new QTableWidgetItem(pers.curTime.toString("yyyy.MM.dd hh:mm:ss")));
        showResultTable->item(row,col)->setTextAlignment(Qt::AlignCenter);
        showResultTable->item(row,col++)->setFont(QFont("song", 18));
        showResultTable->setItem(row, col, new QTableWidgetItem(pers.deptName));
        showResultTable->item(row,col)->setTextAlignment(Qt::AlignCenter);
        showResultTable->item(row,col++)->setFont(QFont("song", 18));
        showResultTable->setItem(row, col, new QTableWidgetItem(pers.choosenPersons));
        showResultTable->item(row,col)->setTextAlignment(Qt::AlignCenter);
        showResultTable->item(row,col++)->setFont(QFont("song", 18));
        //            ui->confirmButton->setEnabled(true);
    }
}

void MainWindowNew::on_dptListWidget_currentRowChanged(int currentRow)
{
    if(!~currentRow) return;
    m_workPers = database->getWorkPerData();
    int deptId = ui->dptListWidget->currentRow() + 1;
    auto maxPerson = m_workPers[deptId].size();

    ui->spinBox->setMaximum(maxPerson);
    ui->availablePerLabel->setText("可选 "+QString::number(maxPerson)+" 人");

}

