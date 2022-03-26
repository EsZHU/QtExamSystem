#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <sqlitedatabase.h>
#include <mainwindow.h>
#include <sqlitedatabase.h>
#include <randomaccess.h>
#include <randomaccess.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1440, 960);
    w.show();
//    sqlDB.SqliteDatabase::initPickNameDBtest();
    // 测试随机选人类
//    RandomAccess* random;
//    random = new RandomAccess();
//    QSet<int> set = random->getRandom(20,3);
//    QSet<int>::iterator it;
//    for(it = set.begin(); it != set.end(); it++) {
//        qDebug() << *it;
//    }
    // 测试随机选人函数
//    SqliteDatabase* random;
//    random = new SqliteDatabase();

//    QVector<QString> str =  random->getRanPer(3, 1, random->getPerData());
//    qDebug() << str;
    return a.exec();

}
