#include "GPIBSet.h"
#include <qicon.h>
#include <visa.h>
#include <visatype.h>

GPIBSet::GPIBSet(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowIcon(QIcon("./Logo.png"));
	findRsrc();
	ui.comboBox->addItems(list);
}

static int i;
static char instrDescriptor[VI_FIND_BUFLEN];
static ViUInt32 numInstrs;
static ViFindList findList;
static ViSession defaultRM, instr;
static ViStatus status;
static ViEventType etype;
static ViEvent ehandle;
static ViUInt16 statusByte;   //SRQ:0x41

GPIBSet::~GPIBSet()
{
}

//查找GPIB设备
int GPIBSet::findRsrc()
{
	//static char instrDescriptor[VI_FIND_BUFLEN];
	//static ViUInt32 numInstrs;
	//static ViFindList findList;
	//static ViSession defaultRM, instr;
	//static ViStatus status;

	status = viOpenDefaultRM(&defaultRM);
	if (status < VI_SUCCESS)
	{
		printf("Could not open a session to the VISA Resource Manager!\n");
		exit(EXIT_FAILURE);
	}

	/*
	 * Find all the VISA resources in our system and store the number of resources
	 * in the system in numInstrs.  Notice the different query descriptions a
	 * that are available.

		Interface         Expression
	--------------------------------------
		GPIB              "GPIB[0-9]*::?*INSTR"
		VXI               "VXI?*INSTR"
		GPIB-VXI          "GPIB-VXI?*INSTR"
		Any VXI           "?*VXI[0-9]*::?*INSTR"
		Serial            "ASRL[0-9]*::?*INSTR"
		PXI               "PXI?*INSTR"
		All instruments   "?*INSTR"
		All resources     "?*"
	*/
	status = viFindRsrc(defaultRM, "?*INSTR", &findList, &numInstrs, instrDescriptor);
	if (status < VI_SUCCESS)
	{
		printf("An error occurred while finding resources.\nHit enter to continue.");
		fflush(stdin);
		getchar();
		viClose(defaultRM);
		return status;
	}

	printf("%d instruments, serial ports, and other resources found:\n\n", numInstrs);
	printf("%s \n", instrDescriptor);
	list.push_back(instrDescriptor);
	/* Now we will open a session to the instrument we just found. */
	status = viOpen(defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
	if (status < VI_SUCCESS)
	{
		printf("An error occurred opening a session to %s\n", instrDescriptor);
	}
	else
	{
		/* Now close the session we just opened.                            */
		/* In actuality, we would probably use an attribute to determine    */
		/* if this is the instrument we are looking for.                    */
		viClose(instr);
	}

	while (--numInstrs)
	{
		/* stay in this loop until we find all instruments */
		status = viFindNext(findList, instrDescriptor);  /* find next desriptor */
		if (status < VI_SUCCESS)
		{   /* did we find the next resource? */
			printf("An error occurred finding the next resource.\nHit enter to continue.");
			fflush(stdin);
			getchar();
			viClose(defaultRM);
			return status;
		}
		printf("%s \n", instrDescriptor);
		list.push_back(instrDescriptor);
		/* Now we will open a session to the instrument we just found */
		status = viOpen(defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
		if (status < VI_SUCCESS)
		{
			printf("An error occurred opening a session to %s\n", instrDescriptor);
		}
		else
		{
			/* Now close the session we just opened.                            */
			/* In actuality, we would probably use an attribute to determine    */
			/* if this is the instrument we are looking for.                    */
			viClose(instr);
		}
	}    /* end while */

	status = viClose(findList);
	status = viClose(defaultRM);
	printf("\nHit enter to continue.");
	fflush(stdin);
	getchar();

	return 0;
}
//刷新gpib
void GPIBSet::on_pushButton_clicked()
{
	if (!list.empty())
		list.clear();
	ui.comboBox->clear();
	findRsrc();
	ui.comboBox->addItems(list);
}

void GPIBSet::on_pushButton_2_clicked()
{
	gpib_name = ui.comboBox->currentText();
	emit send_gpib(ui.comboBox->currentText());
}
//分bin，此功能是当出现无法通信死等或者通信出错时，当不良品分
void GPIBSet::on_pushButton_3_clicked()
{
	char *name = "GPIB0::7::INSTR";
	//选择后的设备名
	//QByteArray ba = gpib_name.toLatin1();
	//name = ba.data();

	char buffer[255] = { 0 };
	status = viOpenDefaultRM(&defaultRM);
	//nReturnStatus = viOpen(rmSession, "USB::0xFFFF::0x6300::802060092746810025::INSTR", VI_NULL, VI_NULL, &pnInstrHandle);  //工厂寄家设备
	status = viOpen(defaultRM, /*instrDescriptor*//*"GPIB0::7::INSTR"*/name, VI_NULL, VI_NULL, &instr);  //工厂设备

	status = viQueryf(instr, "BINON:00000000,00000000,00000000,00002222;\r\n", "%s", buffer);
	if (status < VI_SUCCESS)
	{
		viClose(instr);
		viClose(defaultRM);
		return;
	}
	status = viPrintf(instr, "ECHOOK\n");
	if (status < VI_SUCCESS)
	{
		viClose(instr);
		viClose(defaultRM);
		return;
	}
	viClose(instr);
	viClose(defaultRM);
}
