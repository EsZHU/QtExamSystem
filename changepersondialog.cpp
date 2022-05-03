#include "changepersondialog.h"
#include "ui_changepersondialog.h"

ChangePersonDialog::ChangePersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePersonDialog)
{
    ui->setupUi(this);
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){this->close();});
    this->setWindowTitle("修改人员界面");
    delDlg = new DeleteSuccessDialog();
    database = new SqliteDatabase();
    changePersonButton();
}

ChangePersonDialog::~ChangePersonDialog()
{
    delete ui;
}

void ChangePersonDialog::changePersonButton()
{
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        QString beforeName = ui->nameLabelBefore->text();
        int beforePerId = 1;
        QString beforeDept = ui->depNameComboBoxBefore->currentText();
        QString afterName = ui->nameLabelAfter->text();
        QString afterDept = ui->depNameComboBoxAfter->currentText();

        if(ui->nameLabelBefore->text() == "" || ui->nameLabelAfter->text() == ""){ // 改变前后的名字少了一个都不行
            delDlg->setWindowModality(Qt::ApplicationModal);
            delDlg->showManageNotComplete();
            delDlg->show();
        } else { // 名字都有，看第一个名字存在性
            m_depts = database->getDeptData();
            int beDeptId, afDeptId;
            for(auto dept : m_depts){
                if(dept.deptName == beforeDept)
                    beDeptId = dept.id;
                if(dept.deptName == afterDept)
                    afDeptId = dept.id;
            }

            if(!database->manageExist(beforePerId, beDeptId)) { // 待修改名不合法
                delDlg->setWindowModality(Qt::ApplicationModal);
                delDlg->showManageChangeFail(beforeName, beforeDept);
                delDlg->show();
            } else { // 待修改名合法
                // 先删除待修改
                database->manageDeletePerson(beforePerId, beDeptId);
                // 再增加新加的
                database->manageAddPerson(afterName, afDeptId);
                // 成功弹窗
                delDlg->showManageChangeSuccess(beforeName, beforeDept, afterName, afterDept);
                delDlg->setWindowModality(Qt::ApplicationModal);
                delDlg->show();
            }
        }
    });
}
