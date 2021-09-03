#include "SendJpgDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SendJpgDemo w;
    w.show();
    return a.exec();
}
