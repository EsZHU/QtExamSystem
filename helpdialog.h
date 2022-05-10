#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QWidget>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QWidget
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

private:
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_H
