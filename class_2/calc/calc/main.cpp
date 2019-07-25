#include "venwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VenWidget w;
    w.show();
    char track[] = "취약점";
    char name[] = "김원겸";
    printf("[bob8][%s]vending_machine[%s]", track, name);

    return a.exec();
}
