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
};

struct selectRecord {
    QString deptName, choosenPersons;
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


#endif // DEFS_H
