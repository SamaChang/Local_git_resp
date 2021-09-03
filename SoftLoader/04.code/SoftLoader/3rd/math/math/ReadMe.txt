定点化数学运算库的结构


层次1：skv_math_core 
	1）两个实数之间的加减乘除，通过宏定义实现，比如定义很多类似这样的宏 
	2）两个复数之间的加减乘除
	3）两个实数之间的加减乘除
	
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