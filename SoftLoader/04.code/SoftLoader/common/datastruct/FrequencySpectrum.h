#pragma once
/**
 * @class	用一系列的元素表示一个频谱，每个元素由频率、振幅和相位组成 
 * @date   2021/04/25
 */

#include <QVector>

class FrequencySpectrum
{
public:
	FrequencySpectrum(int numPoints = 0);
	~FrequencySpectrum();
	class Element
	{
	public:
		Element()
			: frequency(0.0)
			, amplitude(0.0)
			, phase(0.0)
			, clipped(false)
		{ }
		qreal frequency;	//频率 Hz
		qreal amplitude;	//振幅 [0.0, 1.0]
		qreal phase;		//相位 [0.0, 2*PI]
		bool clipped;		//指示频谱分析期间是否已裁剪值
	};

	typedef QVector<Element>::iterator iter_freq;
	typedef QVector<Element>::const_iterator const_iter_freq;

	void reset();

	int count() const;
	Element& operator[](int index);
	const Element& operator[](int index) const;
	iter_freq begin();
	iter_freq end();
	const_iter_freq begin() const;
	const_iter_freq end() const;

	void push_back(const Element & element);

	QVector<Element> & operator=(QVector<Element> & vec);

private:
	QVector<Element> m_elements;
};
