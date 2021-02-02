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

void MainWindow::on_UpdateCheckButton_clicked()
{
    ui->jsontestTextEdit->setPlainText(core->get_json());
    UpdaterCore::update_info infokun=core->get_update_info();
    std::cout << infokun.description.toStdString() << std::endl;

}
