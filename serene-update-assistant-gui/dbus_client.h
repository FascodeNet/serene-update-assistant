#ifndef DBUS_CLIENT_H
#define DBUS_CLIENT_H

#include <QObject>

#include "serene_updater_dbus.h"

#include "dbusadaptor.h"

class Dbus_Client : public NetFascodeSerenelinuxSerene_updater_assistantDbusInterface
{
    Q_OBJECT
public:
    explicit Dbus_Client(QString path,QString objname,QString recievename,QString senderName,QObject *parent = nullptr);
private:
    void initDbus();
    QString pathkun;
    QString objn;
    QString recieveN;
    QString senderN;
signals:

};

#endif // DBUS_CLIENT_H
