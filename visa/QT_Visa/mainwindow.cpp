#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visa.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get VISA resource manager
    ViSession resource_manager;
    ViStatus  status;
    status = viOpenDefaultRM(&resource_manager);
    if (status < VI_SUCCESS) {
        printf("Could not open VISA resource manager.\n");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
