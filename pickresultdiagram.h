#ifndef PICKRESULTDIAGRAM_H
#define PICKRESULTDIAGRAM_H

#include <QWidget>
#include <labelplus.h>

namespace Ui {
class PickResultDiagram;
}

class PickResultDiagram : public QWidget
{
    Q_OBJECT

public:
    explicit PickResultDiagram(QWidget *parent = nullptr);
    ~PickResultDiagram();
    void refresh(QMap<QString, QString> pickResult);

private:
    Ui::PickResultDiagram *ui;
};

#endif // PICKRESULTDIAGRAM_H
