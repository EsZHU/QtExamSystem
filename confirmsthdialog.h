#ifndef CONFIRMSTHDIALOG_H
#define CONFIRMSTHDIALOG_H

#include <QWidget>

namespace Ui {
class ConfirmSthDialog;
}

class ConfirmSthDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmSthDialog(std::function<void ()> cb, QWidget *parent = nullptr);
    ~ConfirmSthDialog();
    void setLabelText(QString labelText);

private:
    std::function<void ()> cbf;
    Ui::ConfirmSthDialog *ui;
};

#endif // CONFIRMSTHDIALOG_H
