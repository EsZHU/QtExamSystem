#ifndef STACKEDWIDGETDIALOG_H
#define STACKEDWIDGETDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include "defs.h"
#include <QHeaderView>

namespace Ui {
class stackedWidgetDialog;
}

class stackedWidgetDialog : public QWidget
{
    Q_OBJECT

public:
    explicit stackedWidgetDialog(QWidget *parent = nullptr);
    ~stackedWidgetDialog();
    void setAvailablePerLabel(int perNum);
    void initPerTable(QMap<int,QVector<person>> per, int deptId);
    void chooseRandomPerButton(int ranPerNum);

private:
    Ui::stackedWidgetDialog *ui;
    QTableWidget* perTable;
};

#endif // STACKEDWIDGETDIALOG_H
