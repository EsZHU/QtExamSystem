#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sqlitedatabase.h>
#include <singlerow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SqliteDatabase* database = nullptr;
    QVector<SingleRow*> m_singleRows;
    QMap<int,QVector<person>> m_pers;
    QVector<department> m_depts;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showDept(QVector<department> dept);
    void getRanPers();
    void showGUI(int line);
    void getData();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
