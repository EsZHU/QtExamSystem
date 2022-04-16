#ifndef DPTMANAGEDIALOG_H
#define DPTMANAGEDIALOG_H

#include <QWidget>
#include "adddptdialog.h"
#include "deldptdialog.h"
#include "changedptdialog.h"

namespace Ui {
class DptManageDialog;
}

class DptManageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DptManageDialog(QWidget *parent = nullptr);
    ~DptManageDialog();
    void refresh();

private:
    Ui::DptManageDialog *ui;
    AddDptDialog* addDptDialog;
    DelDptDialog* delDptDialog;
    ChangeDptDialog* changeDptDialog;
};

#endif // DPTMANAGEDIALOG_H
