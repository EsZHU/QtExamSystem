#ifndef LABELPLUS_H
#define LABELPLUS_H

#include <QWidget>

namespace Ui {
class LabelPlus;
}

class LabelPlus : public QWidget
{
    Q_OBJECT

public:
    explicit LabelPlus(QWidget *parent = nullptr);
    ~LabelPlus();
    void setLabelText(QString strKey, QString strValue);

private:
    Ui::LabelPlus *ui;
};

#endif // LABELPLUS_H
