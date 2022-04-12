#ifndef DELETEPERSONDIALOG_H
#define DELETEPERSONDIALOG_H

#include <QWidget>

namespace Ui {
class DeletePersonDialog;
}

class DeletePersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DeletePersonDialog(QWidget *parent = nullptr);
    ~DeletePersonDialog();

private:
    Ui::DeletePersonDialog *ui;
};

#endif // DELETEPERSONDIALOG_H
