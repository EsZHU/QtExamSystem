#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QWidget>

namespace Ui {
class AddPersonDialog;
}

class AddPersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddPersonDialog(QWidget *parent = nullptr);
    ~AddPersonDialog();

private:
    Ui::AddPersonDialog *ui;
};

#endif // ADDPERSONDIALOG_H
