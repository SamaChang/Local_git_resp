#pragma once

#include <QWidget>
#include <QAudioFormat>
#include <QScopedPointer>
#include <QPixmap>
/**
 * @class	����ͼ��ʾ��   
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
	//�������е�pix,������ʾ
	void createPixmaps(const QSize &widgetSize);
	//����windowλ��
	void setWindowPosition(qint64 position);
	//��Ƭ�Ļ���λ��
	qint64 tilePosition(int index) const;
	//������Ƭ����Ƭ��Ľṹ
	struct TilePoint
	{
		TilePoint(int idx = 0, qint64 pos = 0, qint64 pix = 0) : index(idx),positionOffset(pos),pixelOffset(pix)
		{

		}
		int		index;			//��Ƭ����
		qint64	positionOffset;	//��Ƭ��ʼ���ֽ���
		int		pixelOffset;	//��Ӧpixmap����������
	};
	//���������е�λ��ת��Ϊ��Ƭ����������������Ϊ��λ��ƫ����ת��Ϊ��Ӧ��pixmap
	//������ƫ�������ֽ� ���λ������Ƭ����֮�⣬������ΪNullIndex��ƫ����Ϊ��
	TilePoint tilePoint(qint64 position) const;
	//���ֽ�ƫ����ת��Ϊ��Ƭ�е�����ƫ����
	int tilePixelOffset(qint64 positionOffset) const;
	//�����������ֽ�Ϊ��λ��ƫ����ת��Ϊ����widget��rect������������Ϊ��λ��ƫ����
	int windowPixelOffset(qint64 positionOffset) const;
	//�������п��Ի��Ƶ���Ƭ,iff update()�����ã�����true
	bool paintTiles();
	//����ĳһ����Ƭ
	void paintTile(int index);
	//��ǰn����Ƭ�ƶ������е�ĩβ����������Ϊδ����
	void shuffleTiles(int n);
	//������Ƭ����
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
		QPixmap*	pixmap;		//ָ��m_pixmaps�����ָ��
		bool		painted;	//ָʾ����Ƭ�Ƿ��ѻ��Ƶı�־
	};
	QVector<Tile>	m_tiles;

	qint64			m_tileLength;	//ÿ����Ƭ����������Ƶ���ݵ��ֽڳ���
	qint64			m_tileArrayStart;	//���ֽ�Ϊ��λ�ĵ�һ����Ƭ��λ�ã�����ڻ�����

	qint64			m_windowPosition;
	qint64			m_windowLength;
};
