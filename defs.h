#ifndef DEFS_H
#define DEFS_H

#include <QString>

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
    QString curTime, ranNames, deptName;
    int deptId;
};

struct hisDetScope {
    int id;
    QString scope;
};


#endif // DEFS_H
