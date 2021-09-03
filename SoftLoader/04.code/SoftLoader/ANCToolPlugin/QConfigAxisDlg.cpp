#include "QConfigAxisDlg.h"
#include "Config.h"

QConfigAxisDlg::QConfigAxisDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	AXIS_STRUCT & axis_fr = Config::getIns()->m_fr_chart_axis;
	ui.fr_doubleSpinBox_min_x->setValue(axis_fr.nMin_x);
	ui.fr_doubleSpinBox_max_x->setValue(axis_fr.nMax_x);
	ui.fr_doubleSpinBox_min_y->setValue(axis_fr.nMin_y);
	ui.fr_doubleSpinBox_max_y->setValue(axis_fr.nMax_y);

	AXIS_STRUCT & axis_phase = Config::getIns()->m_phase_chart_axis;
	ui.phase_doubleSpinBox_min_x->setValue(axis_phase.nMin_x);
	ui.phase_doubleSpinBox_max_x->setValue(axis_phase.nMax_x);
	ui.phase_doubleSpinBox_min_y->setValue(axis_phase.nMin_y);
	ui.phase_doubleSpinBox_max_y->setValue(axis_phase.nMax_y);


	connect(ui.pushButton, &QPushButton::clicked, [this]{
		
		AXIS_STRUCT & axis_fr = Config::getIns()->m_fr_chart_axis;
		axis_fr.nMin_x = ui.fr_doubleSpinBox_min_x->text().toDouble();
		axis_fr.nMax_x = ui.fr_doubleSpinBox_max_x->text().toDouble();
		axis_fr.nMin_y = ui.fr_doubleSpinBox_min_y->text().toDouble();
		axis_fr.nMax_y = ui.fr_doubleSpinBox_max_y->text().toDouble();

		AXIS_STRUCT & axis_phase = Config::getIns()->m_phase_chart_axis;
		axis_phase.nMin_x = ui.phase_doubleSpinBox_min_x->text().toDouble();
		axis_phase.nMax_x = ui.phase_doubleSpinBox_max_x->text().toDouble();
		axis_phase.nMin_y = ui.phase_doubleSpinBox_min_y->text().toDouble();
		axis_phase.nMax_y = ui.phase_doubleSpinBox_max_y->text().toDouble();

		this->accept();
	});

	connect(ui.pushButton_2, &QPushButton::clicked, [this] {
		this->reject();
	});

}

QConfigAxisDlg::~QConfigAxisDlg()
{
}


