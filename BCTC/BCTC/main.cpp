#include "BCTC.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BCTC w;
    w.show();
    return a.exec();
}
