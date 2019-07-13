#include "venwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VenWidget w;
    w.show();

    return a.exec();
}
