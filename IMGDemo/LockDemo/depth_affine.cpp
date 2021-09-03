#include <stdio.h>
#include <assert.h>
#include "depth_affine.h"
#include <math.h>
#include "def.h"

void get_RT(matrix::SquareMatrix<float, 3> &align_R,
	matrix::Vector3<float> &align_T)
{
	const float k_rgb[] = {
		4.8147049724433202e+002, 0.0, 3.1053510348534098e+002, 0.0,
		4.8135872448676798e+002, 1.8256511991245500e+002,
		0.0f, 0.0f, 1.0f
	};

	const float k_ir[] = {
		4.7739686514226401e+002, 0.0, 3.2619387707367201e+002, 0.0,
		4.7704351868156601e+002, 1.8107256269720500e+002,
		0.0, 0.0, 1.0
	};

	const float r_ir2rgb[] = {
		9.9966600977530196e-001, -1.2051747288106599e-002,
		-2.2860977390058899e-002, 1.2422302561236800e-002,
		9.9979262170686400e-001, 1.6136913570848999e-002,
		2.2661758515222400e-002, -1.6415509977444401e-002,
		9.9960841119569299e-001,
	};

	const float t_ir2rgb[] = {
		-2.9869903142273799e+001, -1.0230687518216101e-002,
		-6.0096784138564496e-001,
	};
	matrix::SquareMatrix<float, 3> K_rgb(k_rgb);
	matrix::SquareMatrix<float, 3> K_ir(k_ir);
	matrix::SquareMatrix<float, 3> R_ir2rgb(r_ir2rgb);
	matrix::Vector3<float> T_ir2rgb(t_ir2rgb);
	align_R = K_rgb * R_ir2rgb * K_ir.I();
	align_T = K_rgb * T_ir2rgb;
}

void depth_affine(uint16_t *src, uint16_t *dst, int h, int w,
	matrix::SquareMatrix<float, 3> &R,
	matrix::Vector3<float> &T)
{
	matrix::Vector3<float> uv_depth;
	uv_depth(2) = 1.0f;
	memset(dst, 0, h * w * sizeof(uint16_t));
	for (int i = 0; i < h; ++i) {
		uv_depth(1) = i;
		for (int j = 0; j < w; ++j) {
			uv_depth(0) = j;
			*src >>= 4;
			matrix::Vector3<float> uv_color = (float)(*src) * R * uv_depth + T;
			if (fabs(uv_color(2)) > 1e-6) {
				int x = roundf(uv_color(0) / uv_color(2));
				int y = roundf(uv_color(1) / uv_color(2));
				if (x >= 0 && x < w && y >= 0 && y < h)
					dst[y * w + x] = *src;
			}
			src++;
		}
	}
}


static matrix::SquareMatrix<float, 3> _align_R;
static matrix::Vector3<float> _align_T;
void depth_affine_api(uint16_t *src, uint16_t *dst, int h, int w)
{

	get_RT(_align_R, _align_T);
	depth_affine(src, dst, h, w,
		_align_R, _align_T);
}



static size_t read_file(char * path, void * out, size_t size)
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

static size_t write_file(char * path, void * in, size_t size)
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

#if 0
#define IMG_W	640
#define IMG_H	360
uint16_t src[640 * 360];
uint16_t dst[640 * 360];
void main()
{
	read_file("depth16_640x360.raw", src, IMG_W * IMG_H * 2);

	depth_affine_api(src, dst, DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH);

	write_file("out.raw", dst, IMG_W * IMG_H * 2);

}
#endif