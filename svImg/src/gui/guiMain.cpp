#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog* w = new Dialog();
    w->show();
    w->display();

    return a.exec();
}
