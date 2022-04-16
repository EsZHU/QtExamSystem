#include "absencemanagedialog.h"
#include "ui_absencemanagedialog.h"

AbsenceManageDialog::AbsenceManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbsenceManageDialog)
{
    ui->setupUi(this);
}

AbsenceManageDialog::~AbsenceManageDialog()
{
    delete ui;
}
