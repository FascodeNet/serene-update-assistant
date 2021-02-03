#include "updatertray.h"

UpdaterTray::UpdaterTray(QWidget *parent)
    :QSystemTrayIcon(parent)
    ,menu_(new QMenu(parent))
    ,action_quit(new QAction(tr("&Quit"),parent) )
    ,action_show_settings(new QAction(tr("&Show Updater"),parent))
    ,main_win(new MainWindow(parent))
{
    menu_->addAction(action_show_settings);
    menu_->addSeparator();
    menu_->addAction(action_quit);
    setContextMenu(menu_);
    connect(action_quit,&QAction::triggered,qApp,&QApplication::quit);
    connect(action_show_settings,&QAction::triggered,this,&UpdaterTray::Show_App);
    setIcon(QIcon("://icon_circle.png"));
    show();
    connect(this,&QSystemTrayIcon::activated,
            [this](QSystemTrayIcon::ActivationReason reason){
            if(reason == QSystemTrayIcon::DoubleClick){
                Show_App();
            }
    });

}
void UpdaterTray::Show_App(){
    main_win->show();
}
