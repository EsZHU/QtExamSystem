#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = new SqliteDatabase();

    showDept(database->getDeptData());
    getRanPers();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showDept(QVector<department> dept)
{
    for(int i = 0; i < dept.size(); i++) {
        qDebug() << dept[i].id << ":" \
                 << dept[i].deptName;

    }
    ui->firstWidget->setDeptLabel(dept[0].deptName);
    ui->secondWidget->setDeptLabel(dept[1].deptName);
    ui->thirdWidget->setDeptLabel(dept[2].deptName);
    ui->forthWidget->setDeptLabel(dept[3].deptName);
    ui->fifthWidget->setDeptLabel(dept[4].deptName);
    ui->sixthWidget->setDeptLabel(dept[5].deptName);
    ui->seventhWidget->setDeptLabel(dept[6].deptName);
    ui->eightWidget->setDeptLabel(dept[7].deptName);
    ui->ninthWidget->setDeptLabel(dept[8].deptName);
    ui->tenthWidget->setDeptLabel(dept[9].deptName);
    ui->widget_11->setDeptLabel(dept[10].deptName);
    ui->widget_12->setDeptLabel(dept[11].deptName);
    ui->widget_13->setDeptLabel(dept[12].deptName);
    ui->widget_14->setDeptLabel(dept[13].deptName);
}

void MainWindow::getRanPers()
{
    // 选择按钮
    connect(ui->firstWidget->chooseButton(), &QPushButton::clicked, ui->firstWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->firstWidget->spinBoxNum(), 1, random->getPerData());
        ui->firstWidget->setLineEdit(str.second);
    });
    connect(ui->secondWidget->chooseButton(), &QPushButton::clicked, ui->secondWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->secondWidget->spinBoxNum(), 2, random->getPerData());
        ui->secondWidget->setLineEdit(str.second);
    });
    connect(ui->thirdWidget->chooseButton(), &QPushButton::clicked, ui->thirdWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->thirdWidget->spinBoxNum(), 3, random->getPerData());
        ui->thirdWidget->setLineEdit(str.second);
    });
    connect(ui->forthWidget->chooseButton(), &QPushButton::clicked, ui->forthWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->forthWidget->spinBoxNum(), 4, random->getPerData());
        ui->forthWidget->setLineEdit(str.second);
    });
    connect(ui->fifthWidget->chooseButton(), &QPushButton::clicked, ui->fifthWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->fifthWidget->spinBoxNum(), 5, random->getPerData());
        ui->fifthWidget->setLineEdit(str.second);
    });
    connect(ui->sixthWidget->chooseButton(), &QPushButton::clicked, ui->sixthWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->sixthWidget->spinBoxNum(), 6, random->getPerData());
        ui->sixthWidget->setLineEdit(str.second);
    });
    connect(ui->seventhWidget->chooseButton(), &QPushButton::clicked, ui->seventhWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->seventhWidget->spinBoxNum(), 7, random->getPerData());
        ui->seventhWidget->setLineEdit(str.second);
    });
    connect(ui->eightWidget->chooseButton(), &QPushButton::clicked, ui->eightWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->eightWidget->spinBoxNum(), 8, random->getPerData());
        ui->eightWidget->setLineEdit(str.second);
    });
    connect(ui->ninthWidget->chooseButton(), &QPushButton::clicked, ui->ninthWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->ninthWidget->spinBoxNum(), 9, random->getPerData());
        ui->ninthWidget->setLineEdit(str.second);
    });
    connect(ui->tenthWidget->chooseButton(), &QPushButton::clicked, ui->tenthWidget->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->tenthWidget->spinBoxNum(), 10, random->getPerData());
        ui->tenthWidget->setLineEdit(str.second);
    });
    connect(ui->widget_11->chooseButton(), &QPushButton::clicked, ui->widget_11->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->widget_11->spinBoxNum(), 11, random->getPerData());
        ui->widget_11->setLineEdit(str.second);
    });
    connect(ui->widget_12->chooseButton(), &QPushButton::clicked, ui->widget_12->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->widget_12->spinBoxNum(), 12, random->getPerData());
        ui->widget_12->setLineEdit(str.second);
    });
    connect(ui->widget_13->chooseButton(), &QPushButton::clicked, ui->widget_13->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->widget_13->spinBoxNum(), 13, random->getPerData());
        ui->widget_13->setLineEdit(str.second);
    });
    connect(ui->widget_14->chooseButton(), &QPushButton::clicked, ui->widget_14->lineEdit(), [=](){
        SqliteDatabase* random;
        random = new SqliteDatabase();
        QPair<int, QString> str =  random->getRanPer(ui->widget_14->spinBoxNum(), 14, random->getPerData());
        ui->widget_14->setLineEdit(str.second);
    });

    // 取消选择
    connect(ui->firstWidget->cancelButton(), &QPushButton::clicked, ui->firstWidget->lineEdit(), [=](){
        ui->firstWidget->setLineEdit("");
    });
    connect(ui->secondWidget->cancelButton(), &QPushButton::clicked, ui->secondWidget->lineEdit(), [=](){
        ui->secondWidget->setLineEdit("");
    });
    connect(ui->thirdWidget->cancelButton(), &QPushButton::clicked, ui->thirdWidget->lineEdit(), [=](){
        ui->thirdWidget->setLineEdit("");
    });
    connect(ui->forthWidget->cancelButton(), &QPushButton::clicked, ui->forthWidget->lineEdit(), [=](){
        ui->forthWidget->setLineEdit("");
    });
    connect(ui->fifthWidget->cancelButton(), &QPushButton::clicked, ui->fifthWidget->lineEdit(), [=](){
        ui->fifthWidget->setLineEdit("");
    });
    connect(ui->sixthWidget->cancelButton(), &QPushButton::clicked, ui->sixthWidget->lineEdit(), [=](){
        ui->sixthWidget->setLineEdit("");
    });
    connect(ui->seventhWidget->cancelButton(), &QPushButton::clicked, ui->seventhWidget->lineEdit(), [=](){
        ui->seventhWidget->setLineEdit("");
    });
    connect(ui->eightWidget->cancelButton(), &QPushButton::clicked, ui->eightWidget->lineEdit(), [=](){
        ui->eightWidget->setLineEdit("");
    });
}

