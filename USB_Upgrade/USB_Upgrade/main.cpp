#include "USB_Upgrade.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    USB_Upgrade w;
    w.show();
    return a.exec();
}
