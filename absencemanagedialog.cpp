#include "absencemanagedialog.h"
#include "ui_absencemanagedialog.h"

AbsenceManageDialog::AbsenceManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbsenceManageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("请假管理页面");
    database = new SqliteDatabase();
    getData();
    refresh();
    confirmAbsentButton();
    confirmBackButton();
}

AbsenceManageDialog::~AbsenceManageDialog()
{
    delete ui;
}

void AbsenceManageDialog::getData()
{
    m_absPers = database->getAbsentPerData();
    m_depts = database->getDeptData();
    m_workPers = database->getWorkPerData();
}

void AbsenceManageDialog::refresh()
{
//    ui->widget_5->hide(); // 暂时不想做成员和处室的适配
//    ui->widget_6->hide(); // 暂时不想做成员和处室的适配
    QTableWidget* absPerTable = new QTableWidget(ui->absenceTableWidget);
    absPerTable->resize(ui->absenceTableWidget->width(), ui->absenceTableWidget->height());
    absPerTable->setColumnCount(2); //设置列数为3
    QStringList header;
//    header << "人名" << "处室" << "请假原因";
    header << "人名" << "处室";
    absPerTable->setHorizontalHeaderLabels(header);

    QVector<person> absPer;

    for(int i = 1; i <= m_depts.size(); i++){
        for(auto per: m_absPers[i]){
            absPer.push_back(per);
        }
    }

    int col;
    int row = 0;

    for(const auto &per : absPer){
        col = 0;
        absPerTable->insertRow(row); // 之前0的位置是row，倒序显示历史记录，现在正序
        absPerTable->setItem(row, col++, new QTableWidgetItem(per.perName));
        for(auto dept: m_depts){
            if(dept.id == per.deptId){
                QString deptName = dept.deptName;
                absPerTable->setItem(row, col++, new QTableWidgetItem(deptName));
            }
        }
//        absPerTable->setItem(0, col++, new QTableWidgetItem(per.absent));
//        qDebug() << per.absent;

        row++;
    }
    absPerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    absPerTable->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    absPerTable->resizeColumnsToContents();
}

void AbsenceManageDialog::confirmAbsentButton()
{
    connect(ui->confirmAbsent, &QPushButton::clicked, [=](){
        int find = 0;
        QString perName = ui->askLeaveNameLabel->text();
//        QString deptName = ui->askLeaveDepNameComboBox->currentText();
        if(perName != ""){
            for(int i = 1; i <= m_depts.size(); i++){
                for(auto per: m_workPers[i]){
                    if(perName == per.perName){ // 找到需要请假的人
                        database->setPerAbsent(perName);
                        m_workPers = database->getWorkPerData();
                        ui->hintLabel->setText("【" + perName + "】成功请假");
                        find = 1;
                    }
                }
            }
            if(find == 0){
                // 您所输入的人不存在或已请假
                ui->hintLabel->setText("您所输入的人不存在或已请假");
            }
        } else if(perName == ""){
                ui->hintLabel->setText("输入栏不能为空");
        }
    });
}

void AbsenceManageDialog::confirmBackButton()
{
    connect(ui->confirmBack, &QPushButton::clicked, [=](){
        int find = 0;
        QString perName = ui->askBackNameLabel->text();
        if(perName != ""){
            for(int i = 1; i <= m_depts.size(); i++){
                for(auto per: m_absPers[i]){
                    if(perName == per.perName){ // 找到需要销假的人
                        database->setPerWork(perName);
                        ui->hintLabelTwo->setText("【" + perName + "】成功销假");
                        find = 1;
                    }
                }
            }
            if(find == 0){
                // 您所输入的人不存在或已销假
                ui->hintLabelTwo->setText("您所输入的人不存在或已销假");
            }
        } else if(perName == ""){
                ui->hintLabelTwo->setText("输入栏不能为空");
        }
    });
}
