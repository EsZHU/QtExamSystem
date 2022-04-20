#include "randomaccess.h"
#include <QDebug>
RandomAccess::RandomAccess()
{

}

QSet<int> RandomAccess::getRandom(int lenth, int n)
{
    //    //利用QRandomGenerator类
    //    QSet<int> set;
    //    int randN ;

    //    while (set.size() < n) {
    //        randN = QRandomGenerator::global()->bounded(0, lenth); // 生成一个0和lenth之间的整数，左闭右开
    //        set.insert(randN);
    //    }
    //    return set;

    // 从[0，lenth)中抽 n个数 n<=lenth

    QSet<int> set;
    int test;
    srand((int)time(0));
    if(n>lenth) n=lenth;
    while (set.size() < n){
        test = rand() % lenth;
        set.insert(test);
    }
    //    qDebug()<<"lenth,n"<<lenth<<n<<"set:"<<set;
    return set;
}
