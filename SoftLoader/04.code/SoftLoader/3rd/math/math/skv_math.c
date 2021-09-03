#include "skv_math.h"
#include "skv_fastmath.h"
#include "../basic/os_support.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>  

Complex RandComplex()
{
	Complex r;
	r.real = rand() / (double)(RAND_MAX);
	r.image = rand() / (double)(RAND_MAX);
	return r;
}
Complex Add1(Complex a, Complex b)
{
	Complex r;
	r.real = a.real + b.real;
	r.image = a.image + b.image;
	return r;
}
Complex Add2(spx_word16_t a, Complex b)
{
	Complex r;
	r.real = a + b.real;
	r.image = b.image;
	return r;
}
Complex Add3(Complex a, spx_word16_t b)
{
	Complex r;
	r.real = a.real + b;
	r.image = a.image;
	return r;
}

Complex Minus1(Complex a, Complex b)
{
	Complex r;
	r.real = a.real - b.real;
	r.image = a.image - b.image;
	return r;
}
Complex Minus2(spx_word16_t a, Complex b)
{
	Complex r;
	r.real = a - b.real;
	r.image = -b.image;
	return r;
}
Complex Minus3(Complex a, spx_word16_t b)
{
	Complex r;
	r.real = a.real - b;
	r.image = a.image;
	return r;
}

Complex Multi1(Complex a, Complex b)
{
	Complex r;
	r.real  = a.real * b.real - a.image * b.image;
	r.image = a.real * b.image + a.image * b.real;
	return r;
}
Complex Multi2(spx_word16_t a, Complex b)
{
	Complex r;
	r.real  = a * b.real;
	r.image = a * b.image;
	return r;
}
Complex Multi3(Complex a, spx_word16_t b)
{
	Complex r;
	r.real  = a.real * b;
	r.image = a.image * b;
	return r;
}

Complex Div1(Complex a, Complex b)
{
	Complex r;
	float tmp = b.real * b.real + b.image * b.image;
	if (tmp == 0)
	{
		if (a.real == 0)
		{
			r.real = 0.0f;
			r.image = 0.0f;
		}
		else
		{
			r.real = a.real > 0 ? FLT_MAX / 10.0f : -FLT_MAX / 10.0f;
		}
		if (a.image == 0)
		{
			r.image = 0.0f;
		}
		else
		{
			r.image = a.image > 0 ? FLT_MAX / 10.0f : -FLT_MAX / 10.0f;
		}
	}
	else
	{
		r.real = (a.real * b.real + a.image * b.image) / tmp;
		r.image = (a.image * b.real - a.real * b.image) / tmp;
		if (isnan(r.real) || isinf(r.real))
		{
			r.real = 0.0;
		}
		if (isnan(r.image) || isinf(r.image))
		{
			r.image = 0.0;
		}
	}
	return r;
}
Complex Div2(spx_word16_t a, Complex b)
{
	Complex aa = { a, 0 };
	return Div1(aa, b);
}
Complex Div3(Complex a, spx_word16_t b)
{
	Complex r;
	if (b == 0)
	{
		if (a.real == 0 && a.image == 0)
		{
			r.real = 0.0f;
			r.image = 0.0f;
		}
		else
		{
			r.real = a.real > 0 ? FLT_MAX : FLT_MIN;
			r.image = a.image > 0 ? FLT_MAX : FLT_MIN;
		}
		r.real = 0.0f;
		r.image = 0.0f;
	}
	else
	{
		r.real = a.real / b;
		r.image = a.image / b;
	}
	return r;
}

Complex Neg(Complex a)
{
	Complex r;
	r.real = -a.real;
	r.image = -a.image;
	return r;
}

Complex Conj(Complex a)
{
	Complex r;
	r.real  = a.real;
	r.image = -a.image;
	return r;
}

spx_word16_t SKV_ABSC(Complex a)
{
	return  SKV_SQRTF(a.real * a.real + a.image * a.image);
}
Complex SKV_SQRTC(spx_word16_t a)
{
	Complex r;
	if (a > 0)
	{
		r.real = SKV_SQRTF(a);
		r.image = 0.0f;
	}
	else if (a < 0)
	{
		r.real = 0.0f;
		r.image = SKV_SQRTF(-a);
	}
	else
	{
		r.real = 0.0f;
		r.image = 0.0f;
	}
	return r;
}
spx_word16_t SKV_POWC(Complex a)
{
	return  a.real * a.real + a.image * a.image;
}
spx_word16_t SKV_ABSR(spx_word16_t a)
{
	return ((a) > 0 ? (a) : (-a));
}
Complex SKV_EXPC(Complex a)
{
	//exp{ a + bi } = (exp{ a })*(cosb + isinb)
	Complex r;
	r.real = SKV_COS(a.image);
	r.image = SKV_SIN(a.image);
	return Multi2(SKV_EXP(a.real), r);
}
void ComplexMatSetOp1(ComplexMatrix x_data, ComplexMatrix y_data)
{
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size)
	{
		fprintf(stderr, "402 Error: ComplexMatrix(0:%d, 0:%d) = ComplexMatrix(0:%d, 0:%d) Failed! \n", x_data.r_size-1, x_data.c_size-1, y_data.r_size-1, y_data.c_size-1);
		exit(1);
	}
	SPEEX_COPY(x_data.data, y_data.data, x_data.r_size * x_data.c_size);
}
void ComplexMatSetOp2(ComplexMatrix x_data, RealMatrix y_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size)
	{
		fprintf(stderr, "402 Error: ComplexMatrix(0:%d, 0:%d) = RealMatrix(0:%d, 0:%d) Failed! \n", x_data.r_size-1, x_data.c_size-1, y_data.r_size-1, y_data.c_size-1);
		exit(1);
	}
	int i = 0;
	for ( i = 0; i < size; i++)
	{
		x_data.data[i].real = y_data.data[i];
		x_data.data[i].image = 0.0f;
	}
}
void ComplexMatSetOp3(ComplexMatrix x_data, Complex y_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "402 Error: ComplexMatrix(0:%d, 0:%d) = Complex Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	int i = 0;
	for ( i = 0; i < size; i++)
	{
		x_data.data[i] = y_data;
	}
}
void ComplexMatSetOp4(ComplexMatrix x_data, Complex y_data, int s_r, int s_c, int e_r, int e_c)
{
	int r_size = e_r - s_r + 1;
	int c_size = e_c - s_c + 1;
	int size = r_size * c_size;
	if (x_data.data == NULL || r_size * c_size <= 0 || s_r < 0 || s_r >= x_data.r_size ||
		s_c < 0 || s_c >= x_data.c_size || e_r < 0 || e_r >= x_data.r_size ||
		e_c < 0 || e_c >= x_data.c_size)
	{
		fprintf(stderr, "402 Error: ComplexMatrix(%d:%d, %d:%d) = Complex Failed\n", s_r, e_r, s_c, e_c);
		exit(1);
	}
	int i = 0, j = 0;
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			x_data.data[i * x_data.c_size + j] = y_data;
		}
	}
}
void ComplexMatSetOp5(ComplexMatrix x_data, ComplexMatrix y_data, int s_r, int s_c, int e_r, int e_c)
{
	int r_size = e_r - s_r + 1;
	int c_size = e_c - s_c + 1;
	int size = r_size * c_size;
	if (y_data.data == NULL || r_size * c_size <= 0 || s_r < 0 || s_r >= y_data.r_size ||
		s_c < 0 || s_c >= y_data.c_size || e_r < 0 || e_r >= y_data.r_size ||
		e_c < 0 || e_c >= y_data.c_size)
	{
		fprintf(stderr, "402 Error: ComplexMatrix = ComplexMatrix(%d:%d, %d:%d) Failed\n", s_r, e_r, s_c, e_c);
		exit(1);
	}
	
	if (x_data.data == NULL)
	{
		x_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
		x_data.r_size = r_size;
		x_data.c_size = c_size;
	}
	else if (size > x_data.r_size * x_data.c_size)
	{
		x_data.data = (Complex *)speex_realloc(x_data.data, size * sizeof(Complex));
		x_data.r_size = r_size;
		x_data.c_size = c_size;
	}
	
	int i = 0, j = 0;
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			x_data.data[(i - s_r) * x_data.c_size + (j - s_c)] = y_data.data[i * y_data.c_size + j];
		}
	}
}
void ComplexMatSetOp6(ComplexMatrix x_data, RealMatrix y_data, int s_r, int s_c, int e_r, int e_c)
{
	int r_size = e_r - s_r + 1;
	int c_size = e_c - s_c + 1;
	int size = r_size * c_size;
	if (y_data.data == NULL || r_size * c_size <= 0 || s_r < 0 || s_r >= y_data.r_size ||
		s_c < 0 || s_c >= y_data.c_size || e_r < 0 || e_r >= y_data.r_size ||
		e_c < 0 || e_c >= y_data.c_size)
	{
		fprintf(stderr, "402 Error: ComplexMatrix = RealMatrix(%d:%d, %d:%d) Failed\n", s_r, e_r, s_c, e_c);
		exit(1);
	}

	if (x_data.data == NULL)
	{
		x_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
		x_data.r_size = r_size;
		x_data.c_size = c_size;
	}
	else if (size > x_data.r_size * x_data.c_size)
	{
		x_data.data = (Complex *)speex_realloc(x_data.data, size * sizeof(Complex));
		x_data.r_size = r_size;
		x_data.c_size = c_size;
	}

	int i = 0, j = 0;
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			x_data.data[(i - s_r) * x_data.c_size + (j - s_c)].real = y_data.data[i * y_data.c_size + j];
			x_data.data[(i - s_r) * x_data.c_size + (j - s_c)].image = 0.0f;
		}
	}
}

ComplexMatrix NewComplexMatrix(spx_uint32_t r_size, spx_uint32_t c_size)
{
	int size = r_size * c_size;
	if (size <= 0)
	{
		fprintf(stderr, "401 Error: NewComplexMatrix(0:%d, 0:%d) Failed!", r_size - 1, c_size - 1);
		exit(1);
	}
	ComplexMatrix st;
	st.r_size = r_size;
	st.c_size = c_size;
	st.data = (Complex *)speex_alloc(size * sizeof(Complex));
	Complex zero = { 0.0f, 0.0f };
	ComplexMatSetOp3(st, zero);
	return st;
}
ComplexMatrix FreeComplexMatrix(ComplexMatrix st)
{
	st.r_size = 0;
	st.c_size = 0;
	if (st.data != NULL)
	{
		speex_free(st.data); st.data = NULL;
	}
	return st;
}
ComplexMatrix RandComplexMatrix(spx_uint32_t r_size, spx_uint32_t c_size)
{
	int size = r_size * c_size;
	if (size <= 0)
	{
		fprintf(stderr, "401 Error: RandComplexMatrix(0:%d, 0:%d) Failed!", r_size - 1, c_size - 1);
		exit(1);
	}
	ComplexMatrix st;
	st.r_size = r_size;
	st.c_size = c_size;
	st.data = (Complex *)speex_alloc(size * sizeof(Complex));
	int i = 0;
	for ( i = 0; i < size; i++)
	{
		st.data[i] = RandComplex();
	}
	return st;
}

Complex ComplexMatrixGetAt(ComplexMatrix x_data, spx_uint32_t i, spx_uint32_t j)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "415 Error: ComplexMatrixGetAt, NULL ComplexMatrix\n");
		exit(1);
	}
	if (i * x_data.c_size + j >= size)
	{
		fprintf(stderr, "415 Error: ComplexMatrixGetAt ComplexMatrix(%d, %d) Failed\n", i, j);
		exit(1);
	}
	return x_data.data[i * x_data.c_size + j];
}
void ComplexMatrixSetAt(ComplexMatrix x_data, spx_uint32_t i, spx_uint32_t j, Complex y_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "415 Error: ComplexMatrixSetAt, NULL ComplexMatrix\n");
		exit(1);
	}
	if (i * x_data.c_size + j >= size)
	{
		fprintf(stderr, "415 Error: ComplexMatrixSetAt ComplexMatrix(%d, %d) Failed\n", i, j);
		exit(1);
	}
	x_data.data[i * x_data.c_size + j] = y_data;
}
void printComplexMatrix(ComplexMatrix x_data, const char * var_name)
{
	if (x_data.data == NULL || x_data.r_size * x_data.c_size <= 0)
	{
		fprintf(stderr, "001 Error: %s(%d, %d)=NULL\n", var_name, x_data.r_size, x_data.c_size);
		return;
	}

	printf("%s(%d, %d) =\n", var_name, x_data.r_size, x_data.c_size);
	        
	int i = 0, j = 0;
	for ( i = 0; i < x_data.r_size; i++)
	{
		printf("               ");
		for ( j = 0; j < x_data.c_size; j++)
		{
			if (x_data.data[i * x_data.c_size + j].image < 0)
			{
				printf("%.3f%.3fi ", x_data.data[i * x_data.c_size + j].real, x_data.data[i * x_data.c_size + j].image);
			}
			else
			{
				printf("%.3f+%.3fi ", x_data.data[i * x_data.c_size + j].real, x_data.data[i * x_data.c_size + j].image);
			}
		}
		printf("\n");
	}
}
void fprintComplexMatrix(FILE * fp, ComplexMatrix x_data, const char * var_name)
{
	if (fp == NULL)
	{
		fprintf(stderr, "001 Error: File cann't be open\n");
		return;
	}
	if (x_data.data == NULL || x_data.r_size * x_data.c_size <= 0)
	{
		fprintf(fp, "%s(0:%d, 0:%d)=NULL\n", var_name, x_data.r_size, x_data.c_size);
		return;
	}

	fprintf(fp, "%s(0:%d, 0:%d) =\n", var_name, x_data.r_size, x_data.c_size);

	int i = 0, j = 0;
	for (i = 0; i < x_data.r_size; i++)
	{
		fprintf(fp, "               ");
		for (j = 0; j < x_data.c_size; j++)
		{
			if (x_data.data[i * x_data.c_size + j].image < 0)
			{
				fprintf(fp, "%f%fi ", x_data.data[i * x_data.c_size + j].real, x_data.data[i * x_data.c_size + j].image);
			}
			else
			{
				fprintf(fp, "%f+%fi ", x_data.data[i * x_data.c_size + j].real, x_data.data[i * x_data.c_size + j].image);
			}
		}
		fprintf(fp,"\n");
	}
}
void fprintComplexMatrix1(ComplexMatrix x_data, int s_r, int s_c, int e_r, int e_c, const char * var_name, const char * filename)
{
	if (x_data.data == NULL || x_data.r_size * x_data.c_size <= 0)
	{
		fprintf(stderr, "x_data(0:%d, 0:%d)=NULL\n", x_data.r_size, x_data.c_size);
		return;
	}
	FILE * fp = NULL;
	fp = fopen(filename, "at");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Cann't open %s\n", filename);
		return;
	}

	fprintf(fp, "%s\n", var_name);
	int i = 0, j = 0;
	for (i = s_r; i <= e_r && i < x_data.r_size; i++)
	{
		for (j = s_c; j <= e_c && j < x_data.c_size; j++)
		{
			if (x_data.data[i * x_data.c_size + j].image < 0)
			{
				fprintf(fp, "%f%fi ", x_data.data[i * x_data.c_size + j].real, x_data.data[i * x_data.c_size + j].image);
			}
			else
			{
				fprintf(fp, "%f+%fi ", x_data.data[i * x_data.c_size + j].real, x_data.data[i * x_data.c_size + j].image);
			}
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

ComplexMatrix ComplexMatAddOp1(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL ||  x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "403 Error: ComplexMatrix(0:%d, 0:%d) + ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size-1, y_data.r_size-1, y_data.c_size-1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex * )speex_alloc(size * sizeof(Complex));
	}
	else if(size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Add1(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
ComplexMatrix ComplexMatAddOp2(ComplexMatrix x_data, Complex y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if ( x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "403 Error: ComplexMatrix(0:%d, 0:%d) + Complex Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Add1(x_data.data[i], y_data);
	}
	return out_data;
}
ComplexMatrix ComplexMatAddOp3(Complex x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = y_data.r_size * y_data.c_size;
	if (y_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "403 Error: Complex + ComplexMatrix(0:%d, 0:%d) Failed\n", y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = y_data.r_size;
	out_data.c_size = y_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Add1(x_data, y_data.data[i]);
	}
	return out_data;
}

ComplexMatrix ComplexMatMinusOp1(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "404 Error: ComplexMatrix(0:%d, 0:%d) - ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Minus1(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
ComplexMatrix ComplexMatMinusOp2(ComplexMatrix x_data, Complex y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "404 Error: ComplexMatrix(0:%d, 0:%d) - Complex Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Minus1(x_data.data[i], y_data);
	}
	return out_data;
}
ComplexMatrix ComplexMatMinusOp3(Complex x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = y_data.r_size * y_data.c_size;
	if (y_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "404 Error: Complex - ComplexMatrix(0:%d, 0:%d) Failed\n", y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = y_data.r_size;
	out_data.c_size = y_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Minus1(x_data, y_data.data[i]);
	}
	return out_data;
}

ComplexMatrix ComplexMatDotMultiOp1(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "405 Error: ComplexMatrix(0:%d, 0:%d) .* ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Multi1(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
ComplexMatrix ComplexMatDotMultiOp2(ComplexMatrix x_data, Complex y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "405 Error: ComplexMatrix(0:%d, 0:%d) .* Complex Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Multi1(x_data.data[i], y_data);
	}
	return out_data;
}
ComplexMatrix ComplexMatDotMultiOp3(Complex x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = y_data.r_size * y_data.c_size;
	if (y_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "405 Error: Complex .* ComplexMatrix(0:%d, 0:%d) Failed\n", y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = y_data.r_size;
	out_data.c_size = y_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Multi1(x_data, y_data.data[i]);
	}
	return out_data;
}

ComplexMatrix ComplexMatDotDivOp1(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "406 Error: ComplexMatrix(0:%d, 0:%d) ./ ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Div1(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
ComplexMatrix ComplexMatDotDivOp2(ComplexMatrix x_data, Complex y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "406 Error: ComplexMatrix(0:%d, 0:%d) ./ Complex Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Div1(x_data.data[i], y_data);
	}
	return out_data;
}
ComplexMatrix ComplexMatDotDivOp3(Complex x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = y_data.r_size * y_data.c_size;
	if (y_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "406 Error: Complex ./ ComplexMatrix(0:%d, 0:%d) Failed\n", y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = y_data.r_size;
	out_data.c_size = y_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Div1(x_data, y_data.data[i]);
	}
	return out_data;
}

ComplexMatrix ComplexMatMultiOp(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	if (x_data.data == NULL || y_data.data == NULL || x_data.c_size != y_data.r_size || x_data.r_size * x_data.c_size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "407 Error: ComplexMatrix(0:%d, 0:%d) * ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	int size = x_data.r_size * y_data.c_size;
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = y_data.c_size;

	int i = 0, j = 0, k = 0;
	for (i = 0; i < x_data.r_size; i++)
	{
		for (j = 0; j < y_data.c_size; j++)
		{
			out_data.data[i * y_data.c_size + j].real = 0.0f;
			out_data.data[i * y_data.c_size + j].image = 0.0f;
			for (k = 0; k < x_data.c_size; k++)
			{
				out_data.data[i * y_data.c_size + j] = Add1(out_data.data[i * y_data.c_size + j], Multi1(x_data.data[i * x_data.c_size + k], y_data.data[k * y_data.c_size + j]));
			}
		}
	}
	return out_data;
}

ComplexMatrix ComplexMatConjOp(ComplexMatrix x_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "408 Error: ComplexMatrix(0:%d, 0:%d)^.* \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Conj(x_data.data[i]);
	}
	return out_data;
}
ComplexMatrix ComplexMatTransOp(ComplexMatrix x_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "409 Error: ComplexMatrix(0:%d, 0:%d)^.T \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.c_size;
	out_data.c_size = x_data.r_size;

	int i = 0, j = 0;
	if (x_data.data == out_data.data)
	{
		ComplexMatrix tmp_data = NewComplexMatrix(out_data.r_size, out_data.c_size);
		for (i = 0; i < x_data.r_size; i++)
		{
			for (j = 0; j < x_data.c_size; j++)
			{
				tmp_data.data[j * tmp_data.c_size + i] = x_data.data[i * x_data.c_size + j];
			}
		}
		SPEEX_COPY(out_data.data, tmp_data.data, size);
		tmp_data = FreeComplexMatrix(tmp_data);
	}
	else
	{
		for ( i = 0; i < x_data.r_size; i++)
		{
			for ( j = 0; j < x_data.c_size; j++)
			{
				out_data.data[j * out_data.c_size + i] = x_data.data[i * x_data.c_size + j];
			}
		}
	}
	return out_data;
}
ComplexMatrix ComplexMatConjTransOp(ComplexMatrix x_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "410 Error: ComplexMatrix(0:%d, 0:%d)^.*T \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.c_size;
	out_data.c_size = x_data.r_size;
	
	int i = 0, j = 0;
	if (x_data.data == out_data.data)
	{
		ComplexMatrix tmp_data = NewComplexMatrix(out_data.r_size, out_data.c_size);
		for (i = 0; i < x_data.r_size; i++)
		{
			for (j = 0; j < x_data.c_size; j++)
			{
				tmp_data.data[j * tmp_data.c_size + i] = Conj(x_data.data[i * x_data.c_size + j]);
			}
		}
		SPEEX_COPY(out_data.data, tmp_data.data, size);
		tmp_data = FreeComplexMatrix(tmp_data);
	}
	else
	{
		for (i = 0; i < x_data.r_size; i++)
		{
			for (j = 0; j < x_data.c_size; j++)
			{
				out_data.data[j * out_data.c_size + i] = Conj(x_data.data[i * x_data.c_size + j]);
			}
		}
	}
	return out_data;
}
ComplexMatrix ComplexMatDiagOp(ComplexMatrix x_data, ComplexMatrix out_data)
{
	if (IsEmpltyOfComplexMatrix(x_data))
	{
		fprintf(stderr, "410 Error: ComplexMatDiagOp Empty ComplexMatrix\n");
		exit(1);
	}
	int size = SKV_MIN(x_data.r_size, x_data.c_size);
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = size;
	out_data.c_size = 1;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i * out_data.c_size + 0] = x_data.data[i * x_data.c_size + i];
	}
	return out_data;
}
Complex ComplexMatTraceOp(ComplexMatrix x_data)
{
	if (IsEmpltyOfComplexMatrix(x_data))
	{
		fprintf(stderr, "410 Error: ComplexMatTraceOp Empty ComplexMatrix\n");
		exit(1);
	}
	Complex r = {0.0f, 0.0f};
	int size = SKV_MIN(x_data.r_size, x_data.c_size);
	int i = 0;
	for ( i = 0; i < size; i++)
	{
		r = Add1(r, x_data.data[i * x_data.c_size + i]);
	}
	return r;
}

ComplexMatrix ComplexMatMeanOp(ComplexMatrix x_data, int rORc, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "431 Error: Mean(ComplexMatrix(0:%d, 0:%d)) %d\n", x_data.r_size - 1, x_data.c_size - 1, rORc);
		exit(1);
	}
	size = rORc == 1 ? x_data.r_size : x_data.c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	int i = 0, j = 0;
	Complex tmp;
	if (rORc == 1)
	{
		out_data.r_size = x_data.r_size;
		out_data.c_size = 1;

		for (i = 0; i < x_data.r_size; i++)
		{
			tmp.real = 0.0f;
			tmp.image = 0.0f;
			for (j = 0; j < x_data.c_size; j++)
			{
				tmp = Add1(tmp, x_data.data[i * x_data.c_size + j]);
			}
			tmp = Div3(tmp, x_data.c_size);
			ComplexMatrixSetAt(out_data, i, 0, tmp);
		}
	}
	else
	{
		out_data.r_size = 1;
		out_data.c_size = x_data.c_size;
		for (j = 0; j < x_data.c_size; j++)
		{
			tmp.real = 0.0f;
			tmp.image = 0.0f;
			for (i = 0; i < x_data.r_size; i++)
			{
				tmp = Add1(tmp, x_data.data[i * x_data.c_size + j]);
			}
			tmp = Div3(tmp, x_data.r_size);
			ComplexMatrixSetAt(out_data, 0, j, tmp);
		}
	}
	return out_data;
}
Complex ComplexMatMeanMeanOp(ComplexMatrix x_data, int s_r, int s_c, int e_r, int e_c)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "432 Error: MeanMean(ComplexMatrix(%d:%d, %d:%d))\n", s_r, s_c, e_r, e_c);
		exit(1);
	}
	int i = 0, j = 0;
	int count = 0;
	Complex tmp;
	tmp.real = 0.0f;
	tmp.image = 0.0f;
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			tmp = Add1(tmp, x_data.data[i * x_data.c_size + j]);
			count = count + 1;
		}
	}
	if (count != 0)
	{
		tmp = Div3(tmp, count);
	}
	return tmp;
}
ComplexMatrix ComplexMatSumOp(ComplexMatrix x_data, int rORc, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "433 Error: Sum(ComplexMatrix(0:%d, 0:%d)) %d\n", x_data.r_size - 1, x_data.c_size - 1, rORc);
		exit(1);
	}
	size = rORc == 1 ? x_data.r_size : x_data.c_size;
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	int i = 0, j = 0;
	Complex tmp;
	if (rORc == 1)
	{
		out_data.r_size = x_data.r_size;
		out_data.c_size = 1;

		for (i = 0; i < x_data.r_size; i++)
		{
			tmp.real = 0.0f;
			tmp.image = 0.0f;
			for (j = 0; j < x_data.c_size; j++)
			{
				tmp = Add1(tmp, x_data.data[i * x_data.c_size + j]);
			}
			ComplexMatrixSetAt(out_data, i, 0, tmp);
		}
	}
	else
	{
		out_data.r_size = 1;
		out_data.c_size = x_data.c_size;
		for (j = 0; j < x_data.c_size; j++)
		{
			tmp.real = 0.0f;
			tmp.image = 0.0f;
			for (i = 0; i < x_data.r_size; i++)
			{
				tmp = Add1(tmp, x_data.data[i * x_data.c_size + j]);
			}
			ComplexMatrixSetAt(out_data, 0, j, tmp);
		}
	}
	return out_data;
}
Complex ComplexMatSumSumOp(ComplexMatrix x_data, int s_r, int s_c, int e_r, int e_c)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "434 Error: SumSum(ComplexMatrix(%d:%d, %d:%d))\n", s_r, s_c, e_r, e_c);
		exit(1);
	}
	int i = 0, j = 0;
	Complex tmp = { 0.0f, 0.0f };
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			tmp = Add1(tmp, x_data.data[i * x_data.c_size + j]);
		}
	}
	return tmp;
}
ComplexMatrix ComplexMatDynamicMeanOp(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data, int frame)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "430 Error: Mean(ComplexMatrix(0:%d, 0:%d)  ComplexMatrix(0:%d, 0:%d)) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	Complex tmp;
	tmp.real = (spx_word16_t)frame;
	tmp.image = 0.0f;
	out_data = ComplexMatDotMultiOp2(x_data, tmp, out_data);
	out_data = ComplexMatAddOp1(out_data, y_data, out_data);
	tmp.real = (spx_word16_t)(frame + 1);
	tmp.image = 0.0f;
	out_data = ComplexMatDotDivOp2(out_data, tmp, out_data);
	return out_data;
}

RealMatrix ComplexMatABSOp(ComplexMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "411 Error: |ComplexMatrix(0:%d, 0:%d)| \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_ABSC(x_data.data[i]);
	}
	return out_data;
}

RealMatrix ComplexMatPOWOp(ComplexMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "412 Error: |ComplexMatrix(0:%d, 0:%d)|.^2 \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_POWC(x_data.data[i]);
	}
	return out_data;
}
bool IsEmpltyOfComplexMatrix(ComplexMatrix x_data)
{
	if (x_data.c_size < 1 || x_data.r_size < 1 || x_data.data == NULL)
	{
		return true;
	}
	return false;
}

RealMatrix RandRealMatrix(spx_uint32_t r_size, spx_uint32_t c_size)
{
	int size = r_size * c_size;
	if (size <= 0)
	{
		fprintf(stderr, "401 Error: RandRealMatrix(0:%d, 0:%d) Failed!", r_size - 1, c_size - 1);
		exit(1);
	}
	RealMatrix st;
	st.r_size = r_size;
	st.c_size = c_size;
	st.data = (spx_word16_t *)speex_alloc(r_size * c_size * sizeof(spx_word16_t));
	int i = 0;
	for (i = 0; i < size; i++)
	{
		st.data[i] = rand() / (double)(RAND_MAX);
	}
	return st;
}
RealMatrix EyeRealMatrix(spx_uint32_t r_size, spx_uint32_t c_size)
{
	int size = r_size * c_size;
	if (size <= 0)
	{
		fprintf(stderr, "401 Error: EyeRealMatrix(0:%d, 0:%d) Failed!", r_size - 1, c_size - 1);
		exit(1);
	}
	RealMatrix st;
	st.r_size = r_size;
	st.c_size = c_size;
	st.data = (spx_word16_t *)speex_alloc(r_size * c_size * sizeof(spx_word16_t));

	int i = 0, j = 0;
	for ( i = 0; i < st.r_size; i++)
	{
		for ( j = 0; j < st.c_size; j++)
		{
			if (i == j)
			{
				st.data[i * st.c_size + j] = 1.0f;
			}
			else
			{
				st.data[i * st.c_size + j] = 0.0f;
			}
		}
	}
	return st;
}
RealMatrix NewRealMatrix(spx_uint32_t r_size, spx_uint32_t c_size)
{
	int size = r_size * c_size;
	if (size <= 0)
	{
		fprintf(stderr, "401 Error: NewRealMatrix(0:%d, 0:%d) Failed!", r_size - 1, c_size - 1);
		exit(1);
	}
	RealMatrix st;
	st.r_size = r_size;
	st.c_size = c_size;
	st.data = (spx_word16_t *)speex_alloc(r_size * c_size * sizeof(spx_word16_t));
	RealMatSetOp2(st, 0.0f);
	return st;
}
RealMatrix FreeRealMatrix(RealMatrix st)
{
	st.r_size = 0;
	st.c_size = 0;
	if (st.data != NULL)
	{
		speex_free(st.data); st.data = NULL;
	}
	return st;
}

spx_word16_t RealMatrixGetAt(RealMatrix x_data, spx_uint32_t i, spx_uint32_t j)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "415 Error: RealMatrixGetAt, NULL RealMatrixGetAt\n");
		exit(1);
	}
	if (i * x_data.c_size + j >= size)
	{
		fprintf(stderr, "415 Error: RealMatrixGetAt RealMatrix(%d, %d) Failed\n", i, j);
		exit(1);
	}
	return x_data.data[i * x_data.c_size + j];
}
void RealMatrixSetAt(RealMatrix x_data, spx_uint32_t i, spx_uint32_t j, spx_word16_t y_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "415 Error: RealMatrixSetAt, NULL RealMatrix\n");
		exit(1);
	}
	if (i * x_data.c_size + j >= size)
	{
		fprintf(stderr, "415 Error: RealMatrixSetAt RealMatrix(%d, %d) Failed\n", i, j);
		exit(1);
	}
	x_data.data[i * x_data.c_size + j] = y_data;
}

void RealMatSetOp1(RealMatrix x_data, RealMatrix y_data)
{
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size)
	{
		fprintf(stderr, "402 Error: RealMatrix(0:%d, 0:%d) = RealMatrix(0:%d, 0:%d) Failed! \n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	SPEEX_COPY(x_data.data, y_data.data, x_data.r_size * x_data.c_size);
}
void RealMatSetOp2(RealMatrix x_data, spx_word16_t y_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "402 Error: RealMatrix(0:%d, 0:%d) = Float Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	int i = 0;
	for (i = 0; i < size; i++)
	{
		x_data.data[i] = y_data;
	}
}
void RealMatSetOp3(RealMatrix x_data, spx_word16_t y_data, int s_r, int s_c, int e_r, int e_c)
{
	int r_size = e_r - s_r + 1;
	int c_size = e_c - s_c + 1;
	int size = r_size * c_size;
	if (x_data.data == NULL || r_size * c_size <= 0 || s_r < 0 || s_r >= x_data.r_size ||
		s_c < 0 || s_c >= x_data.c_size || e_r < 0 || e_r >= x_data.r_size ||
		e_c < 0 || e_c >= x_data.c_size)
	{
		fprintf(stderr, "402 Error: RealMatrix(%d:%d, %d:%d) = Float Failed\n", s_r, e_r, s_c, e_c);
		exit(1);
	}
	int i = 0, j = 0;
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			x_data.data[i * x_data.c_size + j] = y_data;
		}
	}
}

void RealMatSetOp4(RealMatrix x_data, RealMatrix y_data, int s_r, int s_c, int e_r, int e_c)
{
	int r_size = e_r - s_r + 1;
	int c_size = e_c - s_c + 1;
	int size = r_size * c_size;
	if (y_data.data == NULL || r_size * c_size <= 0 || s_r < 0 || s_r >= y_data.r_size ||
		s_c < 0 || s_c >= y_data.c_size || e_r < 0 || e_r >= y_data.r_size ||
		e_c < 0 || e_c >= y_data.c_size)
	{
		fprintf(stderr, "402 Error: RealMatrix = RealMatrix(%d:%d, %d:%d) Failed\n", s_r, e_r, s_c, e_c);
		exit(1);
	}
	if (x_data.data == NULL)
	{
		x_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
		x_data.r_size = r_size;
		x_data.c_size = c_size;
	}
	else if (size > x_data.r_size * x_data.c_size)
	{
		x_data.data = (spx_word16_t *)speex_realloc(x_data.data, size * sizeof(spx_word16_t));
		x_data.r_size = r_size;
		x_data.c_size = c_size;
	}

	int i = 0, j = 0;
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			x_data.data[(i - s_r) * x_data.c_size + (j - s_c)] = y_data.data[i * y_data.c_size + j];
		}
	}
}

void printRealMatrix(RealMatrix x_data, const char * var_name)
{
	if (x_data.data == NULL || x_data.r_size * x_data.c_size <= 0)
	{
		fprintf(stderr, "001 Error: %s(%d, %d)=NULL\n", var_name, x_data.r_size, x_data.c_size);
		return;
	}

	printf("%s(%d, %d) =\n", var_name, x_data.r_size, x_data.c_size);

	int i = 0, j = 0;
	for (i = 0; i < x_data.r_size; i++)
	{
		printf("               ");
		for (j = 0; j < x_data.c_size; j++)
		{
			printf("%.3f ", x_data.data[i * x_data.c_size + j]);
		}
		printf("\n");
	}
}
void fprintRealMatrix(FILE * fp, RealMatrix x_data, const char * var_name)
{
	if (fp == NULL)
	{
		fprintf(stderr, "001 Error: File cann't be open\n");
		return;
	}
	if (x_data.data == NULL || x_data.r_size * x_data.c_size <= 0)
	{
		fprintf(fp, "%s(%d, %d)=NULL\n", var_name, x_data.r_size, x_data.c_size);
		return;
	}

	fprintf(fp, "%s(%d, %d) =\n", var_name, x_data.r_size, x_data.c_size);

	int i = 0, j = 0;
	for (i = 0; i < x_data.r_size; i++)
	{
		fprintf(fp, "               ");
		for (j = 0; j < x_data.c_size; j++)
		{
			fprintf(fp, "%f ", x_data.data[i * x_data.c_size + j]);
		}
		fprintf(fp, "\n");
	}
}
void fprintRealMatrix1(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c, const char * var_name, const char * filename)
{
	if (x_data.data == NULL || x_data.r_size * x_data.c_size <= 0)
	{
		fprintf(stderr, "x_data(0:%d, 0:%d)=NULL\n", x_data.r_size, x_data.c_size);
		return;
	}
	FILE * fp = NULL;
	fp = fopen(filename, "at");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Cann't open %s\n", filename);
		return;
	}

	fprintf(fp, "%s\n", var_name);
	int i = 0, j = 0;
	for (i = s_r; i <= e_r && i < x_data.r_size; i++)
	{
		for (j = s_c; j <= e_c && j < x_data.c_size; j++)
		{
			fprintf(fp, "%f ", x_data.data[i * x_data.c_size + j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

RealMatrix RealMatAddOp1(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "403 Error: RealMatrix(0:%d, 0:%d) + RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data.data[i] + y_data.data[i];
	}
	return out_data;
}
RealMatrix RealMatAddOp2(RealMatrix x_data, spx_word16_t y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "403 Error: RealMatrix(0:%d, 0:%d) + Float Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data.data[i] + y_data;
	}
	return out_data;
}
RealMatrix RealMatAddOp3(spx_word16_t x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = y_data.r_size * y_data.c_size;
	if (y_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "403 Error: Float + RealMatrix(0:%d, 0:%d) Failed\n", y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = y_data.r_size;
	out_data.c_size = y_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data + y_data.data[i];
	}
	return out_data;
}

RealMatrix RealMatMinusOp1(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "404 Error: RealMatrix(0:%d, 0:%d) - RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data.data[i] - y_data.data[i];
	}
	return out_data;
}
RealMatrix RealMatMinusOp2(RealMatrix x_data, spx_word16_t y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "404 Error: RealMatrix(0:%d, 0:%d) - Float Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data.data[i] - y_data;
	}
	return out_data;
}
RealMatrix RealMatMinusOp3(spx_word16_t x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = y_data.r_size * y_data.c_size;
	if (y_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "404 Error: Float - RealMatrix(0:%d, 0:%d) Failed\n", y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = y_data.r_size;
	out_data.c_size = y_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data - y_data.data[i];
	}
	return out_data;
}

RealMatrix RealMatDotMultiOp1(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "405 Error: RealMatrix(0:%d, 0:%d) .* RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data.data[i] * y_data.data[i];
	}
	return out_data;
}
RealMatrix RealMatDotMultiOp2(RealMatrix x_data, spx_word16_t y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "405 Error: RealMatrix(0:%d, 0:%d) .* Float Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data.data[i] * y_data;
	}
	return out_data;
}
RealMatrix RealMatDotMultiOp3(spx_word16_t x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = y_data.r_size * y_data.c_size;
	if (y_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "405 Error: Float .* RealMatrix(0:%d, 0:%d) Failed\n", y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = y_data.r_size;
	out_data.c_size = y_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data * y_data.data[i];
	}
	return out_data;
}

RealMatrix RealMatDotDivOp1(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "406 Error: RealMatrix(0:%d, 0:%d) ./ RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (y_data.data[ i ] == 0)
		{
			if (x_data.data[i] == 0)
			{
				out_data.data[i] = 0;
			}
			else
			{
				out_data.data[i] = x_data.data[i] > 0 ? FLT_MAX : FLT_MIN;
			}
		}
		else
		{
			out_data.data[i] = x_data.data[i] / y_data.data[i];
		}
	}
	return out_data;
}
RealMatrix RealMatDotDivOp2(RealMatrix x_data, spx_word16_t y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "406 Error: RealMatrix(0:%d, 0:%d) ./ Float Failed\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (y_data == 0)
		{
			if (x_data.data[i] == 0)
			{
				out_data.data[i] = 0;
			}
			else
			{
				out_data.data[i] = x_data.data[i] > 0 ? FLT_MAX : FLT_MIN;
			}
		}
		else
		{
			out_data.data[i] = x_data.data[i] / y_data;
		}
	}
	return out_data;
}
RealMatrix RealMatDotDivOp3(spx_word16_t x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = y_data.r_size * y_data.c_size;
	if (y_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "406 Error: Float ./ RealMatrix(0:%d, 0:%d) Failed\n", y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = y_data.r_size;
	out_data.c_size = y_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (y_data.data[i] == 0)
		{
			if (x_data == 0)
			{
				out_data.data[i] = 0;
			}
			else
			{
				out_data.data[i] = x_data > 0 ? FLT_MAX : FLT_MIN;
			}
		}
		else
		{
			out_data.data[i] = x_data / y_data.data[i];
		}
	}
	return out_data;
}

RealMatrix RealMatMultiOp(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data)
{
	if (x_data.data == NULL || y_data.data == NULL || x_data.c_size != y_data.r_size || x_data.r_size * x_data.c_size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "407 Error: RealMatrix(0:%d, 0:%d) * RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	int size = x_data.r_size * y_data.c_size;
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = y_data.c_size;

	int i = 0, j = 0, k = 0;
	for (i = 0; i < x_data.r_size; i++)
	{
		for (j = 0; j < y_data.c_size; j++)
		{
			out_data.data[i * y_data.c_size + j] = 0.0f;
			for (k = 0; k < x_data.c_size; k++)
			{
				out_data.data[i * y_data.c_size + j] = out_data.data[i * y_data.c_size + j] + x_data.data[i * x_data.c_size + k] * y_data.data[k * y_data.c_size + j];
			}
		}
	}
	return out_data;
}

RealMatrix RealMatTransOp(RealMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "409 Error: RealMatrix(0:%d, 0:%d)^.T \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.c_size;
	out_data.c_size = x_data.r_size;

	int i = 0, j = 0;
	if (x_data.data == out_data.data)
	{
		RealMatrix tmp_data = NewRealMatrix(out_data.r_size, out_data.c_size);
		for (i = 0; i < x_data.r_size; i++)
		{
			for (j = 0; j < x_data.c_size; j++)
			{
				tmp_data.data[j * tmp_data.c_size + i] = x_data.data[i * x_data.c_size + j];
			}
		}
		SPEEX_COPY(out_data.data, tmp_data.data, size);
		tmp_data = FreeRealMatrix(tmp_data);
	}
	else
	{
		for (i = 0; i < x_data.r_size; i++)
		{
			for (j = 0; j < x_data.c_size; j++)
			{
				out_data.data[j * out_data.c_size + i] = x_data.data[i * x_data.c_size + j];
			}
		}
	}
	return out_data;
}

RealMatrix RealMatABSOp(RealMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "411 Error: |RealMatrix(0:%d, 0:%d)| \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_ABSR(x_data.data[i]);
	}
	return out_data;
}

RealMatrix RealMatPowOp(RealMatrix x_data, float x, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "413 Error: Pow(RealMatrix(0:%d, 0:%d), %f) \n", x_data.r_size - 1, x_data.c_size - 1, x);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = pow(x_data.data[i], x);
	}
	return out_data;
}
RealMatrix RealMatSqrtOp(RealMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "414 Error: sqrt(RealMatrix(0:%d, 0:%d)) \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (x_data.data[i] < 0)
		{
			out_data.data[i] = 0;
		}
		else
		{
			out_data.data[i] = SKV_SQRTF(x_data.data[i]);
		}
	}
	return out_data;
}
RealMatrix RealMatPow2Op(RealMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "415 Error: RealMatrix(0:%d, 0:%d)^2 \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = x_data.data[i] * x_data.data[i];
	}
	return out_data;
}
RealMatrix RealMatExpOp(RealMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "416 Error: exp(RealMatrix(0:%d, 0:%d)) \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_EXP(x_data.data[i]);
	}
	return out_data;
}
RealMatrix RealMatLogOp(RealMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "417 Error: log(RealMatrix(0:%d, 0:%d)) \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (x_data.data[i] <= 0)
		{
			out_data.data[i] = FLT_MIN;
		}
		else
		{
			out_data.data[i] = SKV_LOG(x_data.data[i]);
		}
	}
	return out_data;
}
RealMatrix RealMatLog2Op(RealMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "418 Error: log2(RealMatrix(0:%d, 0:%d)) \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (x_data.data[i] <= 0)
		{
			out_data.data[i] = FLT_MIN;
		}
		else
		{
			out_data.data[i] = SKV_LOG2(x_data.data[i]);
		}
	}
	return out_data;
}
RealMatrix RealMatLog10Op(RealMatrix x_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "419 Error: log10(RealMatrix(0:%d, 0:%d)) \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (x_data.data[i] <= 0)
		{
			out_data.data[i] = FLT_MIN;
		}
		else
		{
			out_data.data[i] = SKV_LOG10(x_data.data[i]);
		}
	}
	return out_data;
}

RealMatrix RealMatDiagOp(RealMatrix x_data, RealMatrix out_data)
{
	if (IsEmpltyOfRealMatrix(x_data))
	{
		fprintf(stderr, "410 Error: RealMatDiagOp Empty RealMatrix\n");
		exit(1);
	}
	int size = SKV_MIN(x_data.r_size, x_data.c_size);
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = size;
	out_data.c_size = 1;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i * out_data.c_size + 0] = x_data.data[i * x_data.c_size + i];
	}
	return out_data;
}
spx_word16_t RealMatTraceOp(RealMatrix x_data)
{
	if (IsEmpltyOfRealMatrix(x_data))
	{
		fprintf(stderr, "410 Error: RealMatTraceOp Empty RealMatrix\n");
		exit(1);
	}
	spx_word16_t r = 0.0f;
	int size = SKV_MIN(x_data.r_size, x_data.c_size);
	int i = 0;
	for (i = 0; i < size; i++)
	{
		r = r + x_data.data[i * x_data.c_size + i];
	}
	return r;
}

RealMatrix RealMatBandOp(RealMatrix x_data, spx_word16_t low_band, spx_word16_t up_band, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "420 Error: band(RealMatrix(0:%d, 0:%d)) \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_MAX(out_data.data[i], low_band);
		out_data.data[i] = SKV_MIN(out_data.data[i], up_band);
	}
	return out_data;
}

RealMatrix RealMatLowBandOp(RealMatrix x_data, spx_word16_t low_band, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "420 Error: band(RealMatrix(0:%d, 0:%d)) \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_MAX(out_data.data[i], low_band);
	}
	return out_data;
}

RealMatrix RealMatUpBandOp(RealMatrix x_data, spx_word16_t up_band, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "420 Error: band(RealMatrix(0:%d, 0:%d)) \n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_MIN(out_data.data[i], up_band);
	}
	return out_data;
}
RealMatrix RealMatMeanOp(RealMatrix x_data, int rORc, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "421 Error: Mean(RealMatrix(0:%d, 0:%d)) %d\n", x_data.r_size - 1, x_data.c_size - 1, rORc);
		exit(1);
	}
	size = rORc == 1 ? x_data.r_size : x_data.c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	int i = 0, j = 0;
	spx_word16_t tmp;
	if (rORc == 1)
	{
		out_data.r_size = x_data.r_size;
		out_data.c_size = 1;
		for (i = 0; i < x_data.r_size; i++)
		{
			tmp = 0;
			for ( j = 0; j < x_data.c_size; j++)
			{
				tmp = tmp + x_data.data[i * x_data.c_size + j];
			}
			tmp = tmp / x_data.c_size;
			RealMatrixSetAt(out_data, i, 0, tmp);
		}
	}
	else
	{
		out_data.r_size = 1;
		out_data.c_size = x_data.c_size;
		for (j = 0; j < x_data.c_size; j++)
		{
			tmp = 0;
			for (i = 0; i < x_data.r_size; i++)
			{
				tmp = tmp + x_data.data[i * x_data.c_size + j];
			}
			tmp = tmp / x_data.r_size;
			RealMatrixSetAt(out_data, 0, j, tmp);
		}
	}
	return out_data;
}
spx_word16_t RealMatMeanMeanOp(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "422 Error: MeanMean(RealMatrix(0:%d, 0:%d))\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	int i = 0, j = 0;
	int count = 0;
	spx_word16_t tmp = 0.0f;
	for ( i = s_r; i <= e_r; i++)
	{
		for ( j = s_c; j <= e_c; j++)
		{
			tmp = tmp + x_data.data[i * x_data.c_size + j];
			count = count + 1;
		}
	}
	if (count != 0)
	{
		tmp = tmp / count;
	}
	return tmp;
}
RealMatrix RealMatSumOp(RealMatrix x_data, int rORc, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "423 Error: Sum(RealMatrix(0:%d, 0:%d)) %d\n", x_data.r_size - 1, x_data.c_size - 1, rORc);
		exit(1);
	}
	size = rORc == 1 ? x_data.r_size : x_data.c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	int i = 0, j = 0;
	spx_word16_t tmp;
	if (rORc == 1)
	{
		out_data.r_size = x_data.r_size;
		out_data.c_size = 1;

		for (i = 0; i < x_data.r_size; i++)
		{
			tmp = 0;
			for (j = 0; j < x_data.c_size; j++)
			{
				tmp = tmp + x_data.data[i * x_data.c_size + j];
			}
			RealMatrixSetAt(out_data, i, 0, tmp);
		}
	}
	else
	{
		out_data.r_size = 1;
		out_data.c_size = x_data.c_size;
		for (j = 0; j < x_data.c_size; j++)
		{
			tmp = 0;
			for (i = 0; i < x_data.r_size; i++)
			{
				tmp = tmp + x_data.data[i * x_data.c_size + j];
			}
			RealMatrixSetAt(out_data, 0, j, tmp);
		}
	}
	return out_data;
}
spx_word16_t RealMatSumSumOp(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "424 Error: SumSum(RealMatrix(0:%d, 0:%d))\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	int i = 0, j = 0;
	spx_word16_t tmp = 0.0f;
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			tmp = tmp + x_data.data[i * x_data.c_size + j];
		}
	}
	return tmp;
}
RealMatrix RealMatMaxOp(RealMatrix x_data, int rORc, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "425 Error: Max(RealMatrix(0:%d, 0:%d)) %d\n", x_data.r_size - 1, x_data.c_size - 1, rORc);
		exit(1);
	}
	size = rORc == 1 ? x_data.r_size : x_data.c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	int i = 0, j = 0;
	spx_word16_t tmp;
	if (rORc == 1)
	{
		out_data.r_size = x_data.r_size;
		out_data.c_size = 1;

		for (i = 0; i < x_data.r_size; i++)
		{
			tmp = x_data.data[i * x_data.c_size];
			for (j = 1; j < x_data.c_size; j++)
			{
				tmp = SKV_MAX(tmp, x_data.data[i * x_data.c_size + j]);
			}
			RealMatrixSetAt(out_data, i, 0, tmp);
		}
	}
	else
	{
		out_data.r_size = 1;
		out_data.c_size = x_data.c_size;
		for (j = 0; j < x_data.c_size; j++)
		{
			tmp = x_data.data[j];
			for (i = 1; i < x_data.r_size; i++)
			{
				tmp = SKV_MAX(tmp, x_data.data[i * x_data.c_size + j]);
			}
			RealMatrixSetAt(out_data, 0, j, tmp);
		}
	}
	return out_data;
}
spx_word16_t RealMatMaxMaxOp(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "426 Error: MaxMax(RealMatrix(0:%d, 0:%d))\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	int i = 0, j = 0;
	spx_word16_t tmp = x_data.data[s_r * x_data.c_size + s_c];
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			tmp = SKV_MAX(tmp, x_data.data[i * x_data.c_size + j]);
		}
	}
	return tmp;
}
RealMatrix RealMatMinOp(RealMatrix x_data, int rORc, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "427 Error: Min(RealMatrix(0:%d, 0:%d)) %d\n", x_data.r_size - 1, x_data.c_size - 1, rORc);
		exit(1);
	}
	size = rORc == 1 ? x_data.r_size : x_data.c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	int i = 0, j = 0;
	spx_word16_t tmp;
	if (rORc == 1)
	{
		out_data.r_size = x_data.r_size;
		out_data.c_size = 1;

		for (i = 0; i < x_data.r_size; i++)
		{
			tmp = x_data.data[i * x_data.c_size];
			for (j = 1; j < x_data.c_size; j++)
			{
				tmp = SKV_MIN(tmp, x_data.data[i * x_data.c_size + j]);
			}
			RealMatrixSetAt(out_data, i, 0, tmp);
		}
	}
	else
	{
		out_data.r_size = 1;
		out_data.c_size = x_data.c_size;
		for (j = 0; j < x_data.c_size; j++)
		{
			tmp = x_data.data[j];
			for (i = 1; i < x_data.r_size; i++)
			{
				tmp = SKV_MIN(tmp, x_data.data[i * x_data.c_size + j]);
			}
			RealMatrixSetAt(out_data, 0, j, tmp);
		}
	}
	return out_data;
}
spx_word16_t RealMatMinMinOp(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || size <= 0)
	{
		fprintf(stderr, "428 Error: MinMin(RealMatrix(0:%d, 0:%d))\n", x_data.r_size - 1, x_data.c_size - 1);
		exit(1);
	}
	int i = 0, j = 0;
	spx_word16_t tmp = x_data.data[s_r * x_data.c_size + s_c];
	for (i = s_r; i <= e_r; i++)
	{
		for (j = s_c; j <= e_c; j++)
		{
			tmp = SKV_MIN(tmp, x_data.data[i * x_data.c_size + j]);
		}
	}
	return tmp;
}
bool IsEmpltyOfRealMatrix(RealMatrix x_data)
{
	if (x_data.c_size < 1 || x_data.r_size < 1 || x_data.data == NULL)
	{
		return true;
	}
	return false;
}
RealMatrix RealMatDynamicMeanOp(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data, int frame)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "430 Error: Mean(RealMatrix(0:%d, 0:%d)  RealMatrix(0:%d, 0:%d)) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	out_data = RealMatDotMultiOp2(x_data, frame, out_data);
	out_data = RealMatAddOp1(out_data, y_data, out_data);
	out_data = RealMatDotDivOp2(out_data, frame + 1, out_data);
	return out_data;
}
RealMatrix RealMatDynamicMaxOp(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "431 Error: Max(RealMatrix(0:%d, 0:%d)  RealMatrix(0:%d, 0:%d)) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for ( i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_MAX(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
RealMatrix RealMatDynamicMinOp(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "432 Error: Min(RealMatrix(0:%d, 0:%d)  RealMatrix(0:%d, 0:%d)) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = SKV_MIN(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}


ComplexMatrix ComplexRealMatAddOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "403 Error: ComplexMatrix(0:%d, 0:%d) + RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Add3(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
ComplexMatrix RealComplexMatAddOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "403 Error: RealMatrix(0:%d, 0:%d) + ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Add2(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}

ComplexMatrix ComplexRealMatMinusOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "404 Error: ComplexMatrix(0:%d, 0:%d) - RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Minus3(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
ComplexMatrix RealComplexMatMinusOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "404 Error: ComplexMatrix(0:%d, 0:%d) - RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Minus2(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}

ComplexMatrix ComplexRealMatMultiOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data)
{
	if (x_data.data == NULL || y_data.data == NULL || x_data.c_size != y_data.r_size || x_data.r_size * x_data.c_size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "407 Error: ComplexMatrix(0:%d, 0:%d) * RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	int size = x_data.r_size * y_data.c_size;
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = y_data.c_size;

	int i = 0, j = 0, k = 0;
	for (i = 0; i < x_data.r_size; i++)
	{
		for (j = 0; j < y_data.c_size; j++)
		{
			out_data.data[i * y_data.c_size + j].real = 0.0f;
			out_data.data[i * y_data.c_size + j].image = 0.0f;
			for (k = 0; k < x_data.c_size; k++)
			{
				out_data.data[i * y_data.c_size + j] = Add1(out_data.data[i * y_data.c_size + j], Multi3(x_data.data[i * x_data.c_size + k], y_data.data[k * y_data.c_size + j]));
			}
		}
	}
	return out_data;
}
ComplexMatrix RealComplexMatMultiOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	if (x_data.data == NULL || y_data.data == NULL || x_data.c_size != y_data.r_size || x_data.r_size * x_data.c_size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "407 Error: RealMatrix(0:%d, 0:%d) * ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	int size = x_data.r_size * y_data.c_size;
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = y_data.c_size;

	int i = 0, j = 0, k = 0;
	for (i = 0; i < x_data.r_size; i++)
	{
		for (j = 0; j < y_data.c_size; j++)
		{
			out_data.data[i * y_data.c_size + j].real = 0.0f;
			out_data.data[i * y_data.c_size + j].image = 0.0f;
			for (k = 0; k < x_data.c_size; k++)
			{
				out_data.data[i * y_data.c_size + j] = Add1(out_data.data[i * y_data.c_size + j], Multi2(x_data.data[i * x_data.c_size + k], y_data.data[k * y_data.c_size + j]));
			}
		}
	}
	return out_data;
}

ComplexMatrix ComplexRealMatDotMultiOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "405 Error: ComplexMatrix(0:%d, 0:%d) .* RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Multi3(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
ComplexMatrix RealComplexMatDotMultiOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "405 Error: RealMatrix(0:%d, 0:%d) .* ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Multi2(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}

ComplexMatrix ComplexRealMatDotDivOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "406 Error: ComplexMatrix(0:%d, 0:%d) ./ RealMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Div3(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}
ComplexMatrix RealComplexMatDotDivOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data)
{
	int size = x_data.r_size * x_data.c_size;
	if (x_data.data == NULL || y_data.data == NULL || x_data.r_size != y_data.r_size || x_data.c_size != y_data.c_size || size <= 0 || y_data.r_size * y_data.c_size <= 0)
	{
		fprintf(stderr, "406 Error: RealMatrix(0:%d, 0:%d) ./ ComplexMatrix(0:%d, 0:%d) Failed\n", x_data.r_size - 1, x_data.c_size - 1, y_data.r_size - 1, y_data.c_size - 1);
		exit(1);
	}
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size > out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	out_data.r_size = x_data.r_size;
	out_data.c_size = x_data.c_size;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data.data[i] = Div2(x_data.data[i], y_data.data[i]);
	}
	return out_data;
}


struct SKVRealBuffer_
{
	int flag;
	int size;
	int r_size;
	int c_size;
	int write_ptr;
	spx_word16_t ** data;
	spx_word16_t * sum;
};
SKVRealBuffer *skv_real_buffer_init(int size, int matrix_r_size, int matrix_c_size, int flag)
{
	if (size < 1 || matrix_r_size < 1 || matrix_c_size < 1)
	{
		fprintf(stderr, "701 Error:skv_buffer_init Failed\n");
		return NULL;
	}
	SKVRealBuffer *st = (SKVRealBuffer *)speex_alloc(sizeof(SKVRealBuffer));

	int i = 0;
	st->data = (spx_word16_t **)speex_alloc(size * sizeof(spx_word16_t *));
	for (i = 0; i < size; i++)
	{
		st->data[i] = (spx_word16_t *)speex_alloc(matrix_r_size * matrix_c_size * sizeof(spx_word16_t));
	}
	st->sum = (spx_word16_t *)speex_alloc(matrix_r_size * matrix_c_size * sizeof(spx_word16_t));

	st->flag = flag == 0? 0: 1;
	st->size = size;
	st->r_size = matrix_r_size;
	st->c_size = matrix_c_size;
	st->write_ptr = 0;
	skv_real_buffer_clear(st);
	return st;
}

void skv_real_buffer_destroy(SKVRealBuffer *st)
{
	if (st == NULL)
	{
		return;
	}
	int i = 0;
	for (i = 0; i < st->size; i++)
	{
		speex_free(st->data[i]); st->data[i] = NULL;
	}
	speex_free(st->data); st->data = NULL;
	speex_free(st->sum); st->sum = NULL;
	speex_free(st); st = NULL;
}

void skv_real_buffer_clear(SKVRealBuffer *st)
{
	if ( st == NULL )
	{
		return;
	}
	int i = 0;
	for (i = 0; i < st->size; i++)
	{
		SPEEX_MEMSET(st->data[i], 0, st->r_size * st->c_size);
	}
	SPEEX_MEMSET(st->sum, 0, st->r_size * st->c_size);
}

bool skv_real_buffer_write(SKVRealBuffer *st, RealMatrix data)
{
	if (st == NULL || IsEmpltyOfRealMatrix(data) || data.r_size != st->r_size || data.c_size != st->c_size)
	{
		fprintf(stderr, "702 Error: skv_real_buffer_write Failed\n");
		return false;
	}
	RealMatrix mSum, mElement;
	mSum.r_size = st->r_size;
	mSum.c_size = st->c_size;
	mSum.data = st->sum;
	mElement.r_size = st->r_size;
	mElement.c_size = st->c_size;
	if (st->flag)
	{
		mSum = RealMatAddOp1(mSum, data, mSum);
		mElement.data = st->data[st->write_ptr];
		mSum = RealMatMinusOp1(mSum, mElement, mSum);
	}
	mElement.data = st->data[st->write_ptr];
	RealMatSetOp1(mElement, data);
	st->write_ptr = (st->write_ptr + 1) % st->size;
	return true;
}

RealMatrix skv_real_buffer_read(SKVRealBuffer *st, RealMatrix out_data, int iTh)
{
	if ( st == NULL || st->data == NULL || iTh < 0 || iTh >= st->size)
	{
		fprintf(stderr, "703 Error: skv_real_buffer_read Failed\n");
		return out_data;
	}
	int size = st->r_size * st->c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size != out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}

	RealMatrix mElement;
	mElement.r_size = st->r_size;
	mElement.c_size = st->c_size;
	int write_ptr = st->write_ptr;
	write_ptr = (write_ptr + iTh) % st->size;
	mElement.data = st->data[write_ptr];
	RealMatSetOp1(out_data, mElement);
	return out_data;
}

spx_word16_t* skv_real_buffer_scan(SKVRealBuffer *st, int iTh)
{
	if (st == NULL || iTh < 0 || iTh >= st->size)
	{
		fprintf(stderr, "703 Error: skv_real_buffer_scan Failed\n");
		return NULL;
	}

	int write_ptr = st->write_ptr;
	write_ptr = (write_ptr + iTh) % st->size;
	return st->data[write_ptr];
}

RealMatrix skv_real_buffer_mean(SKVRealBuffer *st, RealMatrix out_data)
{
	if (st == NULL || st->data == NULL)
	{
		fprintf(stderr, "704 Error: skv_real_buffer_mean Failed\n");
		return out_data;
	}
	int size = st->r_size * st->c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size != out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	if (st->flag)
	{
		RealMatrix mSum;
		mSum.r_size = st->r_size;
		mSum.c_size = st->c_size;
		mSum.data = st->sum;
		RealMatSetOp1(out_data, mSum);
		out_data = RealMatDotDivOp2(out_data, st->size, out_data);
	}
	else
	{
		RealMatrix mElement;
		mElement.r_size = st->r_size;
		mElement.c_size = st->c_size;
		int i = 0;
		RealMatSetOp2(out_data, 0);
		for ( i = 0; i < st->size; i++)
		{
			mElement.data = st->data[i];
			out_data = RealMatAddOp1(out_data, mElement, out_data);
		}
		out_data = RealMatDotDivOp2(out_data, st->size, out_data);
	}
	return out_data;
}

RealMatrix skv_real_buffer_sum(SKVRealBuffer *st, RealMatrix out_data)
{
	if (st == NULL || st->data == NULL)
	{
		fprintf(stderr, "705 Error: skv_real_buffer_sum Failed\n");
		return out_data;
	}
	int size = st->r_size * st->c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size != out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}
	if (st->flag)
	{
		RealMatrix mSum;
		mSum.r_size = st->r_size;
		mSum.c_size = st->c_size;
		mSum.data = st->sum;
		RealMatSetOp1(out_data, mSum);
	}
	else
	{
		RealMatrix mElement;
		mElement.r_size = st->r_size;
		mElement.c_size = st->c_size;

		int i = 0;
		RealMatSetOp2(out_data, 0);
		for (i = 0; i < st->size; i++)
		{
			mElement.data = st->data[i];
			out_data = RealMatAddOp1(out_data, mElement, out_data);
		}
	}
	return out_data;
}

RealMatrix skv_real_buffer_max(SKVRealBuffer *st, RealMatrix out_data)
{
	if (st == NULL || st->data == NULL)
	{
		fprintf(stderr, "706 Error: skv_real_buffer_max Failed\n");
		return out_data;
	}
	int size = st->r_size * st->c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size != out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}

	RealMatrix mElement;
	mElement.r_size = st->r_size;
	mElement.c_size = st->c_size;
	mElement.data = st->data[0];
	RealMatSetOp1(out_data, mElement);

	int i = 0;
	for (i = 1; i < st->size; i++)
	{
		mElement.data = st->data[i];
		out_data = RealMatDynamicMaxOp(out_data, mElement, out_data);
	}
	return out_data;
}

RealMatrix skv_real_buffer_min(SKVRealBuffer *st, RealMatrix out_data)
{
	if (st == NULL || st->data == NULL)
	{
		fprintf(stderr, "707 Error: skv_real_buffer_min Failed\n");
		return out_data;
	}
	int size = st->r_size * st->c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	}
	else if (size != out_data.r_size * out_data.c_size)
	{
		out_data.data = (spx_word16_t *)speex_realloc(out_data.data, size * sizeof(spx_word16_t));
	}

	RealMatrix mElement;
	mElement.r_size = st->r_size;
	mElement.c_size = st->c_size;
	mElement.data = st->data[0];
	RealMatSetOp1(out_data, mElement);

	int i = 0;
	for (i = 1; i < st->size; i++)
	{
		mElement.data = st->data[i];
		out_data = RealMatDynamicMinOp(out_data, mElement, out_data);
	}
	return out_data;
}

struct SKVComplexBuffer_
{
	int flag;
	int size;
	int r_size;
	int c_size;
	int write_ptr;
	Complex ** data;
	Complex * sum;
};

SKVComplexBuffer *skv_complex_buffer_init(int size, int matrix_r_size, int matrix_c_size, int flag)
{
	if (size < 1 || matrix_r_size < 1 || matrix_c_size < 1)
	{
		fprintf(stderr, "701 Error:skv_complex_buffer_init Failed\n");
		return NULL;
	}
	SKVComplexBuffer *st = (SKVComplexBuffer *)speex_alloc(sizeof(SKVComplexBuffer));

	int i = 0;
	st->data = (Complex **)speex_alloc(size * sizeof(Complex *));
	for (i = 0; i < size; i++)
	{
		st->data[i] = (Complex *)speex_alloc(matrix_r_size * matrix_c_size * sizeof(Complex));
	}
	st->sum = (Complex *)speex_alloc(matrix_r_size * matrix_c_size * sizeof(Complex));

	st->flag = flag;
	st->size = size;
	st->r_size = matrix_r_size;
	st->c_size = matrix_c_size;
	st->write_ptr = 0;
	skv_complex_buffer_clear(st);
	return st;
}

void skv_complex_buffer_destroy(SKVComplexBuffer *st)
{
	if (st == NULL)
	{
		return;
	}
	int i = 0;
	for (i = 0; i < st->size; i++)
	{
		speex_free(st->data[i]); st->data[i] = NULL;
	}
	speex_free(st->data); st->data = NULL;
	speex_free(st->sum); st->sum = NULL;
	speex_free(st); st = NULL;
}

void skv_complex_buffer_clear(SKVComplexBuffer *st)
{
	if (st == NULL)
	{
		return;
	}
	int i = 0;
	for (i = 0; i < st->size; i++)
	{
		SPEEX_MEMSET(st->data[i], 0, st->r_size * st->c_size);
	}
	SPEEX_MEMSET(st->sum, 0, st->r_size * st->c_size);
}

bool skv_complex_buffer_write(SKVComplexBuffer *st, ComplexMatrix data)
{
	if (st == NULL || IsEmpltyOfComplexMatrix(data) || data.r_size != st->r_size || data.c_size != st->c_size)
	{
		fprintf(stderr, "702 Error: skv_complex_buffer_write Failed\n");
		return false;
	}
	ComplexMatrix mSum, mElement;
	mSum.r_size = st->r_size;
	mSum.c_size = st->c_size;
	mSum.data = st->sum;
	mElement.r_size = st->r_size;
	mElement.c_size = st->c_size;
	if (st->flag)
	{
		mSum = ComplexMatAddOp1(mSum, data, mSum);
		mElement.data = st->data[st->write_ptr];
		mSum = ComplexMatMinusOp1(mSum, mElement, mSum);
	}
	mElement.data = st->data[st->write_ptr];
	ComplexMatSetOp1(mElement, data);
	st->write_ptr = (st->write_ptr + 1) % st->size;
	return true;
}

ComplexMatrix skv_complex_buffer_read(SKVComplexBuffer *st, ComplexMatrix out_data, int iTh)
{
	if (st == NULL || st->data == NULL || iTh < 0 || iTh >= st->size)
	{
		fprintf(stderr, "703 Error: skv_complex_buffer_read Failed\n");
		return out_data;
	}
	int size = st->r_size * st->c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size != out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}

	ComplexMatrix mElement;
	mElement.r_size = st->r_size;
	mElement.c_size = st->c_size;
	int write_ptr = st->write_ptr;
	write_ptr = (write_ptr + iTh) % st->size;
	mElement.data = st->data[write_ptr];
	ComplexMatSetOp1(out_data, mElement);
	return out_data;
}

Complex* skv_complex_buffer_scan(SKVComplexBuffer *st, int iTh)
{
	if (st == NULL || iTh < 0 || iTh >= st->size)
	{
		fprintf(stderr, "703 Error: skv_complex_buffer_read Failed\n");
		return NULL;
	}

	int write_ptr = st->write_ptr;
	write_ptr = (write_ptr + iTh) % st->size;
	return st->data[write_ptr];
}

ComplexMatrix skv_complex_buffer_mean(SKVComplexBuffer *st, ComplexMatrix out_data)
{
	if (st == NULL || st->data == NULL)
	{
		fprintf(stderr, "704 Error: skv_complex_buffer_mean Failed\n");
		return out_data;
	}
	int size = st->r_size * st->c_size;
	Complex tmp;
	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size != out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	if (st->flag)
	{
		ComplexMatrix mSum;
		mSum.r_size = st->r_size;
		mSum.c_size = st->c_size;
		mSum.data = st->sum;
		ComplexMatSetOp1(out_data, mSum);
		tmp.real = (spx_word16_t)st->size;
		tmp.image = 0.0f;
		out_data = ComplexMatDotDivOp2(out_data, tmp, out_data);
	}
	else
	{
		ComplexMatrix mElement;
		mElement.r_size = st->r_size;
		mElement.c_size = st->c_size;
		int i = 0;
		Complex zero = { 0.0f, 0.0f };
		ComplexMatSetOp3(out_data, zero);
		for (i = 0; i < st->size; i++)
		{
			mElement.data = st->data[i];
			out_data = ComplexMatAddOp1(out_data, mElement, out_data);
		}
		tmp.real = (spx_word16_t)st->size;
		tmp.image = 0.0f;
		out_data = ComplexMatDotDivOp2(out_data, tmp, out_data);
	}
	return out_data;
}

ComplexMatrix skv_complex_buffer_sum(SKVComplexBuffer *st, ComplexMatrix out_data)
{
	if (st == NULL || st->data == NULL)
	{
		fprintf(stderr, "705 Error: skv_complex_buffer_sum Failed\n");
		return out_data;
	}
	int size = st->r_size * st->c_size;

	if (out_data.data == NULL)
	{
		out_data.data = (Complex *)speex_alloc(size * sizeof(Complex));
	}
	else if (size != out_data.r_size * out_data.c_size)
	{
		out_data.data = (Complex *)speex_realloc(out_data.data, size * sizeof(Complex));
	}
	if (st->flag)
	{
		ComplexMatrix mSum;
		mSum.r_size = st->r_size;
		mSum.c_size = st->c_size;
		mSum.data = st->sum;
		ComplexMatSetOp1(out_data, mSum);
	}
	else
	{
		ComplexMatrix mElement;
		mElement.r_size = st->r_size;
		mElement.c_size = st->c_size;

		int i = 0;
		Complex zero = { 0.0f, 0.0f };
		ComplexMatSetOp3(out_data, zero);
		for (i = 0; i < st->size; i++)
		{
			mElement.data = st->data[i];
			out_data = ComplexMatAddOp1(out_data, mElement, out_data);
		}
	}
	return out_data;
}

CircleBuffer1D * NewCircleBuffer1D(int size)
{
	if (size < 0)
	{
		return NULL;
	}
	CircleBuffer1D * st = (CircleBuffer1D *)speex_alloc(sizeof(CircleBuffer1D));
	st->size = size;
	st->write_ptr = 0;
	st->data = (char *)speex_alloc(size * sizeof(char));

	int i = 0;
	for ( i = 0; i < size; i++)
	{
		st->data[i] = '\0';
	}
	return st;
}
CircleBuffer2D * NewCircleBuffer2D(int r_size, int c_size)
{
	if (r_size < 0 || c_size < 0 )
	{
		return NULL;
	}
	CircleBuffer2D * st = (CircleBuffer2D *)speex_alloc(sizeof(CircleBuffer2D));
	st->r_size = r_size;
	st->c_size = c_size;
	st->write_ptr = 0;

	st->data = (char **)speex_alloc(r_size * sizeof(char *));
	int ch = 0;
	int i = 0;
	for (ch = 0; ch < r_size; ch++)
	{
		st->data[ch] = (char *)speex_alloc(c_size * sizeof(char));
		for ( i = 0; i < c_size; i++)
		{
			st->data[ch][i] = '\0';
		}
	}
	return st;
}

void FreeCircleBuffer1D(CircleBuffer1D * st)
{
	if (st == NULL)
	{
		return;
	}
	if (st->data == NULL)
	{
		return;
	}

	speex_free(st->data); st->data = NULL;
	speex_free(st); st = NULL;
}
void FreeCircleBuffer2D(CircleBuffer2D * st)
{
	if (st == NULL)
	{
		return;
	}
	if (st->data == NULL)
	{
		return;
	}
	int r = 0;
	for ( r = 0; r < st->r_size; r++)
	{
		speex_free(st->data[r]); st->data[r] = NULL;
	}
	speex_free(st->data); st->data = NULL;
	speex_free(st); st = NULL;
}

void PushCircleBuffer1D(CircleBuffer1D * st, void * data, int size)
{
	if (st == NULL || data == NULL || size < 1)
	{
		return;
	}
	int i = 0;
	for ( i = 0; i < size; i++)
	{
		st->data[st->write_ptr] = ((char *)data)[i];
		st->write_ptr = (st->write_ptr + 1) % st->size;
	}
}
static int circle_buffer_write(CircleBuffer2D *st, char *_data, int r, int size)
{
	if (st == NULL || r >= st->r_size || r < 0 || _data == NULL || size < 1)
	{
		return 0;
	}
	int write_ptr = st->write_ptr;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		st->data[r][write_ptr] = _data[i];
		write_ptr = (write_ptr + 1) % st->c_size;
	}
	return 1;
}
static int circle_buffer_writezeros(CircleBuffer2D *st, int r, int size)
{
	if (st == NULL || r >= st->r_size || r < 0 || size < 1)
	{
		return 0;
	}
	int write_ptr = st->write_ptr;
	int i = 0;
	for (i = 0; i < size; i++)
	{
		st->data[r][write_ptr] = '\0';
		write_ptr = (write_ptr + 1) % st->c_size;
	}
	return 1;
}
void PushCircleBuffer2D(CircleBuffer2D * st, void ** data, int r_size, int c_size)
{
	if (st == NULL || r_size < 1 || c_size < 1 || data == NULL)
	{
		return;
	}
	int r = 0;
	for (r = 0; r < st->r_size; r++)
	{
		if (r < r_size)
		{
			circle_buffer_write(st, (char *)data[r], r, c_size);
		}
		else
		{
			circle_buffer_writezeros(st, r, c_size);
		}
	}
	int i = 0;
	for (i = 0; i < c_size; i++)
	{
		st->write_ptr = (st->write_ptr + 1) % st->c_size;
	}
}


spx_word16_t * NewFloatVec1D(int size)
{
	if (size < 1)
	{
		return NULL;
	}
	spx_word16_t * st = (spx_word16_t *)speex_alloc(size * sizeof(spx_word16_t));
	SetVecZeros1(st, 0, size);
	return st;
}
spx_word16_t ** NewFloatVec2D(int r_size, int c_size)
{
	if (r_size < 1 || c_size < 1)
	{
		return NULL;
	}
	spx_word16_t ** st = (spx_word16_t * *)speex_alloc(r_size * sizeof(spx_word16_t *));
	int r = 0;
	for ( r = 0; r < r_size; r++)
	{
		st[r] = NewFloatVec1D(c_size);
	}
	return st;
}
spx_word16_t * FreeFloatVec1D(spx_word16_t * st)
{
	if (st == NULL)
	{
		return NULL;
	}
	speex_free(st); 
	return NULL;
}
spx_word16_t ** FreeFloatVec2D(spx_word16_t ** st, int r_size)
{
	if (st == NULL)
	{
		return NULL;
	}
	int r = 0;
	for ( r = 0; r < r_size; r++)
	{
		speex_free(st[r]); st[r] = NULL;
	}
	speex_free(st); 
	return NULL;
}

void SetVecZeros1(spx_word16_t * data, int offset, int count)
{
	if (data == NULL)
	{
		return;
	}
	int i = 0;
	for (i = offset; i < offset + count; i++)
	{
		data[i] = 0;
	}
}
void SetVecZeros2(int * data, int offset, int count)
{
	if (data == NULL)
	{
		return;
	}
	int i = 0;
	for (i = offset; i < offset + count; i++)
	{
		data[i] = 0;
	}
}
void SetVecOnes(spx_word16_t * data, int offset, int count)
{
	if (data == NULL)
	{
		return;
	}
	int i = 0;
	for (i = offset; i < offset + count; i++)
	{
		data[i] = 0;
	}
}
void SetVecValue(spx_word16_t * data, spx_word16_t value, int offset, int count)
{
	if (data == NULL)
	{
		return;
	}
	int i = 0;
	for (i = offset; i < offset + count; i++)
	{
		data[i] = value;
	}
}

void VecPowOp1(spx_word16_t * in_data, spx_word16_t * out_data, int size, float value)
{
	if (in_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for ( i = 0; i < size; i++)
	{
		out_data[i] = pow(in_data[i], value);
	}
}
void VecPowOp2(spx_word16_t * in_data, spx_word16_t * out_data, int size)
{
	if (in_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = in_data[i] * in_data[i];
	}
}

void VecMultiOp1(spx_word16_t * x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || y_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = x_data[i] * y_data[i];
	}
}
void VecMultiOp2(spx_word16_t * in_data, float value, spx_word16_t * out_data, int size)
{
	if (in_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = in_data[i] * value;
	}
}
void VecMultiOp3(float x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size)
{
	if (y_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = x_data * y_data[i];
	}
}

void VecDivOp1(spx_word16_t * x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || y_data == NULL || out_data == NULL)
	{
		return;
	}
	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (y_data[i] == 0)
		{
			if (x_data[i] == 0)
			{
				out_data[i] = 0;
			}
			else
			{
				out_data[i] = x_data[i] > 0 ? FLT_MAX : FLT_MIN;
			}
		}
		else
		{
			out_data[i] = x_data[i] / y_data[i];
		}
	}
}
void VecDivOp2(spx_word16_t * x_data, float y_data, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || out_data == NULL)
	{
		return;
	}
	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (y_data == 0)
		{
			if (x_data[i] == 0)
			{
				out_data[i] = 0;
			}
			else
			{
				out_data[i] = x_data[i] > 0 ? FLT_MAX : FLT_MIN;
			}
		}
		else
		{
			out_data[i] = x_data[i] / y_data;
		}
	}
}
void VecDivOp3(float x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size)
{
	if ( y_data == NULL || out_data == NULL)
	{
		return;
	}
	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (y_data[i] == 0)
		{
			if (x_data == 0)
			{
				out_data[i] = 0;
			}
			else
			{
				out_data[i] = x_data > 0 ? FLT_MAX : FLT_MIN;
			}
		}
		else
		{
			out_data[i] = x_data / y_data[i];
		}

	}
}

void VecAddOp1(spx_word16_t * x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || y_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = x_data[i] + y_data[i];
	}
}
void VecAddOp2(spx_word16_t * x_data, float y_data, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = x_data[i] + y_data;
	}
}
void VecAddOp3(float x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size)
{
	if (y_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = x_data + y_data[i];
	}
}

void VecMinusOp1(spx_word16_t * x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || y_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = x_data[i] - y_data[i];
	}
}
void VecMinusOp2(spx_word16_t * x_data, float y_data, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = x_data[i] - y_data;
	}
}
void VecMinusOp3(float x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size)
{
	if (y_data == NULL || out_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		out_data[i] = x_data - y_data[i];
	}
}

void VecSetOp1(spx_word16_t * x_data, spx_word16_t * y_data, int size)
{
	if (x_data == NULL || y_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		x_data[i] = y_data[i];
	}
}
void VecSetOp2(spx_word16_t * x_data, float y_data, int size)
{
	if (x_data == NULL)
	{
		return;
	}

	int i = 0;
	for (i = 0; i < size; i++)
	{
		x_data[i] = y_data;
	}
}

void VecBandOp(spx_word16_t * x_data, float low_band, float up_band, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || out_data == NULL)
	{
		return;
	}
	int i;
	for ( i = 0; i < size; i++)
	{
		if (x_data[i] < low_band)
		{
			out_data[i] = low_band;
		}
		else if (x_data[i] > up_band)
		{
			out_data[i] = up_band;
		}
		else
		{
			out_data[i] = x_data[i];
		}
	}
}
void VecLowBandOp(spx_word16_t * x_data, float low_band, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || out_data == NULL)
	{
		return;
	}
	int i;
	for (i = 0; i < size; i++)
	{
		if (x_data[i] < low_band)
		{
			out_data[i] = low_band;
		}
		else
		{
			out_data[i] = x_data[i];
		}
	}
}
void VecUpBandOp(spx_word16_t * x_data, float up_band, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || out_data == NULL)
	{
		return;
	}
	int i;
	for (i = 0; i < size; i++)
	{
		if (x_data[i] > up_band)
		{
			out_data[i] = up_band;
		}
		else
		{
			out_data[i] = x_data[i];
		}
	}
}

void VecExpOp(spx_word16_t * x_data, spx_word16_t * out_data, int size)
{
	if (x_data == NULL || out_data == NULL)
	{
		return;
	}
	int i;
	for ( i = 0; i < size; i++)
	{
		out_data[i] = SKV_EXP(x_data[i]);
	}
}

float VecMeanOp(spx_word16_t * x_data, int s_idx, int e_idx)
{
	if (x_data == NULL || (e_idx - s_idx) <= 0)
	{
		return 0.0f;
	}


	float meanf = 0.0f;
	int i;
	for ( i = s_idx; i <= e_idx; i++)
	{
		meanf = meanf + x_data[i];
	}
	return (meanf / (e_idx - s_idx + 1));
}

float VecSumOp1(spx_word16_t * x_data, int s_idx, int e_idx)
{
	if (x_data == NULL || (e_idx - s_idx) <= 0)
	{
		return 0.0f;
	}


	float sumf = 0.0f;
	int i;
	for (i = s_idx; i <= e_idx; i++)
	{
		sumf = sumf + x_data[i];
	}
	return sumf;
}
float VecSumOp2(int * x_data, int s_idx, int e_idx)
{
	if (x_data == NULL || (e_idx - s_idx) <= 0)
	{
		return 0.0f;
	}


	int sumf = 0.0f;
	int i;
	for (i = s_idx; i <= e_idx; i++)
	{
		sumf = sumf + x_data[i];
	}
	return sumf;
}

void VecDynamicMeanOp(spx_word16_t * x_data, spx_word16_t * y_data, int size, int frame)
{
	if (x_data == NULL || y_data == NULL)
	{
		return;
	}
	int i;
	for ( i = 0; i < size; i++)
	{
		x_data[i] = x_data[i] * frame + y_data[i];
		x_data[i] = x_data[i] / (frame + 1);
	}
}
void VecDynamicMaxOp(spx_word16_t * x_data, spx_word16_t * y_data, int size)
{
	if (x_data == NULL || y_data == NULL)
	{
		return;
	}
	int i;
	for (i = 0; i < size; i++)
	{
		x_data[i] = SKV_MAX(x_data[i], y_data[i]);
	}
}
void VecDynamicMinOp(spx_word16_t * x_data, spx_word16_t * y_data, int size)
{
	if (x_data == NULL || y_data == NULL)
	{
		return;
	}
	int i;
	for (i = 0; i < size; i++)
	{
		x_data[i] = SKV_MIN(x_data[i], y_data[i]);
	}
}

CircleBuff1D init_buffer(int size)
{
	CircleBuff1D buffer;
	buffer.isFull = false;
	buffer.sum = 0;
	buffer.write_ptr = 0;
	buffer.len = size;
	buffer.data = (spx_word16_t*)speex_alloc(size * sizeof(spx_word16_t));
	int i = 0;
	for (i = 0; i < size; i++)
	{
		buffer.data[i] = 0.0f;
	}
	return buffer;
}
CircleBuff1D destroy_buffer(CircleBuff1D * buffer)
{
	buffer->isFull = false;
	buffer->sum = 0;
	buffer->write_ptr = 0;
	buffer->len = 0;
	speex_free(buffer->data); buffer->data = NULL;
	return (*buffer);
}
void clear_buffer(CircleBuff1D * buffer)
{
	buffer->isFull = false;
	buffer->sum = 0;
	buffer->write_ptr = 0;
	int i = 0;
	for (i = 0; i < buffer->len; i++)
	{
		buffer->data[i] = 0.0f;
	}
}
void push_buffer(CircleBuff1D * buffer, spx_word16_t data)
{
	buffer->sum = buffer->sum + data - buffer->data[buffer->write_ptr];
	if (buffer->write_ptr + 1 >= buffer->len)
	{
		buffer->isFull = true;
	}
	buffer->data[buffer->write_ptr] = data;
	buffer->write_ptr = (buffer->write_ptr + 1) % buffer->len;
	/*if (buffer->isFull == false)
	{
	int i = 0;
	spx_word16_t tmp;
	for ( i = buffer->write_ptr; i > 0; i--)
	{
	if (buffer->data[i] < buffer->data[i -1])
	{
	tmp = buffer->data[i - 1];
	buffer->data[i - 1] = buffer->data[i];
	buffer->data[i] = tmp;
	}
	}
	}*/
}
float mean_buffer(CircleBuff1D * buffer)
{
	float mean = 0.0f;
	int i = 0;
	if (buffer->isFull)
	{
		mean = buffer->sum / (float)(buffer->len);
	}
	else
	{
		if (buffer->write_ptr > 0)
		{
			mean = buffer->sum / (float)(buffer->write_ptr);
		}
	}
	return mean;
}
float sum_buffer(CircleBuff1D * buffer)
{
	return buffer->sum;
}
float median_buffer(CircleBuff1D * buffer)
{
	int i = 0, j = 0;
	float tmp;
	if (buffer->isFull)
	{
		spx_word16_t * tmp_buff = (spx_word16_t *)speex_alloc(buffer->len * sizeof(spx_word16_t));
		for (i = 0; i < buffer->len; i++)
		{
			tmp_buff[i] = buffer->data[i];
		}
		for (i = 0; i < buffer->len / 2 + 1; i++)
		{
			for (j = 0; j < buffer->len - i - 1; j++)
			{
				if (tmp_buff[j] > tmp_buff[j + 1])
				{
					tmp = tmp_buff[j + 1];
					tmp_buff[j + 1] = tmp_buff[j];
					tmp_buff[j] = tmp;
				}
			}
		}
		if (buffer->len % 2 != 0)
		{
			tmp = tmp_buff[buffer->len / 2];
			speex_free(tmp_buff); tmp_buff = NULL;
			return tmp;
		}
		else
		{
			tmp = (tmp_buff[buffer->len / 2] + tmp_buff[(buffer->len / 2) - 1]) / 2.0f;
			speex_free(tmp_buff); tmp_buff = NULL;
			return tmp;
		}
	}
	else
	{
		spx_word16_t * tmp_buff = (spx_word16_t *)speex_alloc(buffer->write_ptr * sizeof(spx_word16_t));
		for (i = 0; i < buffer->write_ptr; i++)
		{
			tmp_buff[i] = buffer->data[i];
		}
		for (i = 0; i < buffer->write_ptr / 2 + 1; i++)
		{
			for (j = 0; j < buffer->write_ptr - i - 1; j++)
			{
				if (tmp_buff[j] > tmp_buff[j + 1])
				{
					tmp = tmp_buff[j + 1];
					tmp_buff[j + 1] = tmp_buff[j];
					tmp_buff[j] = tmp;
				}
			}
		}
		if (buffer->write_ptr % 2 != 0)
		{
			tmp = tmp_buff[buffer->write_ptr / 2];
			speex_free(tmp_buff); tmp_buff = NULL;
			return tmp;
		}
		else
		{
			tmp = (tmp_buff[buffer->write_ptr / 2] + tmp_buff[(buffer->write_ptr / 2) - 1]) / 2.0f;
			speex_free(tmp_buff); tmp_buff = NULL;
			return tmp;
		}
	}
}

SmoothWin init_smoothwin(int size)
{
	SmoothWin aSmoothWin;

	aSmoothWin.write_ptr = 0;
	aSmoothWin.len = size;
	aSmoothWin.max = 0;
	aSmoothWin.min = 0;
	aSmoothWin.sum = 0;
	aSmoothWin.data = (spx_word16_t*)speex_alloc(size * sizeof(spx_word16_t));
	int i = 0;
	for (i = 0; i < size; i++)
	{
		aSmoothWin.data[i] = 0.0f;
	}
	return aSmoothWin;
}
SmoothWin destroy_smoothwin(SmoothWin * aSmoothWin)
{
	aSmoothWin->write_ptr = 0;
	aSmoothWin->len = 0;
	aSmoothWin->max = 0;
	aSmoothWin->min = 0;
	aSmoothWin->sum = 0;
	speex_free(aSmoothWin->data); aSmoothWin->data = NULL;
	return (*aSmoothWin);
}
void clear_smoothwin(SmoothWin * aSmoothWin)
{
	aSmoothWin->write_ptr = 0;
	aSmoothWin->max = 0;
	aSmoothWin->min = 0;
	aSmoothWin->sum = 0;
	int i = 0;
	for (i = 0; i < aSmoothWin->len; i++)
	{
		aSmoothWin->data[i] = 0.0f;
	}
}
void push_smoothwin(SmoothWin * win, spx_word16_t data)
{
	int write_ptr = win->write_ptr;
	spx_word16_t pre_v = win->data[win->write_ptr];
	spx_word16_t max = win->max;
	spx_word16_t min = win->min;
	int i = 0, j = 0;

	if (pre_v == max)
	{
		write_ptr = (win->write_ptr + 1) % win->len;
		max = win->data[write_ptr];
		for (j = 2; j < win->len; j++)
		{
			write_ptr = (win->write_ptr + j) % win->len;
			if (max < win->data[write_ptr])
			{
				max = win->data[write_ptr];
			}
		}
	}
	if (pre_v == min)
	{
		write_ptr = (win->write_ptr + 1) % win->len;
		min = win->data[write_ptr];
		for (j = 2; j < win->len; j++)
		{
			write_ptr = (win->write_ptr + j) % win->len;
			if (min > win->data[write_ptr])
			{
				min = win->data[write_ptr];
			}
		}
	}
	if (max < data)
	{
		max = data;
	}
	if (min > data)
	{
		min = data;
	}
	win->max = max;
	win->min = min;
	win->sum = win->sum + data - win->data[win->write_ptr];
	win->data[win->write_ptr] = data;
	win->write_ptr = (win->write_ptr + 1) % win->len;
}
spx_word16_t max_smoothwin(SmoothWin * win)
{
	return win->max;
}
spx_word16_t min_smoothwin(SmoothWin * win)
{
	return win->min;
}
spx_word16_t sum_smoothwin(SmoothWin * win)
{
	return win->sum;
}
spx_word16_t mean_smoothwin(SmoothWin * win)
{
	return win->sum / (float)(win->len);
}

CircleBuff2DFloat init_Float2Dbuffer(int r_size, int c_size)
{
	CircleBuff2DFloat buffer;
	buffer.write_ptr = 0;
	buffer.r_write_ptr = 0;
	buffer.r_size = r_size;
	buffer.c_size = c_size;
	buffer.len = r_size * c_size;
	buffer.sum = (spx_word16_t*)speex_alloc(buffer.c_size * sizeof(spx_word16_t));
	buffer.avg = (spx_word16_t*)speex_alloc(buffer.c_size * sizeof(spx_word16_t));
	buffer.data = (spx_word16_t*)speex_alloc(buffer.len * sizeof(spx_word16_t));
	int i = 0;
	for (i = 0; i < buffer.c_size; i++)
	{
		buffer.sum[i] = 0.0f;
		buffer.avg[i] = 0.0f;
	}
	for (i = 0; i < buffer.len; i++)
	{
		buffer.data[i] = 0.0f;
	}
	return buffer;
}
CircleBuff2DFloat destroy_Float2Dbuffer(CircleBuff2DFloat* buffer)
{
	buffer->write_ptr = 0;
	buffer->r_write_ptr = 0;
	buffer->len = 0;
	buffer->r_size = 0;
	buffer->c_size = 0;
	speex_free(buffer->sum);
	buffer->sum = NULL;
	speex_free(buffer->avg);
	buffer->avg = NULL;
	speex_free(buffer->data);
	buffer->data = NULL;
	return (*buffer);
}
void clear_Float2Dbuffer(CircleBuff2DFloat* buffer)
{
	buffer->write_ptr = 0;
	buffer->r_write_ptr = 0;
	int i = 0;
	for (i = 0; i < buffer->c_size; i++)
	{
		buffer->sum[i] = 0.0f;
		buffer->avg[i] = 0.0f;
	}
	for (i = 0; i < buffer->len; i++)
	{
		buffer->data[i] = 0.0f;
	}
}
void push_Float2Dbuffer(CircleBuff2DFloat* buffer, spx_word16_t* data)
{
	if (buffer->r_write_ptr < buffer->r_size)
	{
		buffer->r_write_ptr = buffer->r_write_ptr + 1;
	}
	int i = 0;
	for (i = 0; i < buffer->c_size; i++)
	{
		buffer->sum[i] = buffer->sum[i] + data[i] - buffer->data[buffer->write_ptr];
		buffer->data[buffer->write_ptr] = data[i];
		buffer->write_ptr = (buffer->write_ptr + 1) % buffer->len;
	}
}
spx_word16_t* mean_Float2Dbuffer(CircleBuff2DFloat * buffer)
{
	int i = 0;
	for (i = 0; i < buffer->c_size; i++)
	{
		buffer->avg[i] = buffer->sum[i] / (float)(buffer->r_write_ptr);
	}
	return buffer->avg;
}


CountBuffer* init_countbuffer(int size)
{
	CountBuffer* buffer = (CountBuffer*)speex_alloc(sizeof(CountBuffer));
	buffer->sum = 0;
	buffer->write_ptr = 0;
	buffer->size = size;
	buffer->data = (skv_int32_t*)speex_alloc(size * sizeof(skv_int32_t));
	SPEEX_MEMSET(buffer->data, 0, buffer->size);
	return buffer;
}
CountBuffer* destroy_countbuffer(CountBuffer * buffer)
{
	buffer->sum = 0;
	buffer->write_ptr = 0;
	buffer->size = 0;
	speex_free(buffer->data); buffer->data = NULL;
	speex_free(buffer); buffer = NULL;
	return buffer;
}
void clear_countbuffer(CountBuffer * buffer)
{
	buffer->sum = 0;
	buffer->write_ptr = 0;
	SPEEX_MEMSET(buffer->data, 0, buffer->size);
}
void push_countbuffer(CountBuffer * buffer, skv_word16_t data)
{
	buffer->sum = buffer->sum + data - buffer->data[buffer->write_ptr];
	buffer->data[buffer->write_ptr] = data;
	buffer->write_ptr = (buffer->write_ptr + 1) % buffer->size;
}
skv_int32_t sum_countbuffer(CountBuffer * buffer)
{
	return buffer->sum;
}

PulseBuffer* skv_pulsebuffer_init(int size, int stable_buffer_size, int stable_disicion_size)
{
	if (size < 1 || stable_buffer_size < 1)
	{
		fprintf(stderr, "Error: skv_pulsebuffer_int Failed\n");
		return NULL;
	}

	PulseBuffer* st = (PulseBuffer*)speex_alloc(sizeof(PulseBuffer));

	int i = 0;
	st->write_ptr = 0;
	st->size = size;
	st->data = (spx_word16_t*)speex_alloc(size * sizeof(spx_word16_t));
	SPEEX_MEMSET(st->data, 0.0f, size);

	st->stable_buffer_size = stable_buffer_size;
	st->stable_buffer = init_countbuffer(stable_buffer_size);
	st->stable_dicision_size = stable_disicion_size;
	st->stable_value = 0.0f;

	return st;
}

PulseBuffer* skv_pulsebuffer_destroy(PulseBuffer * st)
{
	if (st == NULL)
	{
		return NULL;
	}
	st->stable_buffer = destroy_countbuffer(st->stable_buffer);
	st->stable_buffer_size = 0;
	st->stable_dicision_size = 0;
	st->stable_value = -1.0f;

	speex_free(st->data); st->data = NULL;
	st->write_ptr = 0;
	st->size = 0;
	speex_free(st); st = NULL;

	return st;
}

void skv_pulsebuffer_clear(PulseBuffer * st)
{
	clear_countbuffer(st->stable_buffer);

	st->stable_dicision_size = 0;
	st->stable_buffer_size = 0;
	st->stable_value = -1.0f;

	st->write_ptr = 0;
	SPEEX_MEMSET(st->data, 0.0f, st->size);
}

spx_word16_t skv_pulsebuffer_read(PulseBuffer * st, int iTh)
{
	int write_ptr = st->write_ptr;
	write_ptr = (write_ptr + iTh) % st->size;
	return st->data[write_ptr];
}

void skv_pulsebuffer_write(PulseBuffer * st, spx_word16_t data, int STABLE_DECISION_THRESH)
{
	if (st == NULL)
	{
		return;
	}

	int i = 0, j = 0;
	int stable = 1;
	for (i = 0; i < st->stable_dicision_size; i++)
	{
		if (SKV_ABS(data - skv_pulsebuffer_read(st, st->size - i - 1)) > STABLE_DECISION_THRESH)
		{
			stable = 0;
			break;
		}
	}

	if (stable == 1)
	{
		st->stable_value = data;
	}
	else
	{
		st->stable_value = 0.0f;
	}

	push_countbuffer(st->stable_buffer, stable);

	st->data[st->write_ptr] = data;
	st->write_ptr = (st->write_ptr + 1) % st->size;
}


float skv_pulsebuffer_stable(PulseBuffer * st)
{
	if (st == NULL)
	{
		return 0;
	}

	int stable_count = sum_countbuffer(st->stable_buffer);
	if (stable_count >= st->stable_buffer_size)
	{
		st->stable_value = skv_pulsebuffer_read(st, st->size - st->stable_buffer_size / 2 - 1);
		return st->stable_value;
	}
	else
	{
		return -1.0f;
	}
}

int skv_pulsebuffer_jump(PulseBuffer * st, int jump_len, float jump_thresh)
{
	int i = 0;
	int jump = 0;
	for (i = 0; i < jump_len; i++)
	{
		if ((st->stable_value - skv_pulsebuffer_read(st, st->size - 1 - (st->stable_buffer_size + i))) > jump_thresh)
		{
			jump = 1;
			break;
		}
	}
	return jump;
}