#include "blocker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Blocker w;
    w.show();
    return a.exec();
}
