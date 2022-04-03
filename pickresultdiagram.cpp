#include "pickresultdiagram.h"
#include "ui_pickresultdiagram.h"

PickResultDiagram::PickResultDiagram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PickResultDiagram)
{
    ui->setupUi(this);
//    LabelPlus* singleRow;
//    singleRow = new LabelPlus(this->ui->widget);
}

PickResultDiagram::~PickResultDiagram()
{
    delete ui;
}

void PickResultDiagram::refresh(QVector<SelectRecord> pickResult, QString curTime)
{
    int p = 0;

    ui->labelValue->setText(curTime);

    auto addToast = [=](QString key, QString val, int top){
        auto widget = new LabelPlus(ui->widget);
        widget->move(10, top);
        widget->setLabelText(key, val);
    };

    for (const auto& it : pickResult) {
        addToast("部门名称", it.deptName,(p++)*50);
        addToast("选择人员", it.choosenPersons,(p++)*50);
    }
}

//QMap<QString,QString>::const_iterator i;
//    for(i=map.constBegin();i!=map.constEnd();++i)
//        qDebug()<<" "<<i.key()<<" "<<i.value();
