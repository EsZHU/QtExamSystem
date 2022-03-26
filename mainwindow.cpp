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
//    getRanPers();

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
        for(const auto& deptChoosenPersons: m_readPersons){
            qDebug() << deptChoosenPersons.first << ": " << deptChoosenPersons.second;
        }
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
