#include "skv_ulity.h"
#include "skv_info.h"
#include "skv_config.h"

int skv_bigorsmall()
{
	int a = -1;
	unsigned short v = 0x0102;
	unsigned char *p = (unsigned char *)&v;
	if (*p == 0x01)
		a = 1;
	else if (*p == 0x02)
		a = 0;
	return a;
}

int skv_bytes2floats(BYTE * in, float * out, int in_size, int bSamples, int bs)
{
	int nfloats = 0;
	//int bs = skv_bigorsmall();
	int i = 0, j = 0;
	if (bSamples == 16)
	{
		BYTE charArray[2];
		nfloats = in_size / 2;
		for (j = 0; j < in_size; j = j + 2)
		{
			charArray[0] = in[j];
			charArray[1] = in[j + 1];
			if (bs == 0)
				out[j / 2] = (float)((short)((charArray[1] << 8) | charArray[0]));
			else if (bs == 1)
				out[j / 2] = (float)((short)((charArray[0] << 8) | charArray[1]));
		}
	}
	else
	{
		nfloats = in_size;
		for (i = 0; i < in_size; i++)
		{
			out[i] = (float)in[i];
		}
	}
	return nfloats;
}

int skv_floats2bytes(float * in, BYTE * out, int in_size, int bSamples, int bs)
{
	int i = 0, j = 0;
	//int bs = skv_bigorsmall();
	int nbytes = 0;
	if (bSamples == 16)
	{
		nbytes = in_size * 2;
		BYTE b[2];
		short a;
		for (j = 0; j < in_size; j = j + 1)
		{
			a = (short)(in[j]);
			b[0] = (BYTE)(a & 0xff);
			b[1] = (BYTE)((a >> 8) & 0xff);
			if (bs == 0)
			{
				out[2 * j] = b[0];
				out[2 * j + 1] = b[1];
			}
			else if (bs == 1)
			{
				out[2 * j] = b[1];
				out[2 * j + 1] = b[0];
			}
		}
	}
	else
	{
		nbytes = in_size;
		BYTE b;
		for (i = 0; i < in_size; ++i)
		{
			b = (BYTE)(in[i]);
			out[i] = b;
		}
	}
	return nbytes;
}

int skv_bytes2shorts(BYTE * in, short * out, int in_size, int bSamples, int bs)
{
	int nshort = 0;
	//int bs = skv_bigorsmall();
	int i = 0, j = 0;
	if (bSamples == 16)
	{
		BYTE charArray[2];
		nshort = in_size / 2;
		for (j = 0; j < in_size; j = j + 2)
		{
			charArray[0] = in[j];
			charArray[1] = in[j + 1];
			if (bs == 0)
				out[j / 2] = (short)((charArray[1] << 8) | charArray[0]);
			else if (bs == 1)
				out[j / 2] = (short)((charArray[0] << 8) | charArray[1]);
		}
	}
	else
	{
		nshort = in_size;
		for (i = 0; i < in_size; i++)
		{
			out[i] = (short)in[i];
		}
	}
	return nshort;
}

int skv_shorts2bytes(short * in, BYTE * out, int in_size, int bSamples, int bs)
{
	int i = 0, j = 0;
	//int bs = skv_bigorsmall();
	int nbytes = 0;
	if (bSamples == 16)
	{
		nbytes = in_size * 2;
		BYTE b[2];
		for (j = 0; j < in_size; j = j + 1)
		{
			b[0] = (BYTE)(in[j] & 0xff);
			b[1] = (BYTE)((in[j] >> 8) & 0xff);
			if (bs == 0)
			{
				out[2 * j] = b[0];
				out[2 * j + 1] = b[1];
			}
			else if (bs == 1)
			{
				out[2 * j] = b[1];
				out[2 * j + 1] = b[0];
			}
		}
	}
	else
	{
		nbytes = in_size;
		for (i = 0; i < in_size; ++i)
		{
			out[i] = (BYTE)(in[i]);
		}
	}
	return nbytes;
}

/*************************************************************************
* @brief    : 
* @inparam  :
|__ pszDate   2010/04/12/23/59/59、 2010-04-12 23:59:59
* @outparam : NA
* @return   :
|__ time_t
*************************************************************************/
time_t skv_datestr2sec(char* pszDate)
{
	struct tm tmDate = { 0 };
	tmDate.tm_year = atoi(pszDate) - 1900;
	tmDate.tm_mon = atoi(pszDate + 5) - 1;
	tmDate.tm_mday = atoi(pszDate + 8);
	tmDate.tm_hour = atoi(pszDate + 11);
	tmDate.tm_min = atoi(pszDate + 14);
	tmDate.tm_sec = atoi(pszDate + 17);
	return mktime(&tmDate);
}

char * skv_strlwr(char *s)
{
	char *str;
	str = s;
	while (*str != '\0')
	{
		if (*str >= 'A' && *str <= 'Z') 
		{
			*str += 'a' - 'A';
		}
		str++;
	}
	return s;
}

static char number[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
void skv_itoa(int data, char* buffer)
{
	//sprintf(buffer, "%d", data);
	int i = 0;
	do
	{
		int r = data % 10;
		buffer[i] = number[r];
		i = i + 1;
		data = data / 10;
	} while (data > 0);
	int k = 0;
	char ch;
	for (k = 0; k < i / 2; k++)
	{
		ch = buffer[k];
		buffer[k] = buffer[i - 1 - k];
		buffer[i - 1 - k] = ch;
	}
}

void skv_print(char * key, char * str)
{
#ifdef OS_LINUX
		fprintf(stderr, "%s: %s\n", key, str);
#endif
#ifdef OS_ANDROID
		LOGI("%s: %s\n", key, str);
#endif
}