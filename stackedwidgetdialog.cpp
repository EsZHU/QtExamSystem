#include "stackedwidgetdialog.h"
#include "ui_stackedwidgetdialog.h"

stackedWidgetDialog::stackedWidgetDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stackedWidgetDialog)
{
    ui->setupUi(this);
    database = new SqliteDatabase();
    perTable = new QTableWidget(ui->perShowWidget);
    perTable->resize(ui->perShowWidget->width(), ui->perShowWidget->height());
}

stackedWidgetDialog::~stackedWidgetDialog()
{
    delete ui;
}

void stackedWidgetDialog::setAvailablePerLabel(int perNum)
{
    ui->availablePerLabel->setText("可选人数为" + QString::number(perNum) + "人");
}

void stackedWidgetDialog::initPerTable(QMap<int,QVector<person>> pers, int deptId)
{
    ui->spinBox->setMaximum(pers[deptId].size());
    QStringList strList;
    strList <<"姓名";
    perTable->clear();
    perTable->setRowCount(0);
    perTable->setColumnCount(1);
    perTable->setHorizontalHeaderLabels(strList);
    perTable->horizontalHeader()->setFont(QFont("song", 18));
    int row;
    for(auto per : pers[deptId]){
        row = perTable->rowCount();
        perTable->insertRow(row);
        perTable->setItem(row, 0, new QTableWidgetItem(per.perName));
        perTable->item(row,0)->setTextAlignment(Qt::AlignCenter);
        perTable->item(row,0)->setFont(QFont("song", 18));
    }
    perTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    perTable->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    perTable->horizontalHeader()->setDefaultSectionSize(400);
    perTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->confirmButton->setEnabled(false);
}


void stackedWidgetDialog::chooseRandomPerButton(int deptId, QMap<int,QVector<person>> pers, int perNum, QString deptName)
{
    connect(ui->chooseButton, &QPushButton::clicked, [=](){
        int ranPerNum = ui->spinBox->value();
        if(ranPerNum != 0){ // 人数不为0 才可以使确认按钮使能
            QStringList strList;
            strList << "抽取时间" << "抽取结果";
            perTable->clear();
            perTable->setRowCount(0);
            perTable->setColumnCount(2);
            perTable->setHorizontalHeaderLabels(strList);
            perTable->horizontalHeader()->setFont(QFont("song", 18));
            QVector<QString> strs =  database->getRanPerVector(ranPerNum, deptId, pers);

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

            perTable->horizontalHeader()->setDefaultSectionSize(400);
            int col;
            for(auto str: strs){
                col = 0;
                int row = perTable->rowCount();
                perTable->insertRow(row);
                qDebug() << str << current_date_time;
                perTable->setItem(row, col, new QTableWidgetItem(current_date));
                perTable->item(row,col)->setTextAlignment(Qt::AlignCenter);
                perTable->item(row,col++)->setFont(QFont("song", 18));
                perTable->setItem(row, col, new QTableWidgetItem(str));
                perTable->item(row,col)->setTextAlignment(Qt::AlignCenter);
                perTable->item(row,col++)->setFont(QFont("song", 18));
            }
            ui->confirmButton->setEnabled(true);
        }
    });
}

void stackedWidgetDialog::cancelRandomPerButton(QMap<int,QVector<person>> pers, int deptId)
{
    connect(ui->cancelButton, &QPushButton::clicked, [=](){
        initPerTable(pers, deptId);
        ui->confirmButton->setEnabled(false);
        m_readPersons = {};
    });
}

void stackedWidgetDialog::confirmRanPerButton(std::function<void()> cb)
{
    connect(ui->confirmButton, &QPushButton::clicked, [=](){
        // 如果此时没有选择 不能确认抽取
//        ConfirmPickDialog* comPickDlg = new ConfirmPickDialog();
//        comPickDlg->setWindowModality(Qt::ApplicationModal);
//        comPickDlg->show();

        // 您确认抽取“张xx，张xx”吗？确定后将无法修改
//        comPickDlg->confirmPick([=](){
//            database->writePickHis(m_readPersons.curTime, m_readPersons.deptId, m_readPersons.choosenPersons);
//            ui->chooseButton->setEnabled(false);
//            ui->cancelButton->setEnabled(false);
//            ui->confirmButton->setEnabled(false);

//            cb();
//        }, m_readPersons.choosenPersons);

    });
}

int stackedWidgetDialog::returnSpinBoxNum()
{
    return ui->spinBox->value();
    qDebug() << "sdad" << ui->spinBox->value();
}

bool stackedWidgetDialog::ableToChoose()
{

    return true;
}
