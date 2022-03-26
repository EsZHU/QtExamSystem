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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showDept(QVector<department> dept);
    void getRanPers();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
