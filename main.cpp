#include "Fullscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Fullscreen w;
    w.show/*FullScreen*/();

    return a.exec();
}
