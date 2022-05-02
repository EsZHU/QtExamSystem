#ifndef STATEEDITDIALOG_H
#define STATEEDITDIALOG_H

#include <QWidget>

namespace Ui {
class StateEditDialog;
}

typedef std::function<void (QString)> FUNC_TYPE;

class StateEditDialog : public QWidget
{
    Q_OBJECT

public:
    explicit StateEditDialog(QWidget *parent = nullptr);
    StateEditDialog(QString windowTitle, QString editName, FUNC_TYPE cb);
    StateEditDialog(QString windowTitle, FUNC_TYPE cb);
    ~StateEditDialog();
    void setEditLine(QString editState);

private:
    Ui::StateEditDialog *ui;
    FUNC_TYPE cb;
};

#endif // STATEEDITDIALOG_H
