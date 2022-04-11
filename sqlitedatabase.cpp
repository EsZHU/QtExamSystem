#include "sqlitedatabase.h"
#include <qDebug>

SqliteDatabase::SqliteDatabase()
{
//    if(QSqlDatabase::contains("qt_sql_default_connection"))
//        db = QSqlDatabase::database("qt_sql_default_connection");
//    else
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(QApplication::applicationDirPath() + "/CONFIG/" + "PickNameDB.sqlite3");
        qDebug() << QApplication::applicationDirPath();
        if(!db.open()) {
            qDebug() << "Can't open PickNameDB.sqlite3." << db.lastError();
        } else {
            qDebug() << "SqliteDatabase::Succeed to connect to PickNameDB.sqlite3.";
        }
        m_db = db;
}

void SqliteDatabase::initPickNameDBtest()
{
    QVector<department> deptVect;
    QVector<person> perVect;

    // 连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(QApplication::applicationDirPath() + "/CONFIG/" + "PickNameDB.sqlite3");
    if(!db.open()) {
        qDebug() << "Can't open PickNameDB.sqlite3." << db.lastError();
    } else {
        qDebug() << "Succeed to connect to PickNameDB.sqlite3.";
    }

//    QSqlQuery sql_query = db.exec("DROP TABLE department");

    /**************************使用QSqlQuery操作数据库**************************/
    QSqlQuery query; // 执行操作类对象

    // 查询数据
    query.prepare("select * from department");
    query.exec(); // 执行

    QSqlRecord record = query.record(); // recode保存查询到一些内容信息，如表头、列数等等
    int col = record.count(); // 获取读取结果的列数
    QString s1 = record.fieldName(0); // 获取第0列的列名

    while (query.next()) {
        department dept;
        dept.id = query.value("id").toInt();
        dept.deptName = query.value("deptName").toString();
        deptVect.push_back(dept); // 将查询到的单位数据存储在向量中
    }

    for(int i = 0; i < deptVect.size(); i++) {
        qDebug() << deptVect[i].id << ":" \
                 << deptVect[i].deptName;
    }

    // 插入数据
//    query.prepare("insert into department (id, deptName) values (:id, :deptName)");
//    query.bindValue(":id", "15");
//    query.bindValue(":deptName", "测试");
//    if(!query.exec())
//    {
//        qDebug() << "Insert failed." << query.lastError();
//    }


//    query.bindValue(":id","16");
//    query.bindValue(":deptName", "测试+");
//    query.exec();


    // 更改表中id=1222 的deptName属性为admin
//    query.prepare("update department set deptName='admin' where id='1222'");
//    query.exec();

    //删除表中 id=1223 的用户信息
//    query.prepare("delete from department where id='1222'");
//    query.exec();
//    query.prepare("delete from department where id='15'");
//    query.exec();
//    query.prepare("delete from department where id='16'");
    //    query.exec();
}

QVector<department> SqliteDatabase::getDeptData()
{
     QVector<department> deptVect;

     /**************************使用QSqlQuery操作数据库**************************/
     QSqlQuery query;

     query.prepare("select * from department");
     query.exec();

     while (query.next()) {
         department dept;
         dept.id = query.value("id").toInt();
         dept.deptName = query.value("deptName").toString();
         deptVect.push_back(dept);
     }

     return deptVect;
}

QMap<int,QVector<person>> SqliteDatabase::getPerData()
{
    QMap<int,QVector<person>> perMap;

    QSqlQuery query;

    query.prepare("select * from person");
    query.exec();

    while (query.next()) {
        person per;
        per.id = query.value("id").toInt();
        per.deptId = query.value("deptId").toInt();
        per.perName = query.value("perName").toString();

        perMap[per.deptId].push_back(per);
    }

    return perMap;
}

QPair<int, QString> SqliteDatabase::getRanPer(int n, int deptId, QMap<int,QVector<person>> perData)
{
    QVector<QString> names; // 随机人员数组
    QVector<person> pers = perData[deptId]; // 当前处所有人
    QString ranPerMess = ""; // 随机人员信息
    QPair<int, QString> ranPairMess; // 随机<处室, 人员>信息

    int lenth = pers.size(); // 处的人数

    // 测试随机选人类
    RandomAccess* random;
    random = new RandomAccess();
    QSet<int> set = random->getRandom(lenth, n);
    QSet<int>::iterator it;
    for(it = set.begin(); it != set.end(); it++) {
        names.push_back(pers[*it].perName);
        if(it != set.begin())
            ranPerMess += ", ";
        ranPerMess = ranPerMess + pers[*it].perName;
    }
    ranPairMess.first = deptId;
    ranPairMess.second = ranPerMess;
    return ranPairMess;
}

void SqliteDatabase::writePickHis(QString curTime, int deptId, QString names) // 确认抽考
{
    // QMap<int, QString> ranData:int deptId; QString names 同一个处室的人

    QSqlQuery query;

    qDebug() <<"test" << deptId << ":" << names;

    query.prepare("insert into pickHistory (curTime, ranNames, deptId) "
                  "values (:curTime, :ranNames, :deptId)"); // id自增，不管

    query.bindValue(":curTime", curTime);
    query.bindValue(":ranNames", names);
    query.bindValue(":deptId", deptId);

    if(!query.exec()){
        qDebug() << "Error: Fail." << query.lastError();
    }

}

QVector<hisRecord> SqliteDatabase::getHisData()
{
    QVector<hisRecord> hisVect;

    QSqlQuery query; // 执行操作类对象

    // 查询数据
    query.prepare("select * from pickHistory");
    query.exec(); // 执行

    while (query.next()) {
        hisRecord dept;
        dept.curTime = query.value("curTime").toString();
        dept.ranNames = query.value("ranNames").toString();
        dept.deptId = query.value("deptId").toInt();
        hisVect.push_back(dept); // 将查询到的单位数据存储在向量中
    }

    for(int i = 0; i < hisVect.size(); i++) {
        qDebug() << hisVect[i].curTime << ":" \
                 << hisVect[i].ranNames<< ":" \
                 << hisVect[i].deptId   ;
    }

    return hisVect;
}
