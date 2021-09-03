#include "ProductTest_360.h"
#include "packet.h"

ProductTest_360::ProductTest_360(QWidget *parent)
    : QWidget(parent),product(nullptr), snInformation(nullptr)
{
    ui.setupUi(this);
	this->setWindowFlags(Qt::WindowCloseButtonHint);
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(mainTest()));
	//product = new ChoosePro();
	//connect(product, SIGNAL(testForm()), this, SLOT(showMainForm()));
	buttonStyle(ui.pushButton, "./Button.qss");
	buttonStyle(ui.pushButton_2, "./Button.qss");
	buttonStyle(ui.pushButton_3, "./Button.qss");
	this->setWindowIcon(QIcon("./Logo.png"));
	//devices.push_back("360飓风门禁");
	ui.comboBox->addItem(QString::fromLocal8Bit("360飓风门禁"));
	ui.comboBox->addItem(QString::fromLocal8Bit("TX510小门禁"));
}

ProductTest_360::~ProductTest_360()
{
	delete product;
	delete snInformation;
}
//全局测试
void ProductTest_360::mainTest()
{
	this->hide();
	if (ui.comboBox->currentIndex() == 0)
	{
		product = new ChoosePro();
		connect(product, SIGNAL(testForm()), this, SLOT(showMainForm()));
		product->show();
	}
}
//SN信息读取
void ProductTest_360::on_pushButton_clicked()
{
	this->hide();
	snInformation = new SNInformation();
	connect(snInformation, SIGNAL(testForms()), this, SLOT(showMainForm()));
	snInformation->show();
}

void ProductTest_360::showMainForm()
{
	//product->close();
	this->show();
}
