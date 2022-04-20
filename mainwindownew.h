#ifndef MAINWINDOWNEW_H
#define MAINWINDOWNEW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <sqlitedatabase.h>
#include "defs.h"
#include "stackedwidgetdialog.h"

namespace Ui {
class MainWindowNew;
}

class MainWindowNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowNew(QWidget *parent = nullptr);
    ~MainWindowNew();
    void getData();
    void bindLindAndStack();

private:
    Ui::MainWindowNew *ui;
    SqliteDatabase* database;
    QVector<department> m_depts;
    QMap<int,QVector<person>> m_workPers;
    stackedWidgetDialog* stackedWidgetDialog;
};

#endif // MAINWINDOWNEW_H
