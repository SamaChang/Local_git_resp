#include "SLTTestDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SLTTestDemo w;
    w.show();
    return a.exec();
}
