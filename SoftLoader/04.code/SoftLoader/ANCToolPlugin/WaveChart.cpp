#include "WaveChart.h"
#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

#include "../common/customplot/Utility.h"

WaveChart::WaveChart(QWidget *parent)
	: QWidget(parent)
	, m_bufferPosition(0)
	, m_bufferLength(0)
	, m_audioPosition(0)
	, m_active(false)
	, m_tileLength(0)
	, m_tileArrayStart(0)
	, m_windowPosition(0)
	, m_windowLength(0)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	setMinimumHeight(200);
}

WaveChart::~WaveChart()
{
	deletePixmaps();
}

void WaveChart::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(rect(), Qt::black);

	if (m_active)
	{
		qDebug() << "WaveChart::paintEvent " << "windowPosition" << m_windowPosition << " windowLength" << m_windowLength;
		qint64 pos = m_windowPosition;
		const qint64 windowEnd = m_windowPosition + m_windowLength;
		int destLeft = 0;
		int destRight = 0;

		while (pos < windowEnd)
		{
			const TilePoint point = tilePoint(pos);
			qDebug() << "WaveChart::paintEvent pos" << pos << " tileIndex" << point.index << " positionOffset" << point.positionOffset << " pixelOffset" << point.pixelOffset;

			if (point.index != NullIndex)
			{
				const Tile &tile = m_tiles[point.index];
				if (tile.painted)
				{
					const qint64 sectionLength = qMin((m_tileLength - point.positionOffset), (windowEnd - pos));
					Q_ASSERT(sectionLength > 0);
					const int sourceRight = tilePixelOffset(point.positionOffset + sectionLength);
					destRight = windowPixelOffset(pos - m_windowPosition + sectionLength);

					QRect destRect = rect();
					destRect.setLeft(destLeft);
					destRect.setRight(destRight);

					QRect sourceRect(QPoint(), m_pixmapSize);
					sourceRect.setLeft(point.pixelOffset);
					sourceRect.setRight(sourceRight);

					qDebug() << "WaveChart::paintEvent" << " tileIndex" << point.index << " source" << point.pixelOffset << sourceRight << " dest" << destLeft << destRight;
					painter.drawPixmap(destRect, *tile.pixmap, sourceRect);
					destLeft = destRight;

					if (point.index < m_tiles.count())
					{
						pos = tilePosition(point.index + 1);
						qDebug() << "WaveChart::paintEvent" << "pos->" << pos;
					}
					else
					{
						//已到达结尾处
						qDebug() << "WaveChart::paintEvent" << QStringLiteral("已到达结尾处");
						break;
					}
				}
				else
				{
					qDebug() << "WaveChart::paintEvent" << " tile" << point.index << " not painted";
					break;
				}
			}
			else
			{
				qDebug() << "WaveChart::paintEvent" << "pos" << pos << "past end of tile array";
				break;
			}
		}
		qDebug() << "WaveChart::paintEvent final pos" << pos << "final x" << destRight;
	}
}

void WaveChart::resizeEvent(QResizeEvent *event)
{
	if (event->size() != event->oldSize())
	{
		createPixmaps(event->size());
	}
}

void WaveChart::initialize(const QAudioFormat & format, qint64 audioBufferSize, qint64 windowDurationUs)
{
	qDebug() << "Waveform::initialize" << "audioBufferSize" << audioBufferSize << " windowDurationUs" << windowDurationUs;
	reset();
	m_format = format;

	//计算tile大小
	m_tileLength = audioBufferSize;
	//计算窗口大小
	m_windowLength = audioLength(m_format, windowDurationUs);
	//计算所需的瓦片数量
	int nTiles;
	if (m_tileLength > m_windowLength)
	{
		nTiles = 2;
	}
	else
	{
		nTiles = m_windowLength / m_tileLength + 1;
		if (m_windowLength % m_tileLength)
		{
			++nTiles;
		}
	}
	qDebug() << "Waveform::initialize" << "tileLength" << m_tileLength << "windowLength" << m_windowLength << "nTiles" << nTiles;
	m_pixmaps.fill(0, nTiles);
	m_tiles.resize(nTiles);
	createPixmaps(rect().size());
	m_active = true;
}

void WaveChart::reset()
{
	qDebug() << "Waveform::reset";
	m_bufferPosition = 0;
	m_buffer = QByteArray();
	m_audioPosition = 0;
	m_format = QAudioFormat();
	m_active = false;
	deletePixmaps();
	m_tiles.clear();
	m_tileLength = 0;
	m_tileArrayStart = 0;
	m_windowPosition = 0;
	m_windowLength = 0;

}

void WaveChart::setAutoUpdatePosition(bool enabled)
{

}

void WaveChart::bufferChanged(qint64 position, qint64 length, const QByteArray &buffer)
{
	qDebug() << "WaveChart::bufferChanged" << "audioPosition" << m_audioPosition << "bufferPosition" << position << "bufferLength" << length;
	m_bufferPosition = position;
	m_bufferLength = length;
	m_buffer = buffer;
	paintTiles();

}

void WaveChart::audioPositionChanged(qint64 position)
{
	qDebug() << "WaveChart::audioPositionChanged" << " audioPosition" << position << " bufferPosition" << m_bufferPosition << " bufferLength" << m_bufferLength;
	if (position >= m_bufferPosition)
	{
		if (position + m_windowLength > m_bufferPosition + m_bufferLength)
		{
			position = qMax(qint64(0), m_bufferPosition + m_bufferLength - m_windowLength);
		}
		m_audioPosition = position;
		setWindowPosition(position);
	}
}

void WaveChart::deletePixmaps()
{
	qDeleteAll(qExchange(m_pixmaps, {}));
}

void WaveChart::createPixmaps(const QSize &widgetSize)
{
	m_pixmapSize = widgetSize;
	m_pixmapSize.setWidth(qreal(widgetSize.width())*m_tileLength / m_windowLength);
	qDebug() << "WaveChart::createPixmaps" << " widgetSize" << widgetSize << " pixmapSize" << m_pixmapSize;

	Q_ASSERT(m_tiles.count() == m_pixmaps.count());
	//创建pixmap
	for (int i = 0; i < m_pixmaps.size(); ++i)
	{
		delete m_pixmaps[i];
		m_pixmaps[i] = nullptr;
		m_pixmaps[i] = new QPixmap(m_pixmapSize);
		
	}
	//更新瓦片 pixmap指针，并标记为重新绘制
	for (int i = 0; i < m_tiles.count(); ++i)
	{
		m_tiles[i].pixmap = m_pixmaps[i];
		m_tiles[i].painted = false;
	}
}

void WaveChart::setWindowPosition(qint64 position)
{
	qDebug() << "WaveChart::setWindowPosition" << "old" << m_windowPosition << "new" << position << "tileArrayStart" << m_tileArrayStart;
	const qint64 oldPosition = m_windowPosition;
	m_windowPosition = position;
	if ((m_windowPosition >= oldPosition) && (m_windowPosition - m_tileArrayStart < (m_tiles.count()*m_tileLength)))
	{
		//算出需要洗牌多少块
		const qint64 offset = m_windowPosition - m_tileArrayStart;
		const int nTiles = offset / m_tileLength;
		shuffleTiles(nTiles);
	}
	else
	{
		resetTiles(m_windowPosition);
	}
	if (!paintTiles() && m_windowPosition!=oldPosition)
	{
		update();
	}
}

qint64 WaveChart::tilePosition(int index) const
{
	return m_tileArrayStart + index*m_tileLength;
}

WaveChart::TilePoint WaveChart::tilePoint(qint64 position) const
{
	TilePoint result;
	if (position >= m_tileArrayStart)
	{
		const qint64 tileArrayEnd = m_tileArrayStart + m_tiles.count()*m_tileLength;
		if (position < tileArrayEnd)
		{
			const qint64 offsetIntoTileArray = position - m_tileArrayStart;
			result.index = offsetIntoTileArray / m_tileLength;
			Q_ASSERT(result.index >= 0 && result.index <= m_tiles.count());
			result.positionOffset = offsetIntoTileArray % m_tileLength;
			result.pixelOffset = tilePixelOffset(result.positionOffset);
			Q_ASSERT(result.pixelOffset >= 0 && result.pixelOffset <= m_pixmapSize.width());
		}
	}
	return result;
}

int WaveChart::tilePixelOffset(qint64 positionOffset) const
{
	Q_ASSERT(positionOffset >= 0 && positionOffset <= m_tileLength);
	const int result = (qreal(positionOffset) / m_tileLength)*m_pixmapSize.width();
	return result;
}

int WaveChart::windowPixelOffset(qint64 positionOffset) const
{
	Q_ASSERT(positionOffset >= 0 && positionOffset <= m_windowLength);
	const int result = (qreal(positionOffset) / m_windowLength) * rect().width();
	return result;
}

bool WaveChart::paintTiles()
{
	qDebug() << "WaveChart::paintTiles";
	bool updateRequired = false;
	for (int i = 0; i < m_tiles.count(); ++i)
	{
		const Tile &tile = m_tiles[i];
		if (!tile.painted)
		{
			const qint64 tileStart = m_tileArrayStart + i*m_tileLength;
			const qint64 tileEnd = tileStart + m_tileLength;
			if (m_bufferPosition <= tileStart&&m_bufferPosition + m_bufferLength >= tileEnd)
			{
				paintTile(i);
				updateRequired = true;
			}
		}
	}
	if (updateRequired)
	{
		update();
	}
	return updateRequired;
}

void WaveChart::paintTile(int index)
{
	const qint64 tileStart = m_tileArrayStart + index*m_tileLength;
	qDebug() << "WaveChart::paintTile" << " index" << index << " bufferPosition" << m_bufferPosition << " bufferLength" << m_bufferLength << " start" << tileStart << "end" << tileStart + m_tileLength;

	Q_ASSERT(m_bufferPosition <= tileStart);
	Q_ASSERT(m_bufferPosition + m_bufferLength >= tileStart + m_tileLength);
	
	Tile &tile = m_tiles[index];
	QRect rctPixmap = tile.pixmap->rect();
	Q_ASSERT(!tile.painted);

	const qint16* base = reinterpret_cast<const qint16*>(m_buffer.constData());
	const qint16* buffer = base + ((tileStart - m_bufferPosition) / 2);
	const int numSamples = m_tileLength / (2 * m_format.channelCount());

	QPainter painter(tile.pixmap);
	painter.fillRect(tile.pixmap->rect(), Qt::black);

	QPen pen(Qt::white, 1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
	painter.setPen(pen);

	//计算内部PCM的值
	qint16 previousPcmValue = 0;
	if (buffer > base)
	{
		previousPcmValue = *(buffer - m_format.channelCount());
	}
	//计算内部点
	const qreal previousRealValue = pcmToReal(previousPcmValue);
	const int originY = ((previousRealValue + 1.0) / 2)*m_pixmapSize.height();
	const QPoint origin(0, originY);

	QLine line(origin, origin);
	
	for (int i = 0; i < numSamples; ++i)
	{
		const qint16* ptr = buffer + i*m_format.channelCount();
		const int offset = reinterpret_cast<const char*>(ptr) - m_buffer.constData();

		Q_ASSERT(offset >= 0);
		Q_ASSERT(offset < m_bufferLength);
		Q_UNUSED(offset);

		const qint16 pcmValue = *ptr;
		const qreal realValue = pcmToReal(pcmValue);

		const int x = tilePixelOffset(i * 2 * m_format.channelCount());
		const int y = ((realValue + 1.0) / 2)*m_pixmapSize.height();
		
		line.setP2(QPoint(x, y));
		painter.drawLine(line);
		line.setP1(line.p2());
	}
	tile.painted = true;
}

void WaveChart::shuffleTiles(int n)
{
	qDebug() << "WaveChart::shuffleTiles" << " n" << n;
	while (n--)
	{
		Tile tile = m_tiles.first();
		tile.painted = false;
		m_tiles.erase(m_tiles.begin());
		m_tiles += tile;
		m_tileArrayStart += m_tileLength;
	}
	qDebug() << "WaveChart::shuffleTiles" << "tileArrayStart" << m_tileArrayStart;
}

void WaveChart::resetTiles(qint64 newStartPos)
{
	qDebug() << "WaveChart::resetTiles" << "newStartPos" << newStartPos;
	QVector<Tile>::iterator iter = m_tiles.begin();
	for (; iter != m_tiles.end(); ++iter)
	{
		iter->painted = false;
	}
	m_tileArrayStart = newStartPos;
}
