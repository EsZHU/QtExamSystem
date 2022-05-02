#include "addpersondialog.h"
#include "ui_addpersondialog.h"
#include "defs.h"

AddPersonDialog::AddPersonDialog(QWidget *parent):
    QWidget(parent), ui(new Ui::AddPersonDialog)
{
    ui->setupUi(this);
    database = new SqliteDatabase();
    this->setWindowTitle("增加人员界面");
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){this->close();});
    delDlg = new DeleteSuccessDialog();
    m_depts = database->getDeptData();
}

AddPersonDialog::AddPersonDialog(QString deptName, VOID_FUNC_TYPE cb): AddPersonDialog()
{
    this->cb = cb;

    int deptId;
    for(auto dept: m_depts){
        if(dept.deptName == deptName){
            deptId = dept.id;
        }
    }
    ui->deptNameLabel->setText(deptName);
    addPersonButton(deptId, deptName);
    this->setWindowModality(Qt::ApplicationModal);
    this->show();
}

AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}

void AddPersonDialog::addPersonButton(int addDeptId, QString addDeptName)
{
    auto that = this;
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        QString addName = ui->nameLabel->text();

        if(addName == ""){ // 改变前后的名字少了不行
            delDlg->setWindowModality(Qt::ApplicationModal);
            delDlg->showManageNotComplete();
            delDlg->show();
        } else{
            database->manageAddPerson(addName, addDeptId);

            cb();
            that->close();
        }
    });
}
