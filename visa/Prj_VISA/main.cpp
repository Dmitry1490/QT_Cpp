#include "mainatkpa.h"
#include "loghelper.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogHelper::setDebugMessageHandler();
    qApp->setStyle(QStyleFactory::create("Fusion"));
    MainATKPA w;
    w.show();
    return a.exec();
}
