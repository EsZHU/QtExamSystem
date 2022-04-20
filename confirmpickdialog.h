#ifndef CONFIRMPICKDIALOG_H
#define CONFIRMPICKDIALOG_H

#include <QWidget>


namespace Ui {
class ConfirmPickDialog;
}

class ConfirmPickDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmPickDialog(QWidget *parent = nullptr);
    ~ConfirmPickDialog();
    bool confirmPick(std::function<int> func);

    bool confirmPick(std::function<void ()> func);
private:
    Ui::ConfirmPickDialog *ui;
    int confirm;

    std::function<void ()> confirmCBF;
};

#endif // CONFIRMPICKDIALOG_H
