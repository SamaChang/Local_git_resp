#include "EVB_Volume_Test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EVB_Volume_Test w;
    w.show();
    return a.exec();
}
