/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp net.fascode.serenelinux.serene_updater_assistant.dbus.xml -p serene_dbus_interface -a serene_dbus_adaptor
 *
 * qdbusxml2cpp is Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef SERENE_DBUS_INTERFACE_H_1612442142
#define SERENE_DBUS_INTERFACE_H_1612442142

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface net.fascode.serenelinux.serene_updater_assistant.dbus
 */
class NetFascodeSerenelinuxSerene_updater_assistantDbusInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "net.fascode.serenelinux.serene_updater_assistant.dbus"; }

public:
    NetFascodeSerenelinuxSerene_updater_assistantDbusInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~NetFascodeSerenelinuxSerene_updater_assistantDbusInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QString> asyncStdOutInvoke(const QString &data)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(data);
        return asyncCallWithArgumentList(QLatin1String("asyncStdOutInvoke"), argumentList);
    }

    inline QDBusPendingReply<QString> asyncStdOutSend()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("asyncStdOutSend"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace net {
  namespace fascode {
    namespace serenelinux {
      namespace serene_updater_assistant {
        typedef ::NetFascodeSerenelinuxSerene_updater_assistantDbusInterface dbus;
      }
    }
  }
}
#endif
