#pragma once

#include <QLineEdit>

class QMacLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	QMacLineEdit(QWidget *parent);
	~QMacLineEdit();
	
private slots:
	void slot_text_changed(const QString &text);
};
