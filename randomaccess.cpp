#include "randomaccess.h"

RandomAccess::RandomAccess()
{

}

QSet<int> RandomAccess::getRandom(int lenth, int n)
{
    //利用QRandomGenerator类
    QSet<int> set;
    int randN ;

    while (set.size() < n) {
        randN = QRandomGenerator::global()->bounded(0, lenth); // 生成一个0和lenth之间的整数，左闭右开
        set.insert(randN);
    }
    return set;
}
