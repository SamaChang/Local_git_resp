#include "FrequencySpectrum.h"

FrequencySpectrum::FrequencySpectrum(int numPoints) : m_elements(numPoints)
{
}

FrequencySpectrum::~FrequencySpectrum()
{
}

void FrequencySpectrum::reset()
{
	iter_freq i = begin();
	for (; i!=end(); i++)
	{
		*i = Element();
	}
}

int FrequencySpectrum::count() const
{
	return m_elements.count();
}

FrequencySpectrum::Element& FrequencySpectrum::operator[](int index)
{
	return m_elements[index];
}
  
const FrequencySpectrum::Element& FrequencySpectrum::operator[](int index) const
{
	return m_elements[index];
}

FrequencySpectrum::iter_freq FrequencySpectrum::begin()
{
	return m_elements.begin();
}

FrequencySpectrum::const_iter_freq FrequencySpectrum::begin() const
{
	return m_elements.begin();
}

FrequencySpectrum::iter_freq FrequencySpectrum::end()
{
	return m_elements.end();
}

FrequencySpectrum::const_iter_freq FrequencySpectrum::end() const
{
	return m_elements.end();
}

void FrequencySpectrum::push_back(const Element & element)
{
	m_elements.push_back(element);
}

QVector<FrequencySpectrum::Element> & FrequencySpectrum::operator=(QVector<Element> & vec)
{
	m_elements = vec;
	return m_elements;
}
