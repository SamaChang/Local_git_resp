#pragma once
/**
 * @class	��һϵ�е�Ԫ�ر�ʾһ��Ƶ�ף�ÿ��Ԫ����Ƶ�ʡ��������λ��� 
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
		qreal frequency;	//Ƶ�� Hz
		qreal amplitude;	//��� [0.0, 1.0]
		qreal phase;		//��λ [0.0, 2*PI]
		bool clipped;		//ָʾƵ�׷����ڼ��Ƿ��Ѳü�ֵ
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
