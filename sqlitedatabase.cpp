#include "sqlitedatabase.h"
#include <QDebug>

SqliteDatabase::SqliteDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath() + "/CONFIG/" + "PickNameDB.sqlite3");
    if(!db.open()) {
        qDebug() << "Can't open PickNameDB.sqlite3." << db.lastError();
    } else {
        qDebug() << "Succeed to connect to PickNameDB.sqlite3.";
    }

    scopeMap.insert("一年前", 1);
    scopeMap.insert("半年前", 2);
    scopeMap.insert("一个月前", 3);
    scopeMap.insert("一周前", 4);
    scopeMap.insert("全部", 5);
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

//    for(int i = 0; i < deptVect.size(); i++) {
//        qDebug() << deptVect[i].id << ":" \
//                 << deptVect[i].deptName;
//    }

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

QMap<int,QVector<person>> SqliteDatabase::getWorkPerData() // 获取人员信息
{
    QMap<int,QVector<person>> perMap;

    QSqlQuery query;

    query.prepare("select * from person");
    query.exec();

    while (query.next()) {
        if(query.value("absent").toInt() == 1){ // absent=1 在岗
            person per;
            per.id = query.value("id").toInt();
            per.deptId = query.value("deptId").toInt();
            per.perName = query.value("perName").toString();
            per.absent = query.value("absent").toInt();

            perMap[per.deptId].push_back(per);
        } else if(query.value("absent").toInt() == 1){
            continue;
        }
    }

    return perMap;
}

QMap<int, QVector<person> > SqliteDatabase::getAbsentPerData() // !!改
{
    QMap<int,QVector<person>> perMap;

    QSqlQuery query;

    query.prepare("select * from person");
    query.exec();

    while (query.next()) {
        if(query.value("absent").toInt() > 1){ // absent>1 缺席
            person per;
            per.id = query.value("id").toInt();
            per.deptId = query.value("deptId").toInt();
            per.perName = query.value("perName").toString();

            perMap[per.deptId].push_back(per);
        } else if(query.value("absent").toInt() == 1){
            continue;
        }
    }

    return perMap;
}

QMap<int, QVector<person> > SqliteDatabase::getEveryPerData()
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
        per.absent = query.value("absent").toInt();

        perMap[per.deptId].push_back(per);
    }

    return perMap;
}

QMap<int, QString> SqliteDatabase::getState()
{
    QMap<int, QString> stateMap;

    QSqlQuery query;

    query.prepare("select * from stateManage");
    query.exec();

    while(query.next()){
        state curState;
        curState.id = query.value("id").toInt();
        curState.stateName = query.value("absent").toString();

        stateMap[curState.id].push_back(curState.stateName);
    }

    return stateMap;
}

void SqliteDatabase::writeSqlPerState(QMap<int,QVector<person>> perMap)
{
    QSqlQuery query;

    for(auto curDeptPers: perMap){
        for(auto per: curDeptPers){
//            qDebug() << per.perName << per.deptId << per.absent << per.id;
            query.prepare("update person set absent = :absent where id = :id");
            query.bindValue(":absent", per.absent);
            query.bindValue(":id", per.id);
            if(!query.exec()){
                qDebug() << "ChangeData failed." << query.lastError();
            }
        }
    }
    // 更改表中id=1222 的deptName属性为admin
    //    query.prepare("update department set deptName='admin' where id='1222'");
    //    query.exec();
}

void SqliteDatabase::setPerAbsent(QString perName)
{
    QSqlQuery query;

    query.prepare("update person set absent = :absent where perName = :perName");
    query.bindValue(":absent", 1);
    query.bindValue(":perName", perName);
    if(!query.exec()){
        qDebug() << "ChangeData failed." << query.lastError();
    }
}

void SqliteDatabase::setPerWork(QString perName)
{
    QSqlQuery query;

    query.prepare("update person set absent = :absent where perName = :perName");
    query.bindValue(":absent", 0);
    query.bindValue(":perName", perName);
    if(!query.exec()){
        qDebug() << "ChangeData failed." << query.lastError();
    }
}

int SqliteDatabase::getDptPerWorkNum(int deptId)
{
    QMap<int,QVector<person>> perMap;
    perMap = getWorkPerData();
    int curDptWorkNum = 0;
    for(auto per: perMap[deptId]){
        curDptWorkNum++;
    }
    return curDptWorkNum;
}

QPair<int, QString> SqliteDatabase::getRanPerString(int n, int deptId, QMap<int,QVector<person>> perData)
{
    QVector<QString> names; // 随机人员数组
    QVector<person> pers = perData[deptId]; // 当前处所有人
    QString ranPerMess = ""; // 随机人员信息
    QPair<int, QString> ranPairMess; // 随机<处室, 人员>信息

    // 不能直接用处的人数，需要计算没有请假的人
    //    int lenth;
    int lenth = pers.size(); // 处的人数
    //    for(auto per: pers){
    //        qDebug() << "lenth";
    //        if(per.absent == 0){
    //            lenth++;
    //        }
    //    }

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

QVector<QString> SqliteDatabase::getRanPerVector(int n, int deptId, QMap<int, QVector<person> > perData)
{
    QVector<person> pers = perData[deptId]; // 当前处所有人
//    for(auto per: pers){
//        qDebug() << per.absent << per.perName;
//    }
    QString ranPerMess = ""; // 随机人员信息
    QVector<QString> ranPairMess; // 随机<处室, 人员>信息

    int lenth = pers.size(); // 处的人数

    // 测试随机选人类
    RandomAccess* random;
    random = new RandomAccess();
    QSet<int> set = random->getRandom(lenth, n);
    QSet<int>::iterator it;
    for(it = set.begin(); it != set.end(); it++) {
        ranPairMess.push_back(pers[*it].perName);
    }
    return ranPairMess;
}

void SqliteDatabase::writePickHis(QDateTime curTime, int deptId, QString names) // 确认抽考
{
    // QMap<int, QString> ranData:int deptId; QString names 同一个处室的人

    //    QString current_date =curTime.toString("yyyy.MM.dd hh:mm:ss");

    QSqlQuery query;

    //    qDebug() <<"test" << deptId << ":" << names;

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
    QSqlQuery query; // 执行操作类对象

    // 查询数据
    query.prepare("select * from pickHistory");
    query.exec(); // 执行

    m_hisVect.clear();

    while (query.next()) {
        hisRecord dept;
        dept.curTime = query.value("curTime").toDateTime();
        dept.ranNames = query.value("ranNames").toString();
        dept.deptId = query.value("deptId").toInt();
        m_hisVect.push_back(dept); // 将查询到的单位数据存储在向量中
    }

    //    for(int i = 0; i < m_hisVect.size(); i++) {
    //        qDebug() << m_hisVect[i].curTime << ":" \
    //                 << m_hisVect[i].ranNames<< ":" \
    //                 << m_hisVect[i].deptId   ;
    //    }

    return m_hisVect;
}

void SqliteDatabase::hisDelete(QString deleteType)
{
    QSqlQuery query; // 执行操作类对象

    // 查询数据
    query.prepare("select * from pickHistory");
    query.exec(); // 执行

    QDateTime nowTime = QDateTime::currentDateTime();//获取系统现在的时间
    QDateTime tempTime;

    int scopeNum = scopeMap[deleteType];

    switch (scopeNum) {
    case 1:{
        // 一年前的数据 deleteType=1
        QDateTime oneYearBefore = nowTime.addYears(-1);
        query.prepare("delete from pickHistory where curTime < :time");
        query.bindValue(":time", oneYearBefore);
        break;
    }
    case 2:{
        // 半年前的数据 deleteType=2
        QDateTime halfYearBefore = nowTime.addMonths(-6);
        query.prepare("delete from pickHistory where curTime < :time");
        query.bindValue(":time", halfYearBefore);
        break;
    }
    case 3:{
        // 一个月前 deleteType=3
        QDateTime oneMonthBefore = nowTime.addMonths(-1);
        query.prepare("delete from pickHistory where curTime < :time");
        query.bindValue(":time", oneMonthBefore);
        break;
    }
    case 4:{
        // 一周前 deleteType=4
        QDateTime oneWeekBefore = nowTime.addDays(-7);
        query.prepare("delete from pickHistory where curTime < :time");
        query.bindValue(":time", oneWeekBefore);
        break;
    }
    case 5:{
        // 全部 deleteType=5
        QDateTime all = nowTime.addMSecs(-1);
        query.prepare("delete from pickHistory where curTime < :time");
        query.bindValue(":time", all);
        break;
    }
    default:
        break;
    }
    query.exec();
}

// 增加人员
void SqliteDatabase::manageAddPerson(QString addName, int deptId)
{
    QSqlQuery query;

    query.prepare("insert into person (deptId, perName) values (:deptId, :perName)");
    query.bindValue(":deptId", deptId);
    query.bindValue(":perName", addName);
    if(!query.exec()){
        qDebug() << "manageAddPerson failed" << query.lastError();
    }
}

void SqliteDatabase::manageAddState(QString addName)
{
    QSqlQuery query;

    query.prepare("insert into stateManage (absent) values (:absent)");
    query.bindValue(":absent", addName);
    if(!query.exec()){
        qDebug() << "manageAddState failed" << query.lastError();
    }
}

void SqliteDatabase::manageEditState(QString beforeName, QString afterName)
{
    QSqlQuery query;
    QMap<int, QString> stateMap;
    int id;

    stateMap = getState();

    for(auto state: stateMap){
        if(state == beforeName){
            id = stateMap.key(state);
//            qDebug() << "id" << id;
            break;
        }
    }


    query.prepare("update stateManage set absent = :absent where id = :id");
    query.bindValue(":absent", afterName);
    query.bindValue(":id", id);
    if(!query.exec())
    {
        qDebug() << "Delete failed." << query.lastError();
    }

}

bool SqliteDatabase::manageDeletePerson(int perId, int deptId)
{
    QSqlQuery query;

    if(manageExist(perId, deptId)){
        query.prepare("delete from person where id = :perId");
        query.bindValue(":perId", perId);
        query.exec();
        return true;
    }
    return false;
}

void SqliteDatabase::manageDeleteState(QString delName)
{
    QSqlQuery query;

    query.prepare("delete from stateManage where absent = :absent");
    query.bindValue(":absent", delName);
    if(!query.exec()){
        qDebug() << "manageDeleteState failed" << query.lastError();
    }
}

void SqliteDatabase::manageChangePerson(QString beforeName, int beforeDeptId, QString afterName, int afterDeptId)
{

}

QVector<int> SqliteDatabase::manageSearchPerson(QString searchName)
{
    QSqlQuery query;
    QVector<int> deptIdVec;
    deptIdVec.clear();

    query.prepare("select * from person where perName = :perName");
    query.bindValue(":perName", searchName);
    query.exec();

    while(query.next()){
        int chartDeptId = query.value("deptId").toInt();
        deptIdVec.push_back(chartDeptId);
    }

    return deptIdVec;

    // 只能得到一个处室，无法得到重名的人
//    query.prepare("select * from person where perName = :perName");
//    query.bindValue(":perName", searchName);
//    query.exec();
//    query.next();
//    int chartDeptId = query.value("deptId").toInt();
//    return chartDeptId;
}

bool SqliteDatabase::manageExist(int perId, int deptId)
{
    QSqlQuery query;

    // 首先查看对应部门有没有这个人
    query.prepare("select * from person where id = :perId");
    query.bindValue(":perId", perId);
    query.exec();
    query.next();
    int chartDeptId = query.value("deptId").toInt();
//    qDebug() << chartDeptId << "chartDeptId" << deptId << "deptId";
    if(chartDeptId == deptId){
        return true;
    }
    return false;
}

bool SqliteDatabase::manageAddDept(QString deptName)
{
//    qDebug() << "deptName" << deptName;
    QSqlQuery query;
    int exist = 0;

    // 首先看有没有这个部门
    QVector<department> depts;
    depts = getDeptData();
    for(auto dept: depts){
        if(dept.deptName == deptName){
            exist = 1;
        }
    }

    if(!exist){
        query.prepare("insert into department (deptName) values (:deptName)");
        query.bindValue(":deptName", deptName);
        if(!query.exec())
        {
            qDebug() << "Insert failed." << query.lastError();
        }
        return true;
    } else {
        return false;
    }
}

bool SqliteDatabase::manageDelDept(QString deptName)
{
    QSqlQuery query;
    int exist = 0, deptNum;

    // 首先看有没有这个部门
    QVector<department> depts;
    depts = getDeptData();
    for(auto dept: depts){
        if(dept.deptName == deptName){
            exist = 1;
            deptNum = dept.id;
        }
    }

    if(exist){
        query.prepare("delete from department where id = :deptNum");
        query.bindValue(":deptNum", deptNum);
        if(!query.exec())
        {
            qDebug() << "Delete failed." << query.lastError();
        }
        return true;
    } else {
        return false;
    }
}

int SqliteDatabase::manageChangingDept(QString beName, QString afName)
{
    QSqlQuery query;
    int beforeExist = 0;
    int afterExist = 0;
    int beId;

    // 首先看有没有这两个部门
    QVector<department> depts;
    depts = getDeptData();
    for(auto dept: depts){
        if(dept.deptName == beName){
            beforeExist = 1;
            beId = dept.id;
        }
        if(dept.deptName == afName){
            afterExist = 1;
        }
    }

    if(beforeExist && !afterExist){
        query.prepare("update department set deptName = :afName where id = :beId");
        query.bindValue(":afName", afName);
        query.bindValue(":beId", beId);
        if(!query.exec())
        {
            qDebug() << "Delete failed." << query.lastError();
        }
        return 1;
    } else if(!beforeExist){
        return 0;
    } else if(beforeExist && afterExist){
        return 2;
    }
}
