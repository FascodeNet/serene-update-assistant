#ifndef DBUS_CLIENT_H
#define DBUS_CLIENT_H

#include <QObject>

#include "serene_dbus_adaptor.h"

#include "serene_dbus_interface.h"

class Dbus_Client : public QObject
{
    Q_OBJECT
public:
    explicit Dbus_Client(QString path,QString objname,QString recievename,QString senderName,QObject *parent = nullptr);
private:
    void initDbus();
    void createIfce();
    QString pathkun;
    QString objn;
    QString recieveN;
    QString senderN;
    NetFascodeSerenelinuxSerene_updater_assistantDbusInterface* ifcekun;
signals:

};

#endif // DBUS_CLIENT_H
