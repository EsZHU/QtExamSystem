#ifndef STACKEDWIDGETDIALOG_H
#define STACKEDWIDGETDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include "defs.h"
#include <QHeaderView>
#include "sqlitedatabase.h"

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
    void initPerTable(QMap<int,QVector<person>> pers, int deptId);
    void chooseRandomPerButton(int deptId, QMap<int,QVector<person>> pers, int perNum);
    void cancelRandomPerButton(QMap<int,QVector<person>> pers, int deptId);
    void confirmRanPerButton();
    int returnSpinBoxNum();
    bool ableToChoose();

private:
    Ui::stackedWidgetDialog *ui;
    QTableWidget* perTable;
    SqliteDatabase* database;
};

#endif // STACKEDWIDGETDIALOG_H
