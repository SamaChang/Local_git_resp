#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "def.h"

typedef float real_type;
typedef int64_t dtype;
const dtype MAX0 = (1ll << 31) - 1;
const dtype MIN0 = -(1ll << 31);


dtype f2i(float x, int Q) {
	dtype rst = (dtype)(x*(1ll << Q));
	rst = rst > MAX0 ? MAX0 : rst;
	rst = rst < MIN0 ? MIN0 : rst;
	return rst;
}

real_type i2f(int x, int Q) {
	return ((real_type)x) / (1ll << Q);
}

dtype multiplyOp(dtype x, dtype y, int Q_x, int Q_y, int Q_rst) {
	int temp = Q_x + Q_y - Q_rst;
	dtype rst = (x*y) >> temp;
	rst = rst > MAX0 ? MAX0 : rst;
	rst = rst < MIN0 ? MIN0 : rst;
	return rst;
}

dtype divideOp(dtype x, dtype y, int Q_x, int Q_y, int Q_rst){
	int temp = Q_rst - (Q_x - Q_y);
	dtype rst = (x * (1ll << temp)) / y;
	rst = rst > MAX0 ? MAX0 : rst;
	rst = rst < MIN0 ? MIN0 : rst;
	return rst;
}

dtype addOp(dtype x, dtype y, int Q_x, int Q_y, int Q_rst) {
	dtype rst;
	if (Q_x >= Q_y) {
		y = y << (Q_x - Q_y);
		rst = x + y;
		if (Q_x >= Q_rst) {
			rst = rst >> (Q_x - Q_rst);
		}
		else {
			rst = rst << (Q_rst - Q_x);
		}
	}
	else {
		x = x << (Q_y - Q_x);
		rst = x + y;
		if (Q_y >= Q_rst) {
			rst = rst >> (Q_y - Q_rst);
		}
		else {
			rst = rst << (Q_rst - Q_y);
		}
	}
	rst = rst > MAX0 ? MAX0 : rst;
	rst = rst < MIN0 ? MIN0 : rst;
	return rst;
}


void getDepthImg(int16_t * dispImg, uint16_t * depthImg, int h , int w, int b, int L, float f, int offset){
	const int fQ = 12;
	const int INVALID_DISP_SCALED = -1;
	dtype bf = multiplyOp((dtype)b, f2i(f, fQ), 0, fQ, fQ);
	dtype bf_L = divideOp(bf, (dtype)L, fQ, 0, fQ);

	printf("bf   0x%x = %f\n",bf,(float)b * f);
	printf("bf_L 0x%x = %f\n", bf_L, (float)b * f / L);

	int idx = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			float fd = (float)dispImg[idx] / 32;
			fd = fd + offset;
			dtype d2 = f2i(-fd, fQ);
			dtype down = addOp(d2, bf_L, fQ, fQ, fQ);
			if (down == 0) {
				depthImg[idx] = 0;
			}
			else {
				dtype val = divideOp(bf, down, fQ, fQ, 4);
				//real_type res = i2f(val, fQ);
				depthImg[idx] = val;
			}
			idx++;
		}
	}
}

size_t read_file(char * path, void * out, size_t size)
{
	uint8_t *p8 = (uint8_t *)out;
	printf("read file : %s\n", path);
	FILE *fid = fopen(path, "rb");
	if (!fid)
	{
		return 0;
	}
	int rd = 0;
	while (rd != size)
	{
		int len = fread(&p8[rd], 1, size - rd, fid);
		if (len <= 0)
		{
			break;
		}
		rd += len;
	}
	fclose(fid);
	return rd;
}

size_t write_file(char * path, void * in, size_t size)
{
	uint8_t *p8 = (uint8_t *)in;
	printf("write file : %s\n", path);
	FILE *fid = fopen(path, "wb");
	assert(fid);
	if (!fid)
	{
		return 0;
	}
	int wr = 0;
	while (wr != size)
	{
		int len = fwrite(&p8[wr], 1, size - wr, fid);
		if (len <= 0)
		{
			break;
		}
		wr += len;
	}
	fclose(fid);
	return wr;
}



void transToDepthMap(int16_t *src, uint16_t *dst)
{
	const int b = 50;
	const double f = 479.870079f;
	const double l = 900;
	const int offset = -40;
	getDepthImg(src, dst, DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH,
										b, l, f, offset);
#if 0	
	for (int i = 0; i < IMG_H*IMG_W; i++)
	{
		dst[i] = dst[i] >> 4;
	}
#endif
}

const char * getVersion()
{
	static const char ver[] = "v1.0 .0";
	return ver;
}