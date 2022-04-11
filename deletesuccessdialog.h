#ifndef DELETESUCCESSDIALOG_H
#define DELETESUCCESSDIALOG_H

#include <QWidget>

namespace Ui {
class DeleteSuccessDialog;
}

class DeleteSuccessDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteSuccessDialog(QWidget *parent = nullptr);
    ~DeleteSuccessDialog();
    void showDeleteSuccess(QString scope);

private:
    Ui::DeleteSuccessDialog *ui;
};

#endif // DELETESUCCESSDIALOG_H
