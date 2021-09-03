#include "NewUsbUpgrade.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NewUsbUpgrade w;
    w.show();
    return a.exec();
}
