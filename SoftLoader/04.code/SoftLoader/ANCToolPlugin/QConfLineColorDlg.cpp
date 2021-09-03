#include "QConfLineColorDlg.h"


#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

QConfLineColorDlg::QConfLineColorDlg(int nType, QWidget *parent)
	: QDialog(parent)
	, m_nType(nType)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, this, &QConfLineColorDlg::slot_btn_ok);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &QConfLineColorDlg::slot_btn_cancel);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &QConfLineColorDlg::slot_btn_default);

	connect(ui.tbtn_load_line,   &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_load);
	connect(ui.tbtn_load_line_2, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_load);
	connect(ui.tbtn_load_line_3, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_load);
	connect(ui.tbtn_load_line_4, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_load);
	connect(ui.tbtn_load_line_5, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_load);
	connect(ui.tbtn_load_line_6, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_load);

	connect(ui.tbtn_save_line,  &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_save);
	connect(ui.tbtn_save_line_2, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_save);
	connect(ui.tbtn_save_line_3, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_save);
	connect(ui.tbtn_save_line_4, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_save);
	connect(ui.tbtn_save_line_5, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_save);
	connect(ui.tbtn_save_line_6, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_save);

	connect(ui.tbtn_color_line,   &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_set_color);
	connect(ui.tbtn_color_line_2, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_set_color);
	connect(ui.tbtn_color_line_3, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_set_color);
	connect(ui.tbtn_color_line_4, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_set_color);
	connect(ui.tbtn_color_line_5, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_set_color);
	connect(ui.tbtn_color_line_6, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_set_color);
	connect(ui.tbtn_color_line_7, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_set_color);
	connect(ui.tbtn_color_line_8, &QToolButton::clicked, this, &QConfLineColorDlg::slot_tbtn_set_color);

	if (m_nType == WAVE_CHART_FR)
	{
		WAVE_LINE_VEC & vecConf = Config::getIns()->getFrLinesConf();
		initUIShow(vecConf);
	}
	else if (m_nType == WAVE_CHART_PHASE)
	{
		WAVE_LINE_VEC & vecConf = Config::getIns()->getPhaseLinesConf();
		initUIShow(vecConf);
	}
}

QConfLineColorDlg::~QConfLineColorDlg()
{

}

void QConfLineColorDlg::initUIShow(const WAVE_LINE_VEC & vecConf)
{
	ui.edt_name_line->setText(vecConf[0].name);
	ui.edt_path_line->setText(vecConf[0].path);
	ui.tbtn_color_line->setStyleSheet(QString("background-color:%1").arg(vecConf[0].clr));

	ui.edt_name_line_2->setText(vecConf[1].name);
	ui.edt_path_line_2->setText(vecConf[1].path);
	ui.tbtn_color_line_2->setStyleSheet(QString("background-color:%1").arg(vecConf[1].clr));

	ui.edt_name_line_3->setText(vecConf[2].name);
	ui.edt_path_line_3->setText(vecConf[2].path);
	ui.tbtn_color_line_3->setStyleSheet(QString("background-color:%1").arg(vecConf[2].clr));

	ui.edt_name_line_4->setText(vecConf[3].name);
	ui.edt_path_line_4->setText(vecConf[3].path);
	ui.tbtn_color_line_4->setStyleSheet(QString("background-color:%1").arg(vecConf[3].clr));

	ui.edt_name_line_5->setText(vecConf[4].name);
	ui.edt_path_line_5->setText(vecConf[4].path);
	ui.tbtn_color_line_5->setStyleSheet(QString("background-color:%1").arg(vecConf[4].clr));

	ui.edt_name_line_6->setText(vecConf[5].name);
	ui.edt_path_line_6->setText(vecConf[5].path);
	ui.tbtn_color_line_6->setStyleSheet(QString("background-color:%1").arg(vecConf[5].clr));

	ui.edt_name_line_7->setText(vecConf[6].name);
	ui.tbtn_color_line_7->setStyleSheet(QString("background-color:%1").arg(vecConf[6].clr));

	ui.edt_name_line_8->setText(vecConf[7].name);
	ui.tbtn_color_line_8->setStyleSheet(QString("background-color:%1").arg(vecConf[7].clr));

	ui.tbtn_color_line->setProperty("line_color", vecConf[0].clr);
	ui.tbtn_color_line_2->setProperty("line_color", vecConf[1].clr);
	ui.tbtn_color_line_3->setProperty("line_color", vecConf[2].clr);
	ui.tbtn_color_line_4->setProperty("line_color", vecConf[3].clr);
	ui.tbtn_color_line_5->setProperty("line_color", vecConf[4].clr);
	ui.tbtn_color_line_6->setProperty("line_color", vecConf[5].clr);
	ui.tbtn_color_line_7->setProperty("line_color", vecConf[6].clr);
	ui.tbtn_color_line_8->setProperty("line_color", vecConf[7].clr);
}

void QConfLineColorDlg::loadData(int nIndex, QString strPath)
{
	if (nIndex < 1)
	{
		return;
	}
	
	QFile *loadFile = new QFile(strPath);
	bool bOpen = loadFile->open(QIODevice::ReadOnly | QIODevice::Text);
	if (!bOpen)
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("打开文件失败，请检查路径配置文件是否存在"), QMessageBox::Yes);
		return;
	}
	int nPos = 0;

	if (m_nType == WAVE_CHART_FR)
	{
		//数据初始化
		FrequencySpectrum& spectrumData = Config::getIns()->m_fr_chart_data[nIndex - 1];
		spectrumData.reset();

		while (!loadFile->atEnd())
		{
			FrequencySpectrum::Element element;
			QByteArray line = loadFile->readLine();
			QString temp = line;
			QStringList sss = temp.split("\t");
			if (sss.size() == 2)
			{
				element.frequency = sss.at(0).toDouble();
				element.amplitude = sss.at(1).toDouble();
			}
			else if (sss.size() == 3)
			{
				element.frequency = sss.at(0).toDouble();
				element.amplitude = sss.at(1).toDouble();
				element.phase = sss.at(2).toDouble();
			}
			spectrumData.push_back(element);
			++nPos;
		}
	}
	else if (m_nType == WAVE_CHART_PHASE)
	{
		//数据初始化
		FrequencySpectrum& spectrumData = Config::getIns()->m_phase_chart_data[nIndex - 1];
		spectrumData.reset();

		while (!loadFile->atEnd())
		{
			FrequencySpectrum::Element element;
			QByteArray line = loadFile->readLine();
			QString temp = line;
			QStringList sss = temp.split("\t");
			if (sss.size() == 2)
			{
				element.frequency = sss.at(0).toDouble();
				element.amplitude = sss.at(1).toDouble();
			}
			else if (sss.size() == 3)
			{
				element.frequency = sss.at(0).toDouble();
				element.amplitude = sss.at(1).toDouble();
				element.phase = sss.at(2).toDouble();
			}
			spectrumData.push_back(element);
			++nPos;
		}
	}
	
	loadFile->close();
	delete loadFile;
	loadFile = nullptr;

}

void QConfLineColorDlg::saveData(int nIndex, QString strPath)
{
	if (nIndex < 1)
	{
		return;
	}
	//数据存储
	FrequencySpectrum& spectrumData = Config::getIns()->m_fr_chart_data[nIndex - 1];

	QFile *saveFile = new QFile(strPath);
	saveFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
	QTextStream out(saveFile);
	for (int i = 0; i < spectrumData.count(); ++i)
	{
		out << spectrumData[i].frequency << "\t" << spectrumData[i].amplitude << "\t" << spectrumData[i].phase << "\n";
	}
	saveFile->close();
	delete saveFile;
	saveFile = nullptr;
	QMessageBox::information(this, QStringLiteral("保存文件"), QStringLiteral("文件保存成功！！！"), QMessageBox::Yes);
}

void QConfLineColorDlg::slot_btn_ok()
{
	if (m_nType == WAVE_CHART_FR)
	{
		WAVE_LINE_VEC & vecConf = Config::getIns()->getFrLinesConf();
		//第一条
		QString strLinePath = ui.edt_name_line->text();

		vecConf[0].name = ui.edt_name_line->text();
		vecConf[0].path = ui.edt_path_line->text();
		vecConf[0].clr = ui.tbtn_color_line->property("line_color").toString();

		vecConf[1].name = ui.edt_name_line_2->text();
		vecConf[1].path = ui.edt_path_line_2->text();
		vecConf[1].clr = ui.tbtn_color_line_2->property("line_color").toString();

		vecConf[2].name = ui.edt_name_line_3->text();
		vecConf[2].path = ui.edt_path_line_3->text();
		vecConf[2].clr = ui.tbtn_color_line_3->property("line_color").toString();

		vecConf[3].name = ui.edt_name_line_4->text();
		vecConf[3].path = ui.edt_path_line_4->text();
		vecConf[3].clr = ui.tbtn_color_line_4->property("line_color").toString();

		vecConf[4].name = ui.edt_name_line_5->text();
		vecConf[4].path = ui.edt_path_line_5->text();
		vecConf[4].clr = ui.tbtn_color_line_5->property("line_color").toString();

		vecConf[5].name = ui.edt_name_line_6->text();
		vecConf[5].path = ui.edt_path_line_6->text();
		vecConf[5].clr = ui.tbtn_color_line_6->property("line_color").toString();

		//vecConf[6].name = ui.edt_name_line_7->text();
		vecConf[6].clr = ui.tbtn_color_line_7->property("line_color").toString();

		//vecConf[7].name = ui.edt_name_line_7->text();
		vecConf[7].clr = ui.tbtn_color_line_8->property("line_color").toString();
	}
	else if (m_nType == WAVE_CHART_PHASE)
	{
		WAVE_LINE_VEC & vecConf = Config::getIns()->getPhaseLinesConf();
		//第一条
		QString strLinePath = ui.edt_name_line->text();

		vecConf[0].name = ui.edt_name_line->text();
		vecConf[0].path = ui.edt_path_line->text();
		vecConf[0].clr = ui.tbtn_color_line->property("line_color").toString();

		vecConf[1].name = ui.edt_name_line_2->text();
		vecConf[1].path = ui.edt_path_line_2->text();
		vecConf[1].clr = ui.tbtn_color_line_2->property("line_color").toString();

		vecConf[2].name = ui.edt_name_line_3->text();
		vecConf[2].path = ui.edt_path_line_3->text();
		vecConf[2].clr = ui.tbtn_color_line_3->property("line_color").toString();

		vecConf[3].name = ui.edt_name_line_4->text();
		vecConf[3].path = ui.edt_path_line_4->text();
		vecConf[3].clr = ui.tbtn_color_line_4->property("line_color").toString();

		vecConf[4].name = ui.edt_name_line_5->text();
		vecConf[4].path = ui.edt_path_line_5->text();
		vecConf[4].clr = ui.tbtn_color_line_5->property("line_color").toString();

		vecConf[5].name = ui.edt_name_line_6->text();
		vecConf[5].path = ui.edt_path_line_6->text();
		vecConf[5].clr = ui.tbtn_color_line_6->property("line_color").toString();

		//vecConf[6].name = ui.edt_name_line_7->text();
		vecConf[6].clr = ui.tbtn_color_line_7->property("line_color").toString();

		//vecConf[7].name = ui.edt_name_line_7->text();
		vecConf[7].clr = ui.tbtn_color_line_8->property("line_color").toString();
	}
	this->accept();
}

void QConfLineColorDlg::slot_btn_cancel()
{
	this->reject();
}

void QConfLineColorDlg::slot_btn_default()
{
	if (m_nType == WAVE_CHART_FR)
	{
		//WAVE_LINE_VEC & vecConf = Config::getIns()->getFrLinesConf();
		ui.tbtn_color_line->setStyleSheet(QString("background-color:%1").arg(LineColors[0]));
		ui.tbtn_color_line_2->setStyleSheet(QString("background-color:%1").arg(LineColors[1]));
		ui.tbtn_color_line_3->setStyleSheet(QString("background-color:%1").arg(LineColors[2]));
		ui.tbtn_color_line_4->setStyleSheet(QString("background-color:%1").arg(LineColors[3]));
		ui.tbtn_color_line_5->setStyleSheet(QString("background-color:%1").arg(LineColors[4]));
		ui.tbtn_color_line_6->setStyleSheet(QString("background-color:%1").arg(LineColors[5]));
		ui.tbtn_color_line_7->setStyleSheet(QString("background-color:%1").arg(LineColors[6]));
		ui.tbtn_color_line_8->setStyleSheet(QString("background-color:%1").arg(LineColors[7]));
	}
	else if (m_nType == WAVE_CHART_PHASE)
	{
		//WAVE_LINE_VEC & vecConf = Config::getIns()->getPhaseLinesConf();
		ui.tbtn_color_line->setStyleSheet(QString("background-color:%1").arg(LineColors[0]));
		ui.tbtn_color_line_2->setStyleSheet(QString("background-color:%1").arg(LineColors[1]));
		ui.tbtn_color_line_3->setStyleSheet(QString("background-color:%1").arg(LineColors[2]));
		ui.tbtn_color_line_4->setStyleSheet(QString("background-color:%1").arg(LineColors[3]));
		ui.tbtn_color_line_5->setStyleSheet(QString("background-color:%1").arg(LineColors[4]));
		ui.tbtn_color_line_6->setStyleSheet(QString("background-color:%1").arg(LineColors[5]));
		ui.tbtn_color_line_7->setStyleSheet(QString("background-color:%1").arg(LineColors[6]));
		ui.tbtn_color_line_8->setStyleSheet(QString("background-color:%1").arg(LineColors[7]));
	}
	
}

void QConfLineColorDlg::slot_tbtn_set_color()
{
	QToolButton* pColorBtn = qobject_cast<QToolButton*>(sender());
	if (pColorBtn)
	{
		QColor color = QColorDialog::getColor(Qt::red, this, QStringLiteral("颜色对话框"), QColorDialog::ShowAlphaChannel);
		QString strColor = color.name(QColor::HexRgb);
		pColorBtn->setStyleSheet(QString("background-color:%1").arg(strColor));
		pColorBtn->setProperty("line_color", strColor);
	}
	
}

void QConfLineColorDlg::slot_tbtn_load()
{
	QToolButton* pLoadBtn = qobject_cast<QToolButton*>(sender());
	if (pLoadBtn)
	{
		QString strApp = QApplication::applicationDirPath() + "/WaveFiles";
		QString strPath = QFileDialog::getOpenFileName(this, QStringLiteral("加载文件"), strApp, QString("Datas (*.txt *.txt )"));
		if (!strPath.isEmpty())
		{
			int nIndex = -1;
			if (pLoadBtn == ui.tbtn_load_line)
			{
				ui.edt_path_line->setText(strPath);
				nIndex = 1;
			}
			else if(pLoadBtn == ui.tbtn_load_line_2)
			{
				ui.edt_path_line_2->setText(strPath);
				nIndex = 2;
			}
			else if (pLoadBtn == ui.tbtn_load_line_3)
			{
				ui.edt_path_line_3->setText(strPath);
				nIndex = 3;
			}
			else if (pLoadBtn == ui.tbtn_load_line_4)
			{
				ui.edt_path_line_4->setText(strPath);
				nIndex = 4;
			}
			else if (pLoadBtn == ui.tbtn_load_line_5)
			{
				ui.edt_path_line_5->setText(strPath);
				nIndex = 5;
			}
			else if (pLoadBtn == ui.tbtn_load_line_6)
			{
				ui.edt_path_line_6->setText(strPath);
				nIndex = 6;
			}
			loadData(nIndex, strPath);
		}
	}
}

void QConfLineColorDlg::slot_tbtn_save()
{
	QToolButton* pSaveBtn = qobject_cast<QToolButton*>(sender());
	if (pSaveBtn)
	{
		QString strPath = QFileDialog::getSaveFileName(this, tr("Save File"), QString("D://"), tr("Data TEXT (*.txt *.txt)"));
		if (strPath.isEmpty())
		{
			QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("请设置你要保存的文件路径"));
		}
		else
		{
			int nIndex = -1;
			if (pSaveBtn == ui.tbtn_save_line)
			{
				nIndex = 1;
			}
			else if (pSaveBtn == ui.tbtn_save_line_2)
			{
				nIndex = 2;
			}
			else if (pSaveBtn == ui.tbtn_save_line_3)
			{
				nIndex = 3;
			}
			else if (pSaveBtn == ui.tbtn_save_line_4)
			{
				nIndex = 4;
			}
			else if (pSaveBtn == ui.tbtn_save_line_5)
			{
				nIndex = 5;
			}
			else if (pSaveBtn == ui.tbtn_save_line_6)
			{
				nIndex = 6;
			}
			saveData(nIndex, strPath);
		}
	}
}
