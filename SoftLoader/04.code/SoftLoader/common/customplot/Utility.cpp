#include <QAudioFormat>
#include "Utility.h"

qint64 audioDuration(const QAudioFormat & format, qint64 bytes)
{
	//΢��
	return (bytes * 1000000) / (format.sampleRate()*format.channelCount()*(format.sampleSize() / 8));
}

qint64 audioLength(const QAudioFormat & format, qint64 microSeconds)
{
	//microSeconds�������ô����ɼ����ַ�����С
	qDebug() << "sampleRate" << format.sampleRate() << "channelCount()" << format.channelCount() << "sampleSize()" << format.sampleSize();
	qint64 result = (format.sampleRate()*format.channelCount()*(format.sampleSize() / 8))*microSeconds / 1000000;
	result -= result % (format.channelCount() * format.sampleSize());	//ȡ����������ֵ
	return result;
}

qreal nyquist(const QAudioFormat & format)
{
	return format.sampleRate() / 2;
}

QString formatToString(const QAudioFormat & format)
{
	QString result = "UNKNOWN";
	if (QAudioFormat() != format)
	{
		if (format.codec() == "audio/pcm")
		{
			Q_ASSERT(format.sampleType() == QAudioFormat::SignedInt);
			const QString formatEndian = (format.byteOrder() == QAudioFormat::LittleEndian) ? QString("LE") : QString("BE");
			QString formatType;
			switch (format.sampleType())
			{
			case QAudioFormat::SignedInt:
				formatType = "signed";
				break;
			case QAudioFormat::UnSignedInt:
				formatType = "unsigned";
				break;
			case QAudioFormat::Float:
				formatType = "float";
				break;
			default:
				formatType = "unknown";
				break;
			}
			QString formatChannels;	//QString("%1 channels").arg(format.channelCount());
			if (format.channelCount() == 1)	//������
			{
				formatChannels = "mono";	//������
			}
			else if (format.channelCount() == 2)		//������
			{
				formatChannels = "stereo";	//������
			}
			else
			{
				formatChannels = "unknown";		//δ֪
			}
			result = QString("%1 Hz %2 bit %3 %4 %5")
				.arg(format.sampleRate())
				.arg(format.sampleSize())
				.arg(formatType)
				.arg(formatEndian)
				.arg(formatChannels);
		}
		else
		{
			result = format.codec();
		}
	}
	return result;
}

bool isPCM(const QAudioFormat & format)
{
	return (format.codec() == "audio/pcm");
}

bool isPCMS16LE(const QAudioFormat & format)
{
	return isPCM(format) && format.sampleType() == QAudioFormat::SignedInt && format.sampleSize() == 16 && format.byteOrder() == QAudioFormat::LittleEndian;
}

const qint16 PCMS16MAXValue		= 32767;		//16λPCM�����ֵ 
const quint16 PCMS16MaxAmplitude = 32768;		//16λPCM��������

qreal pcmToReal(qint16 pcm)
{
	return qreal(pcm) / PCMS16MaxAmplitude;
}

qint16 realToPcm(qreal real)
{
	return int(real*PCMS16MAXValue);
}

