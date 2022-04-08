#ifndef CONFIRMHISDELETEDIALOG_H
#define CONFIRMHISDELETEDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class ConfirmHisDeleteDialog;
}

class ConfirmHisDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmHisDeleteDialog(QWidget *parent = nullptr);
    ~ConfirmHisDeleteDialog();
    void hisDeleteDialogInit();

private:
    Ui::ConfirmHisDeleteDialog *ui;
};

#endif // CONFIRMHISDELETEDIALOG_H
