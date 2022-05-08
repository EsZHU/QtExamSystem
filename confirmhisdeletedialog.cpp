#include "confirmhisdeletedialog.h"
#include "ui_confirmhisdeletedialog.h"

//ConfirmHisDeleteDialog::ConfirmHisDeleteDialog(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::ConfirmHisDeleteDialog)
//{
//    ui->setupUi(this);
//    database = new SqliteDatabase();
//    this->setWindowTitle("您确认要删除吗？");
////    ui->label_3->setTextInteractionFlags(Qt::TextSelectableByMouse); // 可复制
////    ui->confirmEdit->setPlaceholderText("我确定要删除指定范围内的历史记录"); // 文字显示
//}

ConfirmHisDeleteDialog::ConfirmHisDeleteDialog(std::function<void ()> cb, QString scopeType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmHisDeleteDialog),
    cbf(cb)
{
    ui->setupUi(this);
    database = new SqliteDatabase();
    this->setWindowTitle("您确认要删除吗？");
    connect(ui->yesButton, &QPushButton::clicked, [=](){
        if(ui->confirmEdit->text() == "我确定要删除指定范围内的历史记录"){
            database->hisDelete(scopeType);
            cbf();
            this->close();
            DeleteSuccessDialog* successD = new DeleteSuccessDialog();
            successD->showDeleteSuccess(scopeType);
        }
    });
    connect(ui->noButton, &QPushButton::clicked, [=]()mutable{
        this->close();
    });
}

ConfirmHisDeleteDialog::~ConfirmHisDeleteDialog()
{
    delete ui;
}

//void ConfirmHisDeleteDialog::confirmDlgTrue(QString scopeType)
//{
//    connect(ui->yesButton, &QPushButton::clicked, [=]()mutable{
//        if(ui->confirmEdit->text() == "我确定要删除指定范围内的历史记录"){
//            database->hisDelete(scopeType);
//            this->close();
//            DeleteSuccessDialog* successD = new DeleteSuccessDialog();
//            successD->showDeleteSuccess(scopeType);
//        }
//    });
//    connect(ui->noButton, &QPushButton::clicked, [=]()mutable{
//        this->close();
//    });
//}
