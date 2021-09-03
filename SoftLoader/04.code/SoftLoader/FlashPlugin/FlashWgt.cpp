#include "FlashWgt.h"
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include "CheckAvailablePort.h"

FlashWgt::FlashWgt(QWidget *parent)
	: QWidget(parent)
	, m_n_second_bin_length(0)
	, m_pCheckAvailablePort(new CheckAvailablePort(this))
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/Img/Resources/logo.ico"));		//设置程序图标
	setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
	qRegisterMetaType<BURN_STATE>("BURN_STATE");

	m_vec_p_singleWgt.push_back(SINGLEWGT(ui.singleWgt_1));
	m_vec_p_singleWgt.push_back(SINGLEWGT(ui.singleWgt_2));
	m_vec_p_singleWgt.push_back(SINGLEWGT(ui.singleWgt_3));
	m_vec_p_singleWgt.push_back(SINGLEWGT(ui.singleWgt_4));
	m_vec_p_singleWgt.push_back(SINGLEWGT(ui.singleWgt_5));
	m_vec_p_singleWgt.push_back(SINGLEWGT(ui.singleWgt_6));
	m_vec_p_singleWgt.push_back(SINGLEWGT(ui.singleWgt_7));
	m_vec_p_singleWgt.push_back(SINGLEWGT(ui.singleWgt_8));

	//程序启动时判断是否可以加载第一个bin文件，如果不可以，做相应的提示
	//bool bLoad = loadFirstBin();
	//if (!bLoad)
	//{
	//	QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("加载初始化文件失败，请检查相应路径文件"), QMessageBox::Yes);
	//	return;
	//}
	connect(m_pCheckAvailablePort, &CheckAvailablePort::sig_available_port, this, &FlashWgt::slot_available_port);
}

FlashWgt::~FlashWgt()
{
}

void FlashWgt::slot_available_port(QString strCom)
{
	for (int i = 0; i < m_vec_p_singleWgt.size(); ++i)
	{
		SINGLEWGT &stuSingleWgt = m_vec_p_singleWgt[i];
		if (!stuSingleWgt.bLoad)
		{
			bool bBind = stuSingleWgt.pWgt->bindPort(strCom);
			if (bBind)
			{
				stuSingleWgt.bLoad = true;
				stuSingleWgt.pWgt->setProcessState(1);
				stuSingleWgt.pWgt->setFirstBin(m_array_first_bin);
				stuSingleWgt.pWgt->setSecondBin(m_array_second_bin, m_n_second_bin_length);
				qDebug() << "bind---------------------------------" << strCom;
				break;
			}
		}
	}
}

void FlashWgt::on_pushButton_1_clicked()
{
	QString fileNamePath = qApp->applicationDirPath();
	fileNamePath += "/data";		//文件路径
	QString strPath = QFileDialog::getOpenFileName(this, QStringLiteral("选择文件"), fileNamePath, "(*.bin);;All Files(*.*)");
	if (!strPath.isEmpty())
	{
		QFile file(strPath);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			m_array_second_bin = file.readAll();
			m_n_second_bin_length = m_array_second_bin.length();
			file.close();
			qDebug() << QStringLiteral("加载bin文件成功，文件长度为：%1").arg(m_n_second_bin_length);
		}
	}
}

void FlashWgt::on_pushButton_2_clicked()
{
	for (int i=0; i<m_vec_p_singleWgt.size(); ++i)
	{
		m_vec_p_singleWgt[i].pWgt->initUI();
	}

	m_pCheckAvailablePort->checkPort();
	QVector<QString> vecStrPort = m_pCheckAvailablePort->getAvailablePort();
	int nCount = vecStrPort.size();
	if (!nCount)
		QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("当前无可用串口"), QMessageBox::Yes);
}

//烧写程序
void FlashWgt::on_pushButton_3_clicked()
{
	bool bLoad = loadFirstBin();
	if (!bLoad)
	{
		QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("加载初始化文件失败，请检查相应路径文件"), QMessageBox::Yes);
		return;
	}
	for (int i = 0; i < m_vec_p_singleWgt.size(); ++i)
	{
		SINGLEWGT &stuSingleWgt = m_vec_p_singleWgt[i];
		if (stuSingleWgt.bLoad)
		{
			stuSingleWgt.pWgt->startProcess();
			connect(stuSingleWgt.pWgt, &SingleWgt::sig_burn_finished, this, &FlashWgt::slot_burn_finished);
			qDebug() << QStringLiteral("开始自动。。。");
		}
	}
	/*
	ui.singleWgt_2->setFirstBin(m_array_first_bin);
	ui.singleWgt_2->setSecondBin(m_array_second_bin, m_n_second_bin_length);
	ui.singleWgt_2->slot_start();
	*/
}

void FlashWgt::slot_burn_finished()
{
	SingleWgt* pSingleWgt = qobject_cast<SingleWgt*>(sender());
	for (int i = 0; i < m_vec_p_singleWgt.size(); ++i)
	{
		SINGLEWGT &stuSingleWgt = m_vec_p_singleWgt[i];
		if (stuSingleWgt.bLoad && pSingleWgt == stuSingleWgt.pWgt)
		{
			stuSingleWgt.pWgt->disconnect();
			stuSingleWgt.bLoad = false;
			break;
		}
	}
}

bool FlashWgt::loadFirstBin()
{
	bool bLoad = false;
	QString fileName = qApp->applicationDirPath();
	//fileName += "/data/appotf_download_normal.bin";		//这个是231板子的bootroom
	if (ui.checkBox->isChecked())
	{
		fileName += "/data/appotf_download_normal.bin";		//加密boot
	}
	else
	{
		fileName += "/data/app_download_nosecret.bin";      //不加密boot
	}
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		m_array_first_bin = file.readAll();
		file.close();
		bLoad = true;
	}
	return bLoad;
}
