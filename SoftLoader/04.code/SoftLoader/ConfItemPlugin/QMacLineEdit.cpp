#include "QMacLineEdit.h"
#include <QRegExpValidator>

QMacLineEdit::QMacLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	connect(this, &QMacLineEdit::textChanged, this, &QMacLineEdit::slot_text_changed);
}

QMacLineEdit::~QMacLineEdit()
{
}

void QMacLineEdit::slot_text_changed(const QString &text)
{
	QString strTxt = text;
	QRegExp regexpMac("([0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2}:[0-9A-Fa-f]{2})");
	QRegExpValidator validator(regexpMac, this);
	int nPos = 0;
	if (QValidator::Acceptable == validator.validate(strTxt, nPos))
	{

	}
	
}
