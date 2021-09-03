#include "CaptureTool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	//QFont font;
	//font.setFamily("MicroSoft Yahei");
	//font.setPixelSize(12);
	//a.setFont(font);
    CaptureTool w;
	//w.showMaximized();
    w.show();
    return a.exec();
}
