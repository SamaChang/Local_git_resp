#include "SoftLoader.h"
#include "ui_SoftLoader.h"

#include <QFile>
#include <QIcon>
#include <QDomDocument>
#include <QDomElement>
#include <QPluginLoader>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QToolButton>
#include <QStyleOption>
#include <QPainter>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>
#include <QDebug>
#include "../common/MyInterface.h"

SoftLoader::SoftLoader(QWidget *parent)
	: QWidget(parent)
	, m_pWgt(nullptr)
{
	ui = new Ui::SoftLoader();
	ui->setupUi(this);
	this->setWindowIcon(QIcon(":/SoftLoader/Resources/logo.ico"));
	setAutoFillBackground(true);
	bool bLoad = readPluginConfig();

	initStyle();
	initForm();

	/*
	readPluginConfig();
	int nRet = loadPlugins();
	if (nRet == 0)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("软件启动失败，检查配置项"), QMessageBox::Yes);
	}
	else
	{
		if (m_pWgt)
		{
			int nWid = m_pWgt->width();
			int nHei = m_pWgt->height();
			this->resize(nWid, nHei);
			QHBoxLayout boxLayout;
			boxLayout.addWidget(m_pWgt);
			boxLayout.setMargin(0);
			this->setLayout(&boxLayout);
			setWindowTitle(m_strName);
		}
	}
	*/
	ui->stackedWidget->setCurrentIndex(0);
}

SoftLoader::~SoftLoader()
{
	delete ui;
}

void SoftLoader::initStyle()
{
	m_mousePressed = false;
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
	QString strQSS = QString("QWidget#mainPage{border-image:url(:/SoftLoader/Resources/main3.jpg);} ");
	strQSS += QString("QToolButton{color:#E7ECF0;background-color:rgba(0,0,0,0);border-style:none;}");
	this->setStyleSheet(strQSS);

	connect(ui->tbtn_min, &QToolButton::clicked, this, &SoftLoader::slot_btn_mined);
	connect(ui->tbtn_normal, &QToolButton::clicked, this, &SoftLoader::slot_btn_normal);
	connect(ui->tbtn_close, &QToolButton::clicked, this, &SoftLoader::slot_btn_close);
	connect(ui->tbtn_help, &QToolButton::clicked, this, &SoftLoader::slot_btn_help);
}

void SoftLoader::initForm()
{
	ui->lab_title_icon->setPixmap(QPixmap(":/SoftLoader/Resources/logo.png"));
	QGridLayout* mainLayout = new QGridLayout(ui->mainPage);
	
	int nCount = m_vecPlugin.count();
	
	for (int i=0; i<nCount; ++i)
	{
		QToolButton* pToolBtn = new QToolButton(this);
		pToolBtn->setFixedSize(180, 180);
		pToolBtn->setIconSize(QSize(150, 150));
		pToolBtn->setIcon(QIcon(":/SoftLoader/Resources/tool.png"));
		pToolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		pToolBtn->setText(m_vecPlugin.at(i).softName);
		pToolBtn->setProperty("pluginName", m_vecPlugin.at(i).pluginName);
		mainLayout->addWidget(pToolBtn, i / 2, (i-(i/2)*2) % 3, 1, 1, Qt::AlignCenter);
		connect(pToolBtn, &QToolButton::clicked, this, &SoftLoader::slot_btn);
	}
}

bool SoftLoader::readPluginConfig()
{
	QVector<PluginStu>().swap(m_vecPlugin);
	bool bFlag = false;
	QString strSysConfigFileName = qApp->applicationDirPath();
	strSysConfigFileName += "/config/cong_plugin.xml";
	QFile xmlFile(strSysConfigFileName);
	if (xmlFile.open(QFile::ReadOnly))
	{
		QDomDocument docXml;
		if (docXml.setContent(&xmlFile))
		{
			QDomElement xmlRoot = docXml.documentElement();
			QDomNodeList nodeList = xmlRoot.childNodes();

			int nCount = nodeList.count();
			for (int i = 1; i < nodeList.count(); ++i)
			{
				QDomElement subNodeElement = nodeList.at(i).toElement();
				if (subNodeElement.hasAttribute("pluginName"))
				{
					//qDebug() << "id<<<" << subNodeElement.attribute("id") << ">>> pluginName<<<" << subNodeElement.attribute("pluginName") << ">>> bLoad<<<" << subNodeElement.attribute("bLoad")<<">>>";
					PluginStu temp;
					temp.nID = subNodeElement.attribute("id").toInt();
					temp.pluginName = subNodeElement.attribute("pluginName");
					temp.softName = subNodeElement.attribute("softName");
					temp.bLoad = subNodeElement.attribute("bLoad").toInt() > 0 ? true : false;
					m_vecPlugin.push_back(temp);
					bFlag = true;
				}
			}
		}
		xmlFile.close();
	}
	return bFlag;
}

int SoftLoader::loadPlugins()
{
	QString strPath = qApp->applicationDirPath();
	strPath += "/Plugin/";
	for (int i=0; i<m_vecPlugin.count(); ++i)
	{
		QString strPlugin = strPath + m_vecPlugin.at(i).pluginName;
		if (m_vecPlugin.at(i).bLoad)
		{
			QPluginLoader pluginLoader(strPlugin);
			if (pluginLoader.load())
			{
				QObject* pluginObj = pluginLoader.instance();
				if (pluginObj)
				{
					MyInterface* pInterface = qobject_cast<MyInterface*>(pluginObj);
					if (pInterface)
					{
						m_pWgt = pInterface->createWidget(this);
						m_strName = pInterface->getPluginName();
						return 1;
					}
				}
			}
			else
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("加载程序失败，%1").arg(pluginLoader.errorString()), QMessageBox::Yes);
			}
		}
	}
	return 0;
}

bool SoftLoader::loadPlugin(QString strPluginName)
{
	QString strPath = qApp->applicationDirPath();
	strPath += "/Plugin/";
	QString strPlugin = strPath + strPluginName;
	QPluginLoader pluginLoader(strPlugin);
	if (pluginLoader.load())
	{
		QObject* pluginObj = pluginLoader.instance();
		if (pluginObj)
		{
			MyInterface* pInterface = qobject_cast<MyInterface*>(pluginObj);
			if (pInterface)
			{
				m_pWgt = pInterface->createWidget(this);
				m_strName = pInterface->getPluginName();
				return 1;
			}
		}
	}
	else
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("加载程序失败，%1").arg(pluginLoader.errorString()), QMessageBox::Yes);
	}
}

void SoftLoader::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	int nWidth = this->width();
	int nHeight = this->height();
	if (m_pWgt)
	{
		m_pWgt->resize(this->width(), nHeight-65);
	}
}

void SoftLoader::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_mousePressed = true;
		m_mousePoint = event->globalPos() - this->pos();
		event->accept();
	}
}

void SoftLoader::mouseMoveEvent(QMouseEvent *event)
{
	if (m_mousePressed && (event->buttons() && Qt::LeftButton))
	{
		this->move(event->globalPos() - m_mousePoint);
		event->accept();
	}
}

void SoftLoader::mouseReleaseEvent(QMouseEvent *event)
{
	m_mousePressed = false;
}

/*
void SoftLoader::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
*/

void SoftLoader::slot_btn()
{
	
	QObject *pObj = sender();
	QToolButton* pBtn = qobject_cast<QToolButton*>(sender());
	if (pBtn)
	{
		//pToolBtn->setProperty("pluginName", m_vecPlugin.at(i).pluginName);
		QString strPluginName = pBtn->property("pluginName").toString();

		bool bCanUse = false;
		//检查工具是否可以被使用
		for (int i = 0; i < m_vecPlugin.count(); i++)
		{
			if (strPluginName == m_vecPlugin.at(i).pluginName && m_vecPlugin.at(i).bLoad)
			{
				bCanUse = true;
				break;
			}
		}
		if (bCanUse)
		{
			bool bRet = loadPlugin(strPluginName);
			if (bRet)
			{
				m_strPdfFile = strPluginName.left(strPluginName.length() - 4);
				ui->stackedWidget->setCurrentIndex(1);
				int nWid = m_pWgt->width();
				int nHei = m_pWgt->height();
				this->resize(nWid, nHei);
				QHBoxLayout boxLayout;
				boxLayout.addWidget(m_pWgt);
				boxLayout.setMargin(0);
				ui->pluginPage->setLayout(&boxLayout);
				ui->lab_title->setText(m_strName);
				//setWindowTitle(m_strName);
				this->showMaximized();
			}
			else
			{
				QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("当前工具故障不可用"), QMessageBox::Yes);
			}
		}
		else
		{
			QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("当前工具设置为不可用，请联系相关人员，获取响应权限软件"), QMessageBox::Yes);
		}
	}
	
}

void SoftLoader::slot_btn_mined()
{
	this->showMinimized();
}

void SoftLoader::slot_btn_normal()
{
	if (isMaximized())
	{
		this->showNormal();
	}
	else
	{
		this->showMaximized();
	}
}

void SoftLoader::slot_btn_close()
{
	this->close();
}

void SoftLoader::slot_btn_help()
{
	if (m_strPdfFile.isEmpty())
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("当前无可查看操作手册"), QMessageBox::Yes);
	}
	else
	{
		QString strHelpFile = qApp->applicationDirPath();
		//strHelpFile += "/config/HelpFile/ANC_help.pdf";
		strHelpFile += "/config/HelpFile/";
		strHelpFile += m_strPdfFile;
		strHelpFile += ".pdf";
		//QProcess *process = new QProcess;
		//process->start("hh.exe",QStringList(strHelpFile));
		QDesktopServices::openUrl(QUrl::fromLocalFile(strHelpFile));
	}
}
