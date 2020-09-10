#include "mainwnd.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWnd w;
    w.show();*/
    QObject* w = ObjectFactory::createObjectFromConfigFile(QApplication::applicationDirPath() + "/MainUi.xml");

    if (ObjectFactory::isWidgetObject(w)) {
        ObjectFactory::toWidgetObject(w)->show();
    }
    return a.exec();
}
