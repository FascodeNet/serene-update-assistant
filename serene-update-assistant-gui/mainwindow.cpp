#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
MainWindow::MainWindow(QSystemTrayIcon *traykun,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    trayiconkun=traykun;
    ui->setupUi(this);
    setWindowIcon(QIcon("://icon_circle.png"));
    core=new UpdaterCore();
    ui->currentosver_label->setText(QString::fromStdString(core->check_current_ver()));
    on_UpdateCheckButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::send_notification(){
    QString app_name=tr("Serene Updater Assistant");
    QString contents=QString::asprintf(tr("New Version %s is found.").toUtf8().data(),infokun.vername.toUtf8().data());
    pid_t pid=fork();
    if(pid < 0){
        perror("fork");
        exit(-1);
    }else if(pid ==0){
        execlp("notify-send","notify-send","-a",app_name.toUtf8().data(),"-t","5000","-i","serene",app_name.toUtf8().data(),contents.toUtf8().data());
        perror("exec");
        exit(-1);
    }
    int status;
    pid_t responsekun = waitpid(pid, &status, 0);
    if(responsekun < 0){
        perror("waitpid");
        exit(-1);
    }

}
void MainWindow::on_UpdateCheckButton_clicked()
{
    //ui->jsontestTextEdit->setPlainText(core->get_json());
    ui->runupdatebutton->setEnabled(false);
    infokun=core->get_update_info();
    std::cout << infokun.description.toStdString() << std::endl;
    ui->update_ver_label->setText(infokun.vername);
    ui->vdesc_textlabel->setText(infokun.description);
    if(infokun.vername != ""){

        ui->runupdatebutton->setEnabled(true);
        /*trayiconkun->showMessage(tr("Serene Updater Assistant"),QString::asprintf(tr("New Version %s is found.").toUtf8().data(),infokun.vername.toUtf8().data())
                                 ,QIcon("://icon_circle.png"),5000);*/

        //trayiconkun->setIcon(QIcon("://icon_circle_arrived.png"));
        send_notification();

    }
}

void MainWindow::on_runupdatebutton_clicked()
{
    std::cout << "debug update button clicked" << std::endl;
    std::cout << infokun.download_update_url.toStdString() << std::endl;
    core->update(&infokun,ui->LogTextEdit);

}
