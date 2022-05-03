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
        int first = 1;
        QVector<int> deptIdVec;
        deptIdVec.clear();
        QString searchDeptNa;
        QString searchName = ui->nameLabel->text();
        QString fromDept;
        if(ui->nameLabel->text() == ""){ // 改变前后的名字少了不行
            ui->departLabel->setText("");
            delDlg->setWindowModality(Qt::ApplicationModal);
            delDlg->showManageNotComplete();
            delDlg->show();
        } else {
            deptIdVec = database->manageSearchPerson(searchName);
            if(deptIdVec.empty()) { // 人员不存在
                ui->departLabel->setText("");
                delDlg->setWindowModality(Qt::ApplicationModal);
                delDlg->showManageSearchFail(searchName);
                delDlg->show();
            } else { // 显示对应的处室
                m_depts = database->getDeptData();
                for(auto deptId: deptIdVec){
                    for(auto dept : m_depts){
                        if(deptId == dept.id){
                            if(first){
                                searchDeptNa = dept.deptName;
                                first = 0;
                            } else {
                                searchDeptNa += ", ";
                                searchDeptNa += dept.deptName;
                            }
                        }
                    }
                }
                ui->departLabel->setText(searchDeptNa);
            }
        }
    });
}
