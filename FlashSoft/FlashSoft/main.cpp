#include "FlashSoft.h"
#include "FlashWgt.h"
//#include "CheckAvailablePort.h"
#include <QtWidgets/QApplication>

//#define SINGLE_EXE

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

#ifdef SINGLE_EXE
	FlashSoft w;
	w.show();
#else
	FlashWgt w;
	w.show();
#endif
	
	//SingleWgt w;
	//w.show();
	return a.exec();
}
