#ifndef CHANGEPERWARNING_H
#define CHANGEPERWARNING_H

#include <QWidget>

namespace Ui {
class ChangePerWarning;
}

class ChangePerWarning : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePerWarning(QWidget *parent = nullptr);
    ~ChangePerWarning();

private:
    Ui::ChangePerWarning *ui;
};

#endif // CHANGEPERWARNING_H
