#ifndef STACKEDWIDGETDIALOG_H
#define STACKEDWIDGETDIALOG_H

#include <QWidget>
#include <QTableWidget>
#include "defs.h"
#include <QHeaderView>
#include "sqlitedatabase.h"
#include "confirmpickdialog.h"

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
    void chooseRandomPerButton(int deptId, QMap<int,QVector<person>> pers, int perNum, QString deptName);
    void cancelRandomPerButton(QMap<int,QVector<person>> pers, int deptId);
    void confirmRanPerButton(std::function<void()> cb);
    int returnSpinBoxNum();
    bool ableToChoose();

private:
    Ui::stackedWidgetDialog *ui;
    QTableWidget* perTable;
    SqliteDatabase* database;
//    QMap<int, QPair<int, QString>> m_readPersons; // 之前用QMap是因为要一起抽，现在不用是因为一个一个抽
//    QVector<newSelectRecord> m_readPersons;
    QDateTime curTime;
    newSelectRecord m_readPersons;
};

#endif // STACKEDWIDGETDIALOG_H
