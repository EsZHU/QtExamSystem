#ifndef HISTORYSHOW_H
#define HISTORYSHOW_H

#include <QDialog>
#include "defs.h"
#include <QTableWidget>

namespace Ui {
class HistoryShow;
}

class HistoryShow : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryShow(QWidget *parent = nullptr);
    ~HistoryShow();
    QWidget hisShow();
    void refresh(QVector<hisRecord> hisResult, QVector<department> departs);

private:
    Ui::HistoryShow *ui;
};

#endif // HISTORYSHOW_H
