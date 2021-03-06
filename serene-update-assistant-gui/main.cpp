#include "updatertray.h"
#include <QCommandLineParser>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Serene Updater Assistant");
    a.setApplicationVersion("1.0");
    a.setQuitOnLastWindowClosed(false);
    QTranslator translator;
    //translator.load("serene-update-assistant-gui_ja_JP");
    translator.load(QLatin1String("serene-update-assistant-gui_" )+QLocale::system().name());
    a.installTranslator(&translator);
    QCommandLineParser  parser;
    parser.setApplicationDescription("Serene Updater Assistant");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption update_option({"u","update"},"Update","version");
    parser.addOption(update_option);
    parser.process(QCoreApplication::arguments());
    if(parser.value(update_option) != nullptr){
        std::cout << "Update ver:" << parser.value(update_option).toStdString() << std::endl;
        UpdaterCore core;
        UpdaterCore::update_info uinfo;
        /*uinfo.description="tintin";
        uinfo.vername=parser.value(update_option);
        uinfo.download_update_url="https://fascodenet.github.io/serenelinux-update-info/updates/33.0.0_33.0.1.sh";*/
        uinfo = core.get_update_info();
        core.update_admin(&uinfo);
        return 0;
    }
    /*MainWindow w;
    w.show();*/
    UpdaterTray traykun;
    traykun.show();
    Q_INIT_RESOURCE(resources);
    return a.exec();
}
