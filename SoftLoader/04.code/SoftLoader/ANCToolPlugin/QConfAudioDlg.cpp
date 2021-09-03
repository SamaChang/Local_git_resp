#include "QConfAudioDlg.h"
#include "Config.h"

QConfAudioDlg::QConfAudioDlg(QWidget *parent /*= Q_NULLPTR*/)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.comboBox->setCurrentText(QString::number(Config::getIns()->m_sys_freqRate));
	ui.comboBox_2->setCurrentIndex(Config::getIns()->m_sys_channel - 1);

	connect(ui.pushButton, &QPushButton::clicked, [this] {
		Config::getIns()->m_sys_freqRate = ui.comboBox->currentText().toInt();
		Config::getIns()->m_sys_channel = ui.comboBox_2->currentIndex() + 1;
		Config::getIns()->m_nPowerOfTwo = ui.spinBox->value();
		Config::getIns()->m_sys_dB = ui.spinBox_2->value();
		this->accept();

		//±£´æÅäÖÃ
		Config::getIns()->writeCommonJson();
	});

	connect(ui.pushButton_2, &QPushButton::clicked, [this] {
		this->reject();
	});
}

QConfAudioDlg::~QConfAudioDlg()
{
}

