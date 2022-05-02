#ifndef DEFS_H
#define DEFS_H

#include <QString>
#include <QDateTime>

struct department{
    int id;
    QString deptName;
};

struct person{
    int id;
    int deptId;
    QString perName;
    int absent;
};

struct selectRecord {
    QString deptName, choosenPersons;
};

struct newSelectRecord {
    int deptId;
    QString choosenPersons;
    QDateTime curTime;
    QString deptName;
};

struct hisRecord {
    QDateTime curTime;
    QString ranNames, deptName;
    int deptId;
};

struct hisDetScope {
    int id;
    QString scope;
};

struct state{
    int id;
    QString stateName;
};


typedef std::function<void ()> VOID_FUNC_TYPE;

#endif // DEFS_H
