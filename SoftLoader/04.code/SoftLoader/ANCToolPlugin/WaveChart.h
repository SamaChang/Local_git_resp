#pragma once

#include <QWidget>
#include <QAudioFormat>
#include <QScopedPointer>
#include <QPixmap>
/**
 * @class	波形图显示类   
 * @date   2021/04/27
 */

class WaveChart : public QWidget
{
	Q_OBJECT

public:
	WaveChart(QWidget *parent = nullptr);
	~WaveChart();

protected:
	void paintEvent(QPaintEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

public:
	void initialize(const QAudioFormat & format, qint64 audioBufferSize, qint64 windowDurationUs);
	void reset();
	void setAutoUpdatePosition(bool enabled);

public slots:
	void bufferChanged(qint64 position, qint64 length, const QByteArray &buffer);
	void audioPositionChanged(qint64 position);

private:
	void deletePixmaps();
	//创建所有的pix,更新显示
	void createPixmaps(const QSize &widgetSize);
	//更新window位置
	void setWindowPosition(qint64 position);
	//瓦片的基本位置
	qint64 tilePosition(int index) const;
	//给定瓦片中瓦片点的结构
	struct TilePoint
	{
		TilePoint(int idx = 0, qint64 pos = 0, qint64 pix = 0) : index(idx),positionOffset(pos),pixelOffset(pix)
		{

		}
		int		index;			//瓦片索引
		qint64	positionOffset;	//瓦片开始的字节数
		int		pixelOffset;	//对应pixmap左侧的像素数
	};
	//将缓冲区中的位置转换为瓦片索引，并将以像素为单位的偏移量转换为相应的pixmap
	//缓冲区偏移量，字节 如果位置在瓦片数组之外，则索引为NullIndex，偏移量为零
	TilePoint tilePoint(qint64 position) const;
	//将字节偏移量转换为瓦片中的像素偏移量
	int tilePixelOffset(qint64 positionOffset) const;
	//将窗口中以字节为单位的偏移量转换为窗口widget的rect（）中以像素为单位的偏移量
	int windowPixelOffset(qint64 positionOffset) const;
	//绘制所有可以绘制的瓦片,iff update()被调用，返回true
	bool paintTiles();
	//绘制某一个瓦片
	void paintTile(int index);
	//将前n个瓦片移动到阵列的末尾，并将其标记为未绘制
	void shuffleTiles(int n);
	//重置瓦片队列
	void resetTiles(qint64 newStartPos);

private:
	static const int NullIndex = -1;

private:
	qint64			m_bufferPosition;
	qint64			m_bufferLength;
	QByteArray		m_buffer;
	
	qint64			m_audioPosition;
	QAudioFormat	m_format;

	bool			m_active;

	QSize			m_pixmapSize;
	QVector<QPixmap*>	m_pixmaps;

	struct Tile
	{
		QPixmap*	pixmap;		//指向m_pixmaps数组的指针
		bool		painted;	//指示此瓦片是否已绘制的标志
	};
	QVector<Tile>	m_tiles;

	qint64			m_tileLength;	//每个瓦片所描述的音频数据的字节长度
	qint64			m_tileArrayStart;	//以字节为单位的第一个瓦片的位置，相对于缓冲区

	qint64			m_windowPosition;
	qint64			m_windowLength;
};
