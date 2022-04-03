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

struct SelectRecord {
    QString deptName, choosenPersons;
};

struct hisRecord {
    QString curTime, ranNames, deptName;
    int deptId;
};


#endif // DEFS_H
