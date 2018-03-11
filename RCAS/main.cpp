#include "RCASMainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RCASMainWindow w;
    w.show();

    return a.exec();
}
