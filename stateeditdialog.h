#ifndef STATEEDITDIALOG_H
#define STATEEDITDIALOG_H

#include <QWidget>

namespace Ui {
class StateEditDialog;
}

class StateEditDialog : public QWidget
{
    Q_OBJECT

public:
    explicit StateEditDialog(QWidget *parent = nullptr);
    ~StateEditDialog();
    void setEditLine(QString editState);

private:
    Ui::StateEditDialog *ui;
};

#endif // STATEEDITDIALOG_H
