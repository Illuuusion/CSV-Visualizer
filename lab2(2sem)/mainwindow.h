#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "entrypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Browser_clicked();

    void on_RegionName_textChanged(const QString &arg1);

    void on_loadData_clicked();

    void on_Row_valueChanged(const QString &arg1);

    void on_calculateMetrics_clicked();

    void printRow(Node* top, int indRow, QTableWidget* table);

    void displayData();

private:
    Ui::MainWindow *ui;
    AppParams param;
    AppContext context;
    Node* top;
    double* arr;
    CalculatedMetrics metrics;
    CheckInput inputData;
    Node* tail;
};

#endif
