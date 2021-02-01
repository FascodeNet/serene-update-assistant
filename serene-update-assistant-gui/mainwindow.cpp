#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    upt=new UpdaterTray();
    core=new UpdaterCore();
    ui->currentosver_label->setText(QString::fromStdString(core->check_current_ver()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

