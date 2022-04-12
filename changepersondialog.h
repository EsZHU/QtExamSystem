#ifndef CHANGEPERSONDIALOG_H
#define CHANGEPERSONDIALOG_H

#include <QWidget>
#include "changeperwarning.h"

namespace Ui {
class ChangePersonDialog;
}

class ChangePersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePersonDialog(QWidget *parent = nullptr);
    ~ChangePersonDialog();
    void confirmButton();

private:
    Ui::ChangePersonDialog *ui;
};

#endif // CHANGEPERSONDIALOG_H
