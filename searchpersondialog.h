#ifndef SEARCHPERSONDIALOG_H
#define SEARCHPERSONDIALOG_H

#include <QWidget>

namespace Ui {
class SearchPersonDialog;
}

class SearchPersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPersonDialog(QWidget *parent = nullptr);
    ~SearchPersonDialog();

private:
    Ui::SearchPersonDialog *ui;
};

#endif // SEARCHPERSONDIALOG_H
