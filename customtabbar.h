#ifndef CUSTOMTABBAR_H
#define CUSTOMTABBAR_H
#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTabBar>

class CustomTabBar:public QTabBar
{
public:
    CustomTabBar();
    QSize tabSizeHint(int index) const override;
protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // CUSTOMTABBAR_H
