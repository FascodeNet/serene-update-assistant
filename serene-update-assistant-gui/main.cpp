#include "updatertray.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    //QTranslator translator;
    //translator.load("serene-update-assistant-gui_ja_JP");
    //translator.load(QLatin1String("serene-update-assistant-gui_" )+QLocale::system().name());
    //a.installTranslator(&translator);
    /*MainWindow w;
    w.show();*/
    UpdaterTray traykun;
    traykun.show();
    Q_INIT_RESOURCE(resources);
    return a.exec();
}
