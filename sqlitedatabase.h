#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMap>
#include <randomaccess.h>
#include <defs.h>

struct UserInfo{
    int id;
    int depid;
    QString pername;
};
struct DepInfo{
    int id;
    QString depname;
};

class SqliteDatabase
{
    QSqlDatabase db;
public:
    SqliteDatabase();
    void initPickNameDBtest(); // 测试函数
    QVector<department> getDeptData(); // 读取处表返回处的结构体
    QMap<int,QVector<person>> getWorkPerData(); // 读取人员表返回人员的结构体
    QMap<int,QVector<person>> getAbsentPerData(); // 读取人员表返回人员的结构体
    void setPerAbsent(QString perName);
    QPair<int, QString> getRanPer(int n, int deptId, QMap<int,QVector<person>> perData); // 点击选择获取n人数据
    void writePickHis(QDateTime curTime, int deptId, QString names); // 确认抽考
    QVector<hisRecord> getHisData();
    void hisDelete(QString deleteType);
    void manageAddPerson(QString addName, int deptId);
    bool manageDeletePerson(QString delName, int deptId);
    void manageChangePerson(QString beforeName, int beforeDeptId, QString afterName, int afterDeptId);
    int manageSearchPerson(QString searchName);
    bool manageExist(QString nameS, int deptId);
    bool manageAddDept(QString deptName);
    bool manageDelDept(QString deptName);
    int manageChangingDept(QString beName, QString afName);

private:
    QVector<hisRecord> m_hisVect;
    QMap<QString, int> scopeMap;

 //init db
    void init();
    //增加人员
    bool add_user(UserInfo info);
    //更新人员
    bool update_user(UserInfo info);
    //删除人员
    bool del_user(int id);
    //get user
    UserInfo get_user(int id);
    //
    void showall();
    //
    QList<UserInfo> get_all_user();
    //

private:
    QSqlDatabase m_db;

};

#endif // SQLITEDATABASE_H
