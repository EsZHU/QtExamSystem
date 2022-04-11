#include "rygl.h"
#include "ui_rygl.h"

rygl::rygl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rygl)
{
    ui->setupUi(this);
    showtabel();
    this->setWindowTitle("人员管理界面");
    connect(ui->closeButton, &QPushButton::clicked, [=](){
        this->close();

    });
}

rygl::~rygl()
{
    delete ui;
}


void rygl::showtabel()
{

}

void rygl::on_pushButton_2_clicked()
{
    //增加

}


void rygl::on_pushButton_clicked()
{
    //修改
    //获取信息
    //将信息展示在info界面
    //关闭info后并保存后 更新

}

void rygl::on_pushButton_4_clicked()
{
    //删除


}
