#ifndef SINGLEROW_H
#define SINGLEROW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class SingleRow;
}

class SingleRow : public QWidget
{
    Q_OBJECT

public:
    explicit SingleRow(QWidget *parent = nullptr);
    ~SingleRow();
    void setDeptLabel(QString dept);
    void chooseButPress();
    QPushButton* chooseButton();
    QLineEdit *lineEdit();
    int spinBoxNum();
    void setLineEdit(QString str);
//    QSize QLineEdit::sizeHint() const{
//        return QSize(fontMetrics().horizontalAdvance(text()) + 35, 30);
//    }
    QPushButton *cancelButton();

private:
    Ui::SingleRow *ui;
};

#endif // SINGLEROW_H
