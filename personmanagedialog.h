#ifndef PERSONMANAGEDIALOG_H
#define PERSONMANAGEDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include <CustomTabStyle.h>
#include <customtabbar.h>


namespace Ui {
class PersonManageDialog;
}

class PersonManageDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PersonManageDialog(QWidget *parent = nullptr);
    ~PersonManageDialog();
    void setTabWidgetValue();

private:
    Ui::PersonManageDialog *ui;
    QTableWidget* m_firstTB;
};

#endif // PERSONMANAGEDIALOG_H
