    #include "updatertray.h"

UpdaterTray::UpdaterTray(QWidget *parent)
    :QSystemTrayIcon(parent)
    ,menu_(new QMenu(parent))
    ,action_quit(new QAction(tr("終了(&Q)"),parent) )
{
    menu_->addAction(action_quit);
    setContextMenu(menu_);
    connect(action_quit,&QAction::triggered,qApp,&QApplication::quit);
    show();

}
