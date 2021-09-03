#include "WavFile.h"
#include <qendian.h>

#include "../common/datastruct/DataStruct_anc_eq.h"

WavFile::WavFile(QObject *parent) : QFile(parent),m_headerLength(0)
{
}

WavFile::~WavFile()
{
}

bool WavFile::open(const QString & fileName)
{
	close();
	setFileName(fileName);
	return QFile::open(QIODevice::ReadOnly) && readHeader();
}

const QAudioFormat & WavFile::fileFormat() const
{
	return m_fileFormat;
}

qint64 WavFile::headerLength() const
{
	return m_headerLength;
}

bool WavFile::readHeader()
{
	seek(0);
	WAVE_HEADER header;
	bool bResult = read(reinterpret_cast<char*>(&header), sizeof(WAVE_HEADER)) == sizeof(WAVE_HEADER);
	if (bResult)
	{
		if ((memcmp(&header.fiff_header.szRiffID, "RIFF", 4) == 0 || memcmp(&header.fiff_header.szRiffID, "RIFX", 4) == 0)
			&& memcmp(&header.fiff_header.szRiffFormat, "WAVE", 4) == 0
			&& memcmp(&header.fmt_header.szFmtID, "fmt ", 4) == 0
			&& (header.fmt_header.wavFormat.wFormatTag == 1 || header.fmt_header.wavFormat.wFormatTag == 0)
			)
		{
			//ÅÐ¶Ï´óÐ¡¶Ë×Ö½ÚÐò
			if (memcmp(&header.fiff_header.szRiffID, "RIFF", 4) == 0)
			{
				m_fileFormat.setByteOrder(QAudioFormat::LittleEndian);
			}
			else
			{
				m_fileFormat.setByteOrder(QAudioFormat::BigEndian);
			}
			int bps = qFromLittleEndian<qint16>(header.fmt_header.wavFormat.wBitsPerSample);
			m_fileFormat.setChannelCount(qFromLittleEndian<qint16>(header.fmt_header.wavFormat.wChannels));
			m_fileFormat.setCodec("audio/pcm");
			m_fileFormat.setSampleRate(qFromLittleEndian<qint32>(header.fmt_header.wavFormat.dwSamplesPerSec));
			m_fileFormat.setSampleSize(qFromLittleEndian<qint16>(header.fmt_header.wavFormat.wBitsPerSample));
			m_fileFormat.setSampleType(bps == 8 ? QAudioFormat::UnSignedInt : QAudioFormat::SignedInt);
		}
		else
		{
			bResult = false;
		}
		m_headerLength = pos();
	}
	return bResult;
}
