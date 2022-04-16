#ifndef ABSENCEMANAGEDIALOG_H
#define ABSENCEMANAGEDIALOG_H

#include <QWidget>

namespace Ui {
class AbsenceManageDialog;
}

class AbsenceManageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AbsenceManageDialog(QWidget *parent = nullptr);
    ~AbsenceManageDialog();

private:
    Ui::AbsenceManageDialog *ui;
};

#endif // ABSENCEMANAGEDIALOG_H
