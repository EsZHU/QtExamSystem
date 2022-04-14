#include "addpersondialog.h"
#include "ui_addpersondialog.h"
#include "defs.h"

AddPersonDialog::AddPersonDialog(QWidget* pmd, QWidget *parent) :
    QWidget(parent), ui(new Ui::AddPersonDialog),
    m_pmd(pmd)
{
    ui->setupUi(this);
    database = new SqliteDatabase();
    this->setWindowTitle("增加人员界面");
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){this->close();});
    delDlg = new DeleteSuccessDialog();
    addPersonButton();
}

AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}

void AddPersonDialog::addPersonButton()
{
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        QString addName = ui->nameLabel->text();
        QString addDeptName = ui->depNameComboBox->currentText();

        if(ui->nameLabel->text() == ""){ // 改变前后的名字少了不行
            delDlg->setWindowModality(Qt::ApplicationModal);
            delDlg->showManageNotComplete();
            delDlg->show();
        } else{
            m_depts = database->getDeptData();
            int addDeptId;
            for(auto dept : m_depts)
                if(dept.deptName == addDeptName)
                    addDeptId = dept.id;
            qDebug() << addDeptId;

            database->manageAddPerson(addName, addDeptId);

            DeleteSuccessDialog* delDlg = new DeleteSuccessDialog();
            delDlg->showManageAddSuccess(addName, addDeptName);
            delDlg->setWindowModality(Qt::ApplicationModal);
            delDlg->show();

            this->close();

            // 动态显示 没成功？
    //        ((PersonManageDialog* )m_pmd)->setTabWidgetValue();
        }
    });
}
