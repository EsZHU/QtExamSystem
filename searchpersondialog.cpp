#include "searchpersondialog.h"
#include "ui_searchpersondialog.h"

SearchPersonDialog::SearchPersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPersonDialog)
{
    ui->setupUi(this);
//    ui->departLabel->setPlaceholderText("不可编辑");
    this->setWindowTitle("搜索人员界面");
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){this->close();});
    delDlg = new DeleteSuccessDialog();
    database = new SqliteDatabase();
    searchPersonButton();
}

SearchPersonDialog::~SearchPersonDialog()
{
    delete ui;
}

void SearchPersonDialog::searchPersonButton()
{
    connect(ui->saveBtn, &QPushButton::clicked, [=](){
        int searchDeptNum = 0;
        QString searchDeptNa;
        QString searchName = ui->nameLabel->text();
        QString fromDept;
        if(ui->nameLabel->text() == ""){ // 改变前后的名字少了不行
            delDlg->setWindowModality(Qt::ApplicationModal);
            delDlg->showManageNotComplete();
            delDlg->show();
        } else {
            searchDeptNum = database->manageSearchPerson(searchName);
            if(searchDeptNum > 14 || searchDeptNum < 1) { // 人员不存在
                ui->departLabel->setText("");
                delDlg->setWindowModality(Qt::ApplicationModal);
                delDlg->showManageSearchFail(searchName);
                delDlg->show();
            } else { // 显示对应的处室
                m_depts = database->getDeptData();
                for(auto dept : m_depts){
                    if(searchDeptNum == dept.id){
                        searchDeptNa = dept.deptName;
                        break;
                    }
                }
                ui->departLabel->setText(searchDeptNa);
            }
        }
    });
}
