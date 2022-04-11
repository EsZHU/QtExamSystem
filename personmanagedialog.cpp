#include "personmanagedialog.h"
#include "ui_personmanagedialog.h"

PersonManageDialog::PersonManageDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonManageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("人员管理界面");
    connect(ui->closeButton, &QPushButton::clicked, [=](){this->close();});
    setTabWidgetValue();

}

PersonManageDialog::~PersonManageDialog()
{
    delete ui;
}

void PersonManageDialog::setTabWidgetValue()
{
    QTableWidget* firstTB = new QTableWidget(ui->tabWidget);
    QTableWidget* secondTB = new QTableWidget(ui->tabWidget);
    QTableWidget* thirdTB = new QTableWidget(ui->tabWidget);
    QTableWidget* forthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* fifthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* sixthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* seventhTB = new QTableWidget(ui->tabWidget);
    QTableWidget* eightTB = new QTableWidget(ui->tabWidget);
    QTableWidget* ninthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* tenthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* m_eleventhTB = new QTableWidget(ui->tabWidget);
    QTableWidget* m_twelfthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* m_thirteenthTB = new QTableWidget(ui->tabWidget);
    QTableWidget* m_forteenthTB = new QTableWidget(ui->tabWidget);

    ui->tabWidget->addTab(firstTB, "办领导");
    ui->tabWidget->addTab(secondTB, "综合处");
    ui->tabWidget->addTab(thirdTB, "政策法规处");
    ui->tabWidget->addTab(forthTB, "机构改革处");
    ui->tabWidget->addTab(fifthTB, "党群政法行政机构编制管理处");
    ui->tabWidget->addTab(sixthTB, "政府行政机构编制管理处");
    ui->tabWidget->addTab(seventhTB, "市县行政机构编制管理处");
    ui->tabWidget->addTab(eightTB, "事业机构编制管理处");
    ui->tabWidget->addTab(ninthTB, "事业单位登记管理处");
    ui->tabWidget->addTab(tenthTB, "机构编制监督检查处");
    ui->tabWidget->addTab(m_eleventhTB, "人事处");
    ui->tabWidget->addTab(m_twelfthTB, "机关党委");
    ui->tabWidget->addTab(m_thirteenthTB, "省机构编制电子政务中心");
    ui->tabWidget->addTab(m_forteenthTB, "省机构编制研究中心");

    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);

    if(nullptr != firstTB)
        firstTB->setRowCount(0);
    firstTB->insertColumn(1);
    QStringList headList;
    headList.push_back("名字");
    firstTB->setColumnCount(1);
    firstTB->setHorizontalHeaderLabels(headList);
    headList.append("");


}
