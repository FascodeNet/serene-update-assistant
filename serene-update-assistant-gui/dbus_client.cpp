#include "dbus_client.h"

Dbus_Client::Dbus_Client(QString path,QString objname,QString recievename,QString senderName,QObject *parent ) : QObject(parent)
  ,pathkun(path),objn(objname),recieveN(recievename),senderN(senderName)
{

}
void Dbus_Client::initDbus(){
    QDBusConnection session_Dbus=QDBusConnection::connectToBus(QDBusConnection::SessionBus,senderN);
    if(!session_Dbus.isConnected()){
        return;
    }
    if(!session_Dbus.registerService(pathkun + senderN)){

    }
    if(!session_Dbus.registerObject(objn + senderN,this)){

    }

    new DbusAdaptor(this);
}
void Dbus_Client::createIfce(){
    QDBusConnection session_Dbus=QDBusConnection::connectToBus(QDBusConnection::SessionBus,recieveN);
    if(!session_Dbus.isConnected()){
        return;
    }
    ifcekun=new NetFascodeSerenelinuxSerene_updater_assistantDbusInterface(pathkun + recieveN,objn + recieveN,session_Dbus,this);

}
