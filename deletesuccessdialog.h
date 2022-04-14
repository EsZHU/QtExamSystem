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
    void showManageAddSuccess(QString addName, QString deptName);
    void showManageDeleteSuccess(QString delName, QString deptName);
    void showManageDeleteFail(QString delName, QString deptName);
    void showManageChangeFail(QString delName, QString deptName);
    void showManageNotComplete();
    void showManageChangeSuccess(QString beName, QString beDept, QString afName, QString afDept);
    void showManageSearchFail(QString searchName);

private:
    Ui::DeleteSuccessDialog *ui;
};

#endif // DELETESUCCESSDIALOG_H
