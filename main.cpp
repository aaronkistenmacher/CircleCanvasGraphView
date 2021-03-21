#include "CircleWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CircleWindow w;
    w.show();

    return a.exec();
}
