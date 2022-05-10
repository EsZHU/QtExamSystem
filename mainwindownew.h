#ifndef MAINWINDOWNEW_H
#define MAINWINDOWNEW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <sqlitedatabase.h>
#include "defs.h"
//#include "stackedwidgetdialog.h"
#include <QColorDialog>
#include <QMenu>
#include <QMenuBar>
#include "dptmanagedialog.h"
#include <QToolBar>
#include "personmanagedialog.h"
#include "absencemanagedialog.h"
#include "historyshow.h"
#include "confirmsthdialog.h"
#include "helpdialog.h"
#include "aboutdialog.h"

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
    void initResultShowTable();
    void refreshDptListShow();
//    void bindLindAndStack();
    void initMenu();
    void choosePickButton();
    void cancelPickButton();
    void isSurePickButton();
    void refreshTable();

private slots:
    void on_dptListWidget_currentRowChanged(int currentRow);

private:
    Ui::MainWindowNew *ui;
    SqliteDatabase* database;
    QVector<department> m_depts;
    QMap<int,QVector<person>> m_workPers;
//    stackedWidgetDialog* stackedWidgetDialog;
    QVector<hisRecord> m_his;
//    QTableWidget* showResultTable;
    newSelectRecord m_readPersons;
    QMap<int, newSelectRecord> m_readPersonsMap;

};

#endif // MAINWINDOWNEW_H
