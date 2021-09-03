#include "skv_fastmath.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SKV_LOG2_SIZE       (1024)  //(512)
#define SKV_LOG2_SIZE_L2    (10)    //(9)

static ieee754_float32_t log_table[SKV_LOG2_SIZE+1];

void skv_logtab_init()
{
    int j;
    assert((1<<SKV_LOG2_SIZE_L2) == SKV_LOG2_SIZE);
    for (j = 0; j < SKV_LOG2_SIZE+1; j++)
        log_table[j] = log(1.0f+j/(ieee754_float32_t)SKV_LOG2_SIZE)/log(2.0f);
}

ieee754_float32_t skv_fast_log2(ieee754_float32_t x)
{
    ieee754_float32_t log2val;
    union {
        ieee754_float32_t f;
        int     i;
    } fi;
    int mantisse;
    fi.f = x;
    mantisse =   fi.i & 0x7fffff;
    log2val  =   ((fi.i>>23) & 0xFF)-0x7f;
    mantisse >>= (23-SKV_LOG2_SIZE_L2);
    log2val  +=  log_table[mantisse];

    return log2val;
}

//angle function
float skv_fast_sin(float angle)
{
	float real_angle;
	float square,result;
	int sign;

    /*normalize the angle in [0,2*M_PI]*/
	angle = angle + M_PI_MUL2;
	angle = fmodf(angle, M_PI_MUL2);	//now the angle is in(0,2*M_PI)

	if (angle <= M_PI) {
		real_angle = M_PI - angle;
		angle      = SKV_MIN(real_angle, angle);
		sign = 1;
	} else {
		angle	   = angle - M_PI;
		real_angle = M_PI - angle;
		angle      = SKV_MIN(real_angle, angle);
		sign       = -1;
	}
	
    /*do fast compute*/
	square =  angle*angle;
    result =  7.61e-03f;
    result *= square;
    result -= 1.6605e-01f;
    result *= square;
    result += 1.0f;
    result *= angle;

    return result*sign;

}

float skv_fast_cos(float angle)
{
	float real_angle;
	float square,result;
	int sign;

    /*normalize the angle in [0,2*M_PI]*/
	angle = angle + M_PI_MUL2;
	angle = fmodf(angle, M_PI_MUL2);	//now the angle is in(0,2*M_PI)

	if (angle <= M_PI){
		real_angle = M_PI - angle;
		/*sign       = (M_PI_DIV2 - angle)/SKV_ABS(M_PI_DIV2 - angle);*/
		sign       = ((M_PI_DIV2 - angle) >= 0 ? 1 : -1);
		angle      = SKV_MIN(real_angle,angle);
	}else{
		angle	   = angle - M_PI;
		real_angle = M_PI - angle;
		/*sign	   = (angle - M_PI_DIV2)/SKV_ABS(angle - M_PI_DIV2);*/
		sign	   = ((angle - M_PI_DIV2) >= 0 ? 1 : -1);
		angle      = SKV_MIN(real_angle,angle);
	}

    /*do fast compute*/
    square = angle*angle;
    result = 3.705e-02f;
    result *= square;
    result -= 4.967e-01f;
    result *= square;
    result += 1.0f;

    return result*sign;
}

/*value should be (-1,1)*/
static float fast_atan (float value)
{
    float square = value*value;
    float result = 0.0208351f;

    result *= square;
    result -= 0.085133f;
    result *= square;
    result += 0.180141f;
    result *= square;
    result -= 0.3302995f;
    result *= square;
    result += 0.999866f;
    result *= value;

    return result;
}


float skv_fast_atan2(float y, float x)
{
    float sita;
    float abs_y, abs_x;

    abs_y = SKV_ABS(y);
    abs_x = SKV_ABS(x);

    if (abs_y >= abs_x) {
        if (y > 0)
            sita = M_PI_DIV2 - fast_atan(x/y);
        else 
            sita = M_PI_DIV2 - fast_atan(x/y) - M_PI;

    } else  {
        if (x > 0)
            sita = fast_atan(y/x);
        else 
            sita = fast_atan(y/x) - M_PI;
    }

    return sita;
}


float skv_fast_invsqrtf(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);       
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);       
    
    return x;
}


float skv_fast_sqrtf(float number)
{
    int i;   
    float x, y;   
    const float f = 1.5F;    
    x = number * 0.5F;  
    y  = number;   
    i  = * ( int * ) &y;    
    i  = 0x5f3759df - ( i >> 1 );    
    y  = * ( float * ) &i;    
    y  = y * ( f - ( x * y * y ) );    
    y  = y * ( f - ( x * y * y ) );    
    return number * y;    
}

/*float skv_fast_sqrtf(float f)
{
	float result;
	_asm
	{
		mov eax, f
		sub eax, 0x3f800000
		sar eax, 1
		add eax, 0x3f800000
		mov result, eax
	}
	return result;
}*/




