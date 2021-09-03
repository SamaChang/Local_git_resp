
#ifndef _SKV_MATH_H
#define _SKV_MATH_H

#ifdef __cplusplus 
extern "C"
{
#endif  

#include "../basic/skv_config.h"
#include "../basic/skv_types.h"
#include "skv_math_core.h"
#include "skv_fastmath.h"

#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

	Complex RandComplex();
	Complex Add1(Complex a, Complex b);
	Complex Add2(spx_word16_t a, Complex b);
	Complex Add3(Complex a, spx_word16_t b);

	Complex Minus1(Complex a, Complex b);
	Complex Minus2(spx_word16_t a, Complex b);
	Complex Minus3(Complex a, spx_word16_t b);

	Complex Multi1(Complex a, Complex b);
	Complex Multi2(spx_word16_t a, Complex b);
	Complex Multi3(Complex a, spx_word16_t b);

	Complex Div1(Complex a, Complex b);
	Complex Div2(spx_word16_t a, Complex b);
	Complex Div3(Complex a, spx_word16_t b);

	Complex Neg(Complex a);

	Complex Conj(Complex a);

	spx_word16_t SKV_ABSC(Complex a);
	spx_word16_t SKV_POWC(Complex a);
	spx_word16_t SKV_ABSR(spx_word16_t a);
	Complex SKV_SQRTC(spx_word16_t a);
	Complex SKV_EXPC(Complex a);

	ComplexMatrix RandComplexMatrix(spx_uint32_t r_size, spx_uint32_t c_size);
	ComplexMatrix NewComplexMatrix(spx_uint32_t r_size, spx_uint32_t c_size);
	ComplexMatrix FreeComplexMatrix(ComplexMatrix st);
	void ComplexMatSetOp1(ComplexMatrix x_data, ComplexMatrix y_data);
	void ComplexMatSetOp2(ComplexMatrix x_data, RealMatrix y_data);
	void ComplexMatSetOp3(ComplexMatrix x_data, Complex y_data);
	void ComplexMatSetOp4(ComplexMatrix x_data, Complex y_data, int s_r, int s_c, int e_r, int e_c);
	void ComplexMatSetOp5(ComplexMatrix x_data, ComplexMatrix y_data, int s_r, int s_c, int e_r, int e_c);
	void ComplexMatSetOp6(ComplexMatrix x_data, RealMatrix y_data, int s_r, int s_c, int e_r, int e_c);

	bool IsEmpltyOfComplexMatrix(ComplexMatrix x_data);

	Complex ComplexMatrixGetAt(ComplexMatrix x_data, spx_uint32_t i, spx_uint32_t j);
	void ComplexMatrixSetAt(ComplexMatrix x_data, spx_uint32_t i, spx_uint32_t j, Complex y_data);

	void printComplexMatrix(ComplexMatrix x_data, const char * var_name);
	void fprintComplexMatrix(FILE * fp, ComplexMatrix x_data, const char * var_name);
	void fprintComplexMatrix1(ComplexMatrix x_data, int s_r, int s_c, int e_r, int e_c, const char * var_name, const char * filename);

	ComplexMatrix ComplexMatAddOp1(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatAddOp2(ComplexMatrix x_data, Complex y_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatAddOp3(Complex x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexMatMinusOp1(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatMinusOp2(ComplexMatrix x_data, Complex y_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatMinusOp3(Complex x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexMatDotMultiOp1(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatDotMultiOp2(ComplexMatrix x_data, Complex y_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatDotMultiOp3(Complex x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexMatDotDivOp1(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatDotDivOp2(ComplexMatrix x_data, Complex y_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatDotDivOp3(Complex x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexMatMultiOp(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexMatConjOp(ComplexMatrix x_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatTransOp(ComplexMatrix x_data, ComplexMatrix out_data);
	ComplexMatrix ComplexMatConjTransOp(ComplexMatrix x_data, ComplexMatrix out_data);
	
	ComplexMatrix ComplexMatDiagOp(ComplexMatrix x_data, ComplexMatrix out_data);
	Complex ComplexMatTraceOp(ComplexMatrix x_data);

	ComplexMatrix ComplexMatMeanOp(ComplexMatrix x_data, int rORc, ComplexMatrix out_data);
	Complex ComplexMatMeanMeanOp(ComplexMatrix x_data, int s_r, int s_c, int e_r, int e_c);
	ComplexMatrix ComplexMatSumOp(ComplexMatrix x_data, int rORc, ComplexMatrix out_data);
	Complex ComplexMatSumSumOp(ComplexMatrix x_data, int s_r, int s_c, int e_r, int e_c);
	
	ComplexMatrix ComplexMatDynamicMeanOp(ComplexMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data, int frame);
	
	RealMatrix ComplexMatABSOp(ComplexMatrix x_data, RealMatrix out_data);
	RealMatrix ComplexMatPOWOp(ComplexMatrix x_data, RealMatrix out_data);

	RealMatrix EyeRealMatrix(spx_uint32_t r_size, spx_uint32_t c_size);
	RealMatrix RandRealMatrix(spx_uint32_t r_size, spx_uint32_t c_size);
	RealMatrix NewRealMatrix(spx_uint32_t r_size, spx_uint32_t c_size);
	RealMatrix FreeRealMatrix(RealMatrix st);
	spx_word16_t RealMatrixGetAt(RealMatrix x_data, spx_uint32_t i, spx_uint32_t j);
	void RealMatrixSetAt(RealMatrix x_data, spx_uint32_t i, spx_uint32_t j, spx_word16_t y_data);
	void RealMatSetOp1(RealMatrix x_data, RealMatrix y_data);
	void RealMatSetOp2(RealMatrix x_data, spx_word16_t y_data);
	void RealMatSetOp3(RealMatrix x_data, spx_word16_t y_data, int s_r, int s_c, int e_r, int e_c);
	void RealMatSetOp4(RealMatrix x_data, RealMatrix y_data, int s_r, int s_c, int e_r, int e_c);
	
	bool IsEmpltyOfRealMatrix(RealMatrix x_data);

	void printRealMatrix(RealMatrix x_data, const char * var_name);
	void fprintRealMatrix(FILE * fp, RealMatrix x_data, const char * var_name);
	void fprintRealMatrix1(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c, const char * var_name, const char * filename);

	RealMatrix RealMatAddOp1(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data);
	RealMatrix RealMatAddOp2(RealMatrix x_data, spx_word16_t y_data, RealMatrix out_data);
	RealMatrix RealMatAddOp3(spx_word16_t x_data, RealMatrix y_data, RealMatrix out_data);

	RealMatrix RealMatMinusOp1(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data);
	RealMatrix RealMatMinusOp2(RealMatrix x_data, spx_word16_t y_data, RealMatrix out_data);
	RealMatrix RealMatMinusOp3(spx_word16_t x_data, RealMatrix y_data, RealMatrix out_data);

	RealMatrix RealMatDotMultiOp1(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data);
	RealMatrix RealMatDotMultiOp2(RealMatrix x_data, spx_word16_t y_data, RealMatrix out_data);
	RealMatrix RealMatDotMultiOp3(spx_word16_t x_data, RealMatrix y_data, RealMatrix out_data);

	RealMatrix RealMatDotDivOp1(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data);
	RealMatrix RealMatDotDivOp2(RealMatrix x_data, spx_word16_t y_data, RealMatrix out_data);
	RealMatrix RealMatDotDivOp3(spx_word16_t x_data, RealMatrix y_data, RealMatrix out_data);

	RealMatrix RealMatMultiOp(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data);

	RealMatrix RealMatTransOp(RealMatrix x_data, RealMatrix out_data);

	RealMatrix RealMatABSOp(RealMatrix x_data, RealMatrix out_data);

	RealMatrix RealMatDiagOp(RealMatrix x_data, RealMatrix out_data);
	spx_word16_t RealMatTraceOp(RealMatrix x_data);

	RealMatrix RealMatPowOp(RealMatrix x_data, float x, RealMatrix out_data);
	RealMatrix RealMatSqrtOp(RealMatrix x_data, RealMatrix out_data);
	RealMatrix RealMatPow2Op(RealMatrix x_data, RealMatrix out_data);
	RealMatrix RealMatExpOp(RealMatrix x_data, RealMatrix out_data);
	RealMatrix RealMatLogOp(RealMatrix x_data, RealMatrix out_data);
	RealMatrix RealMatLog2Op(RealMatrix x_data, RealMatrix out_data);
	RealMatrix RealMatLog10Op(RealMatrix x_data, RealMatrix out_data);

	/*
	x_data(x_data < low_band) = low_band, x_data(x_data > up_band) = up_band
	*/
	RealMatrix RealMatBandOp(RealMatrix x_data, spx_word16_t low_band, spx_word16_t up_band, RealMatrix out_data); 
	/*
	x_data(x_data < low_band) = low_band
	*/
	RealMatrix RealMatLowBandOp(RealMatrix x_data, spx_word16_t low_band, RealMatrix out_data);
	/*
	x_data(x_data > up_band) = up_band
	*/
	RealMatrix RealMatUpBandOp(RealMatrix x_data,  spx_word16_t up_band, RealMatrix out_data);

	RealMatrix RealMatMeanOp(RealMatrix x_data, int rORc, RealMatrix out_data);
	spx_word16_t RealMatMeanMeanOp(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c);
	RealMatrix RealMatSumOp(RealMatrix x_data, int rORc, RealMatrix out_data);
	spx_word16_t RealMatSumSumOp(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c);
	RealMatrix RealMatMaxOp(RealMatrix x_data, int rORc, RealMatrix out_data);
	spx_word16_t RealMatMaxMaxOp(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c);
	RealMatrix RealMatMinOp(RealMatrix x_data, int rORc, RealMatrix out_data);
	spx_word16_t RealMatMinMinOp(RealMatrix x_data, int s_r, int s_c, int e_r, int e_c);

	RealMatrix RealMatDynamicMeanOp(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data, int frame);
	RealMatrix RealMatDynamicMaxOp(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data);
	RealMatrix RealMatDynamicMinOp(RealMatrix x_data, RealMatrix y_data, RealMatrix out_data);

	ComplexMatrix ComplexRealMatAddOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix RealComplexMatAddOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexRealMatMinusOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix RealComplexMatMinusOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexRealMatMultiOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix RealComplexMatMultiOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexRealMatDotMultiOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix RealComplexMatDotMultiOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	ComplexMatrix ComplexRealMatDotDivOp(ComplexMatrix x_data, RealMatrix y_data, ComplexMatrix out_data);
	ComplexMatrix RealComplexMatDotDivOp(RealMatrix x_data, ComplexMatrix y_data, ComplexMatrix out_data);

	typedef struct CircleBuff1D_
	{
		bool isFull;
		int write_ptr;
		int len;
		spx_word16_t * data;
		spx_word16_t sum;
	} CircleBuff1D;
	CircleBuff1D init_buffer(int size);
	CircleBuff1D destroy_buffer(CircleBuff1D * buffer);
	void clear_buffer(CircleBuff1D * buffer);
	void push_buffer(CircleBuff1D * buffer, spx_word16_t data);
	float mean_buffer(CircleBuff1D * buffer);
	float sum_buffer(CircleBuff1D * buffer);
	float median_buffer(CircleBuff1D * buffer);

	typedef struct SmoothWin_
	{
		int write_ptr;
		int len;
		spx_word16_t max;
		spx_word16_t min;
		spx_word16_t sum;
		spx_word16_t * data;
	} SmoothWin;
	SmoothWin init_smoothwin(int size);
	SmoothWin destroy_smoothwin(SmoothWin * aSmoothWin);
	void clear_smoothwin(SmoothWin * aSmoothWin);
	void push_smoothwin(SmoothWin * win, spx_word16_t data);
	spx_word16_t max_smoothwin(SmoothWin * win);
	spx_word16_t min_smoothwin(SmoothWin * win);
	spx_word16_t sum_smoothwin(SmoothWin * win);
	spx_word16_t mean_smoothwin(SmoothWin * win);


	typedef struct CircleBuffer1D
	{
		int write_ptr;
		int size;
	    char * data;
	} CircleBuffer1D;
	typedef struct CircleBuffer2D
	{
		int write_ptr;
		int r_size;
		int c_size;
		char ** data;
	} CircleBuffer2D;

	CircleBuffer1D * NewCircleBuffer1D(int size);
	CircleBuffer2D * NewCircleBuffer2D(int r_size, int c_size);

	void FreeCircleBuffer1D(CircleBuffer1D * st);
	void FreeCircleBuffer2D(CircleBuffer2D * st);

	void PushCircleBuffer1D(CircleBuffer1D * st, void * data, int size);
	void PushCircleBuffer2D(CircleBuffer2D * st, void ** data, int r_size, int c_size);

	struct SKVRealBuffer_;
	typedef struct SKVRealBuffer_ SKVRealBuffer;

	SKVRealBuffer *skv_real_buffer_init(int size, int matrix_r_size, int matrix_c_size, int flag);

	void skv_real_buffer_destroy(SKVRealBuffer *st);

	void skv_real_buffer_clear(SKVRealBuffer *st);

	bool skv_real_buffer_write(SKVRealBuffer *st, RealMatrix data);

	RealMatrix skv_real_buffer_read(SKVRealBuffer *st, RealMatrix out_data, int iTh);

	spx_word16_t* skv_real_buffer_scan(SKVRealBuffer *st, int iTh);

	RealMatrix skv_real_buffer_mean(SKVRealBuffer *st, RealMatrix out_data);

	RealMatrix skv_real_buffer_sum(SKVRealBuffer *st, RealMatrix out_data);

	RealMatrix skv_real_buffer_max(SKVRealBuffer *st, RealMatrix out_data);

	RealMatrix skv_real_buffer_min(SKVRealBuffer *st, RealMatrix out_data);

	struct SKVComplexBuffer_;
	typedef struct SKVComplexBuffer_ SKVComplexBuffer;

	SKVComplexBuffer *skv_complex_buffer_init(int size, int matrix_r_size, int matrix_c_size, int flag);

	void skv_complex_buffer_destroy(SKVComplexBuffer *st);

	void skv_complex_buffer_clear(SKVComplexBuffer *st);

	bool skv_complex_buffer_write(SKVComplexBuffer *st, ComplexMatrix data);

	ComplexMatrix skv_complex_buffer_read(SKVComplexBuffer *st, ComplexMatrix out_data, int iTh);

	Complex* skv_complex_buffer_scan(SKVComplexBuffer *st, int iTh);

	ComplexMatrix skv_complex_buffer_mean(SKVComplexBuffer *st, ComplexMatrix out_data);

	ComplexMatrix skv_complex_buffer_sum(SKVComplexBuffer *st, ComplexMatrix out_data);

	typedef struct CircleBuff2DFloat_
	{
		int write_ptr;
		int r_write_ptr;
		int len;
		int r_size;
		int c_size;
		spx_word16_t* data;
		spx_word16_t* sum;
		spx_word16_t* avg;
	} CircleBuff2DFloat;
	CircleBuff2DFloat init_Float2Dbuffer(int r_size, int c_size);
	CircleBuff2DFloat destroy_Float2Dbuffer(CircleBuff2DFloat* buffer);
	void clear_Float2Dbuffer(CircleBuff2DFloat* buffer);
	void push_Float2Dbuffer(CircleBuff2DFloat* buffer, spx_word16_t* data);
	spx_word16_t* mean_Float2Dbuffer(CircleBuff2DFloat* buffer);

	typedef struct CountBuffer_
	{
		int write_ptr;
		int size;
		skv_int32_t* data;
		skv_int32_t sum;
	} CountBuffer;
	CountBuffer* init_countbuffer(int size);
	CountBuffer* destroy_countbuffer(CountBuffer* buffer);
	void clear_countbuffer(CountBuffer* buffer);
	void push_countbuffer(CountBuffer* buffer, skv_word16_t data);
	skv_int32_t sum_countbuffer(CountBuffer* buffer);

	typedef struct PulseBuffer_
	{
		CountBuffer* stable_buffer;
		int stable_buffer_size;
		int stable_dicision_size;
		spx_word16_t stable_value;

		int write_ptr;
		int size;
		spx_word16_t* data;
	} PulseBuffer;

	PulseBuffer* skv_pulsebuffer_init(int size, int stable_buffer_size, int stable_disicion_size);
	PulseBuffer* skv_pulsebuffer_destroy(PulseBuffer* st);
	void skv_pulsebuffer_clear(PulseBuffer* st);
	spx_word16_t skv_pulsebuffer_read(PulseBuffer* st, int iTh);
	void skv_pulsebuffer_write(PulseBuffer* st, spx_word16_t data, int STABLE_DECISION_THRESH);
	float skv_pulsebuffer_stable(PulseBuffer* st);
	int skv_pulsebuffer_jump(PulseBuffer* st, int jump_len, float jump_thresh);

	spx_word16_t * NewFloatVec1D(int size);
	spx_word16_t ** NewFloatVec2D(int r_size, int c_size);

	spx_word16_t * FreeFloatVec1D(spx_word16_t * st);
	spx_word16_t ** FreeFloatVec2D(spx_word16_t ** st, int r_size);

	void SetVecZeros1(spx_word16_t * data, int offset, int count);
	void SetVecZeros2(int * data, int offset, int count);
	void SetVecOnes(spx_word16_t * data, int offset, int count);
	void SetVecValue(spx_word16_t * data, spx_word16_t value, int offset, int count);

	void VecPowOp1(spx_word16_t * in_data, spx_word16_t * out_data, int size, float value);
	void VecPowOp2(spx_word16_t * in_data, spx_word16_t * out_data, int size);

	void VecMultiOp1(spx_word16_t * x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size);
	void VecMultiOp2(spx_word16_t * in_data, float value, spx_word16_t * out_data, int size);
	void VecMultiOp3(float x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size);

	void VecDivOp1(spx_word16_t * x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size);
	void VecDivOp2(spx_word16_t * x_data, float y_data, spx_word16_t * out_data, int size);
	void VecDivOp3(float x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size);

	void VecAddOp1(spx_word16_t * x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size);
	void VecAddOp2(spx_word16_t * x_data, float y_data, spx_word16_t * out_data, int size);
	void VecAddOp3(float x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size);

	void VecMinusOp1(spx_word16_t * x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size);
	void VecMinusOp2(spx_word16_t * x_data, float y_data, spx_word16_t * out_data, int size);
	void VecMinusOp3(float x_data, spx_word16_t * y_data, spx_word16_t * out_data, int size);

	void VecSetOp1(spx_word16_t * x_data, spx_word16_t * y_data, int size);
	void VecSetOp2(spx_word16_t * x_data, float y_data, int size);

	void VecBandOp(spx_word16_t * x_data, float low_band, float up_band, spx_word16_t * out_data, int size);
	void VecLowBandOp(spx_word16_t * x_data, float low_band, spx_word16_t * out_data, int size);
	void VecUpBandOp(spx_word16_t * x_data, float up_band, spx_word16_t * out_data, int size);

	void VecExpOp(spx_word16_t * x_data, spx_word16_t * out_data, int size);

	float VecMeanOp(spx_word16_t * x_data, int s_idx, int e_idx);

	float VecSumOp1(spx_word16_t * x_data, int s_idx, int e_idx);
	float VecSumOp2(int * x_data, int s_idx, int e_idx);
	
	void VecDynamicMeanOp(spx_word16_t * x_data, spx_word16_t * y_data, int size, int frame);
	void VecDynamicMaxOp(spx_word16_t * x_data, spx_word16_t * y_data, int size);
	void VecDynamicMinOp(spx_word16_t * x_data, spx_word16_t * y_data, int size);
	

#ifdef __cplusplus 
}
#endif  

#endif
