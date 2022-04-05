#ifndef RANDOMACCESS_H
#define RANDOMACCESS_H
#include <QVector>
#include <QTime>
//#include <QRandomGenerator>
#include <QSet>
//#include<QTime>
#include <iostream>
#include <ctime>
class RandomAccess
{
public:
    RandomAccess();
    QSet<int> getRandom(int lenth, int n);
    void generateRandomNumber();
};

#endif // RANDOMACCESS_H
