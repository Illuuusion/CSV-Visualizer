#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    top = (Node*)calloc(1, sizeof(Node));
    arr = (double*)malloc(MIN_REGIONS * sizeof(double));
    doOperation(Default, &context, param, top, tail, arr, &metrics, &inputData);
    connect(ui->RegionName, &QLineEdit::textChanged, this, &MainWindow::on_RegionName_textChanged);
    connect(ui->Row, &QSpinBox::textChanged, this, &MainWindow::on_Row_valueChanged);
    connect(ui->loadData, &QPushButton::clicked, this, &MainWindow::on_loadData_clicked);
    connect(ui->calculateMetrics, &QPushButton::clicked, this, &MainWindow::on_calculateMetrics_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Browser_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Opening a file", QDir::currentPath(), "*.csv");
    ui->labelFileName->setText(QFileInfo(fileName).fileName());
    param.fileName = fileName.toStdString();
    doOperation(UpdatingFileName, &context, param, top, tail, arr, &metrics, &inputData);
}

void MainWindow::on_RegionName_textChanged(const QString &arg1)
{
    param.regionName = arg1.toStdString();
    doOperation(UpdatingRegionName, &context, param, top, tail, arr, &metrics, &inputData);
}


void MainWindow::on_loadData_clicked()
{
    doOperation(LoadData, &context, param, top, tail, arr, &metrics, &inputData);
    ui->CorrectLinesLabel->setText(QString::number(inputData.countOk));
    ui->ErrorLinesLabel->setText(QString::number(inputData.countError));
    displayData();
}


void MainWindow::on_Row_valueChanged(const QString &arg1)
{
    param.numberColumn = arg1.toInt();
    doOperation(UpdatingNumberColumn, &context, param, top, tail, arr, &metrics, &inputData);
}

void MainWindow::on_calculateMetrics_clicked()
{
    if(context.regionName != ""){
        doOperation(CalculatingMetrics, &context, param, top, tail, arr, &metrics, &inputData);
        ui->labelMinRes->setText(QString::number(metrics.min));
        ui->labelMediumRes->setText(QString::number(metrics.medium));
        ui->labelMaxRes->setText(QString::number(metrics.max));
    }
}

QTableWidgetItem* printCell(std::string str){
    return new QTableWidgetItem(QString::fromStdString(str));
}

QTableWidgetItem* printCell(double num){
    QTableWidgetItem* item=new QTableWidgetItem();
    item->setData(Qt::DisplayRole, num);
    return item;}

void MainWindow::printRow(Node* top, int indRow, QTableWidget* table){
    table->setItem(indRow, 0, printCell(top->data.year));
    table->setItem(indRow, 1, printCell(top->data.regionName));
    table->setItem(indRow, 2, printCell(top->data.populationGrowth));
    table->setItem(indRow, 3, printCell(top->data.birthRate));
    table->setItem(indRow, 4, printCell(top->data.deathRate));
    table->setItem(indRow, 5, printCell(top->data.demographicWeight));
    table->setItem(indRow, 6, printCell(top->data.urbanization));
}

void MainWindow::displayData(){
    ui->tableWidget->clear();
    QStringList headerLabels;
    headerLabels << "Year" << "Region" << "Population growth" << "Birth rate" << "Death rate" << "Demographic weight" << "Urbanization";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setRowCount(inputData.countOk);
    Node* curr = top->next;
    for(int i = 0; i < inputData.countOk; ++i){
        printRow(curr, i, ui->tableWidget);
        curr = curr->next;
    }
}

