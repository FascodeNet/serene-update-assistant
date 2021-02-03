#ifndef UPDATERTRAY_H
#define UPDATERTRAY_H

#include <QSystemTrayIcon>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QApplication>
#include "mainwindow.h"

class UpdaterTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit UpdaterTray(QWidget *parent = nullptr);
private:
    QMenu *menu_;
    QAction *action_quit;
    QAction *action_show_settings;
    MainWindow* main_win=nullptr;
public slots:
    void Show_App();
};

#endif // UPDATERTRAY_H
