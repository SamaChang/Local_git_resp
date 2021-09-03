#include <stdint.h>

bool judge_0_16(uint16_t * gray, int h, int w)
{

	for (int i = 1; i < h - 1; i++)
	{
		for (int j = 1; j < w - 1; j++)
		{
			if (gray[i * w + j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

inline uint32_t sumWin3x3_16(uint16_t * cnter, int w)
{
	int sum = cnter[0] + cnter[1] + cnter[-1];
	sum += cnter[0 + w] + cnter[1 + w] + cnter[-1 + w];
	sum += cnter[0 - w] + cnter[1 - w] + cnter[-1 - w];
	return sum;
}

inline uint32_t conutNonZero3x3_16(uint16_t * cnter, int w)
{
	int count = 0;
	count += cnter[-1] != 0;
	count += cnter[0] != 0;
	count += cnter[1] != 0;

	count += cnter[-1 + w] != 0;
	count += cnter[0 + w] != 0;
	count += cnter[1 + w] != 0;


	count += cnter[-1 - w] != 0;
	count += cnter[0 - w] != 0;
	count += cnter[1 - w] != 0;


	return count;
}


void fill_16(uint16_t * gray, int h, int w)
{
	for (int i = 1; i < h - 1; i++)
	{
		for (int j = 1; j < w - 1; j++)
		{
			if (gray[i * w + j] == 0)
			{
				uint32_t sum = sumWin3x3_16(&gray[i * w + j], w);
				uint32_t cnt = conutNonZero3x3_16(&gray[i * w + j], w);
				if (cnt)
					gray[i * w + j] = sum / cnt;
			}
		}
	}
}


void fill_reverse_16(uint16_t * gray, int h, int w)
{
	for (int i = 1; i < h - 1; i++)
	{
		for (int j = w - 1; j >= 0; j--)
		{
			if (gray[i * w + j] == 0)
			{
				uint32_t sum = sumWin3x3_16(&gray[i * w + j], w);
				uint32_t cnt = conutNonZero3x3_16(&gray[i * w + j], w);
				if (cnt)
					gray[i * w + j] = sum / cnt;
			}
		}
	}
}

bool fill_gray16(uint16_t * gray, int h, int w)
{
	bool jd = true;
	int count = 0;
	bool tmp = false;
	do {
		tmp = judge_0_16(gray, h, w);
		count++;
		if (count == 10) {
			jd = false;
			break;
		}
		if (tmp == false)
		{
			if (count % 2)
				fill_16(gray, h, w);
			else
				fill_reverse_16(gray, h, w);
		}
	} while (tmp == false);
	return jd;
}
