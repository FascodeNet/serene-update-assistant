#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTranslator>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include "updatercore.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QSystemTrayIcon *traykun, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_UpdateCheckButton_clicked();

    void on_runupdatebutton_clicked();

private:
    Ui::MainWindow *ui;
    UpdaterCore *core=nullptr;
    UpdaterCore::update_info infokun;
    QSystemTrayIcon* trayiconkun;
    void send_notification();
    bool isinited=false;
};
#endif // MAINWINDOW_H
