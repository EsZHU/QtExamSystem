#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = new SqliteDatabase();
    getData();
    initGUI();
    showDept();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getData()
{
    m_depts = database->getDeptData();
    m_pers = database->getPerData();
}

void MainWindow::initGUI()
{
    for(int i = 0; i < m_depts.size(); i++) {
        auto widget = new SingleRow(this->ui->widgetBig);
        widget->move(10, i * 50);

        connect(widget->chooseButton(), &QPushButton::clicked, widget->lineEdit(), [=](){
            QPair<int, QString> str =  database->getRanPer(widget->spinBoxNum(), i+1, m_pers);
            m_readPersons[i] = str;
            refreshSingleRow(i);
        });

        connect(widget->cancelButton(), &QPushButton::clicked, widget->lineEdit(), [=](){
            m_readPersons[i] = {};
            refreshSingleRow(i);
        });
        singleRows.append(widget);
    }

    connect(ui->checkButton, &QPushButton::clicked, [=](){
        QVector<SelectRecord> pickResultVec;
        // current_date字符串结果为"2016.05.20 12:17:01.445 周五"
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");

        for(const auto& deptChoosenPersons: m_readPersons){
            QString tempDept;
            if(deptChoosenPersons.second.size()){
                qDebug() << deptChoosenPersons.first << ": " << deptChoosenPersons.second;
                database->writePickHis(current_date, deptChoosenPersons.first, deptChoosenPersons.second);
                for(auto dept : m_depts){
                    if(dept.id == deptChoosenPersons.first){
                        tempDept = dept.deptName;
                    }
                }
                pickResultVec.push_back({tempDept, deptChoosenPersons.second});
            }
        }
        auto resultDiagram = new PickResultDiagram();
        resultDiagram->refresh(pickResultVec, current_date);
        resultDiagram->show();
        pickResultVec.clear();
    });
}

void MainWindow::showDept()
{
    for(int i = 0; i < m_depts.size(); i++) {
        singleRows[i]->setDeptLabel(m_depts[i].deptName);
    }
}

void MainWindow::refreshSingleRow(int line)
{
    auto widget = singleRows[line];
    widget->setLineEdit(m_readPersons[line].second);
}
