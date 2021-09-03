#pragma once

#include <QFile>
#include <QAudioFormat>

class WavFile : public QFile
{
public:
	WavFile(QObject *parent = nullptr);
	~WavFile();

	bool open(const QString & fileName);
	const QAudioFormat & fileFormat() const;
	qint64 headerLength() const;

private:
	bool readHeader();

private:
	QAudioFormat m_fileFormat;
	qint64 m_headerLength;
};
