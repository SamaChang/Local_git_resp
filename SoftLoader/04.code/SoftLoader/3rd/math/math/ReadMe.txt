���㻯��ѧ�����Ľṹ


���1��skv_math_core 
	1������ʵ��֮��ļӼ��˳���ͨ���궨��ʵ�֣����綨��ܶ����������ĺ� 
	2����������֮��ļӼ��˳�
	3������ʵ��֮��ļӼ��˳�
	
Complex* dot_product_complex1(Complex *a, Complex *b, Complex *out, spx_uint32_t len);
Complex* dot_product_complex2(Complex a, Complex *b, Complex *out, spx_uint32_t len);
Complex* dot_product_complex3(Complex *a, Complex b, Complex *out, spx_uint32_t len);

spx_word16_t* dot_product_real1(spx_word16_t *a, spx_word16_t *b, spx_word16_t *out, spx_uint32_t len);
spx_word16_t* dot_product_real2(spx_word16_t a, spx_word16_t *b, spx_word16_t *out, spx_uint32_t len);
spx_word16_t* dot_product_real3(spx_word16_t *a, spx_word16_t b, spx_word16_t *out, spx_uint32_t len);

Complex* dot_product_complex_real1(Complex *a, spx_word16_t *b, Complex *out, spx_uint32_t len);
Complex* dot_product_complex_real2(Complex a, spx_word16_t *b, Complex *out, spx_uint32_t len);
Complex* dot_product_complex_real3(Complex *a, spx_word16_t b, Complex *out, spx_uint32_t len);

Complex* dot_product_real_complex1(spx_word16_t *a, Complex *b, Complex *out, spx_uint32_t len);
Complex* dot_product_real_complex2(spx_word16_t a, Complex *b, Complex *out, spx_uint32_t len);
Complex* dot_product_real_complex3(spx_word16_t *a, Complex b, Complex *out, spx_uint32_t len);