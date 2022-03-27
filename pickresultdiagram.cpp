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

void PickResultDiagram::refresh(QMap<QString, QString> pickResult)
{

    QMap<QString, QString>::const_iterator i;
    int p = 0;
    for(i = pickResult.constBegin(); i != pickResult.constEnd(); i++){
        auto widget = new LabelPlus(ui->widget);
        widget->move(10, p * 50);
        p++;
        widget->setLabelText(i.key(), i.value());
    }
}

//QMap<QString,QString>::const_iterator i;
//    for(i=map.constBegin();i!=map.constEnd();++i)
//        qDebug()<<" "<<i.key()<<" "<<i.value();
