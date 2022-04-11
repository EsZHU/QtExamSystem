#ifndef PICKRESULTDIAGRAM_H
#define PICKRESULTDIAGRAM_H

#include <QWidget>
#include "defs.h"
#include <QTableWidget>

namespace Ui {
class PickResultDiagram;
}

class PickResultDiagram : public QWidget
{
    Q_OBJECT

public:
    explicit PickResultDiagram(QWidget *parent = nullptr);
    ~PickResultDiagram();
    void refresh(QVector<selectRecord> pickResult, QString curTime);

private:
    Ui::PickResultDiagram *ui;
};

#endif // PICKRESULTDIAGRAM_H
