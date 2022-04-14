#include "deletepersondialog.h"
#include "ui_deletepersondialog.h"

DeletePersonDialog::DeletePersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeletePersonDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("删除人员界面");
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){this->close();});
    database = new SqliteDatabase();
    delDlg = new DeleteSuccessDialog();
    deletePersonButton();
}

DeletePersonDialog::~DeletePersonDialog()
{
    delete ui;
}

void DeletePersonDialog::deletePersonButton()
{
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        QString delName = ui->nameLabel->text();
        QString delDeptName = ui->depNameComboBox->currentText();

        m_depts = database->getDeptData();
        int delDeptId;
        for(auto dept : m_depts)
            if(dept.deptName == delDeptName)
                delDeptId = dept.id;

        bool delSuc = database->manageDeletePerson(delName, delDeptId);

        if(delSuc){ // 删除成功
            delDlg->showManageDeleteSuccess(delName, delDeptName);
            delDlg->setWindowModality(Qt::ApplicationModal);
            delDlg->show();
            this->close();
        } else { // 删除失败
            delDlg->showManageDeleteFail(delName, delDeptName);
            delDlg->setWindowModality(Qt::ApplicationModal);
            delDlg->show();
        }
    });
}
