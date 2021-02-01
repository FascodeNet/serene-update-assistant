#ifndef UPDATERTRAY_H
#define UPDATERTRAY_H

#include <QSystemTrayIcon>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QApplication>

class UpdaterTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit UpdaterTray(QWidget *parent = nullptr);
private:
    QMenu *menu_;
    QAction *action_quit;
};

#endif // UPDATERTRAY_H
