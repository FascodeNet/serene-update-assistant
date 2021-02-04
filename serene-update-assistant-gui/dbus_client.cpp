#include "dbus_client.h"

Dbus_Client::Dbus_Client(QString path,QString objname,QString recievename,QString senderName,QObject *parent ) : QObject(parent)
  ,pathkun(path),objn(objname),recieveN(recievename),senderN(senderName)
{

}
void Dbus_Client::initDbus(){
    QDBusConnection session_Dbus=QDBusConnection::connectToBus(QDBusConnection::SessionBus,recieveN);
    if(!session_Dbus.isConnected()){
        return;
    }
    //new NetFascodeSerenelinuxSerene_updater_assistantDbusInterface::eventFilter(Dbus_Client)
}
