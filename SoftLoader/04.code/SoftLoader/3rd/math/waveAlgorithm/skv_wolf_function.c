/************************************************************************************
    Copyright (C) 2021 tsingmicro
*   Written by Jiayu Su 2021                                                        *
*	Function:                                                                       *
*		The function for ANC and EQ
*
*				                                                                    *
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#ifndef pi
#define pi 3.1415926535898
#endif 
int print_freqz(int frequency, int order, double * a, double* b, double*H_z, int nWavePoints)
{
	double fenzi[2] = { +0,0 };
	double fenmu[2] = { +0,0};	
	double tmp = +0.0;	
	double  w;	
	int     i;
	int     j;	
	for (i = 0; i < nWavePoints; i++)
	{
		w = (2.0 * pi * i) / frequency;
		fenzi[0] = +0.0;
		fenzi[1] = +0.0;
		fenmu[0] = +0.0;
		fenmu[1] = +0.0;

		for (j = 0; j <= order; j++) {
			fenzi[0] = fenzi[0] + b[j] * cos(-j * w); // real
			fenzi[1] = fenzi[1] + b[j] * sin(-j * w); // imag
			fenmu[0] = fenmu[0] + a[j] * cos(-j * w); // real
			fenmu[1] = fenmu[1] + a[j] * sin(-j * w); // imag
		}
		
		tmp = fenmu[0] * fenmu[0] + fenmu[1] * fenmu[1];
		H_z[i*2] = (fenzi[0] * fenmu[0] + fenzi[1] * fenmu[1]) / tmp;
		H_z[i*2+1] = (fenzi[1] * fenmu[0] - fenzi[0] * fenmu[1]) / tmp;		
	}

	return 0;
}

void wolf_function_peak(int fc, double boost, double Q, int fs, double Total_gain, double*IIR_out)
{
	double Total_gain_db = pow(10, Total_gain / 20);
	if (abs(boost*100000) < 1 || abs(Q * 100000) < 1)
	{
		IIR_out[0] = 1;
		IIR_out[1] = 0;
		IIR_out[2] = 0;
		IIR_out[3] = 1;
		IIR_out[4] = 0;
		IIR_out[5] = 0;
	}
	else
	{
		double A = pow(10, boost / 40);
		double w0 = 2 * pi*fc / fs;
		double alpha = sin(w0) / 2 / Q;
		double b0 = 1 + alpha * A;
		double b1 = -2 * cos(w0);
		double b2 = 1 - alpha * A;
		double a0 = 1 + alpha / A;

		double a1 = b1;
		double a2 = 1 - alpha / A;

		
		IIR_out[0] = b0 ;
		IIR_out[1] = b1;
		IIR_out[2] = b2;
		IIR_out[3] = a0;
		IIR_out[4] = a1;
		IIR_out[5] = a2;
	}
	if (abs(Total_gain_db * 100000) > 0)
	{
		IIR_out[0] *= Total_gain_db;
		IIR_out[1] *= Total_gain_db;
		IIR_out[2] *= Total_gain_db;
	}
}
void wolf_function_high_shelving(double gain_db, int fc, int fs, double slope, double*IIR_out)
{
	if (abs(gain_db * 100000) < 1 || abs(slope * 100000) <1)
	{
		IIR_out[0] = 1;
		IIR_out[1] = 0;
		IIR_out[2] = 0;
		IIR_out[3] = 1;
		IIR_out[4] = 0;
		IIR_out[5] = 0;
	}
	else
	{
		double k = tan(pi*fc * 4 / 3 / fs);
		double v0 = pow(10, gain_db / 20);
		if (v0 < 1)
		{
			v0 = 1 / v0;
		}
		double root2 = 1 / (slope / pow(2, 0.5));
		IIR_out[3] = 1;
		if (gain_db < 0)
		{
			double div_factor1 = v0 + root2 * sqrt(v0)*k + k * k;
			double div_factor2 = 1 + root2 / sqrt(v0)*k + k * k / v0;
			IIR_out[0] = (1 + root2 * k + k * k) / div_factor1;
			IIR_out[1] = (2 * (k*k - 1)) / div_factor1;
			IIR_out[2] = (1 - root2 * k + k * k) / div_factor1;
			IIR_out[4] = (2 * (k*k / v0 - 1)) / div_factor2;
			IIR_out[5] = (1 - root2 / sqrt(v0)*k + k * k / v0) / div_factor2;
		}
		else
		{
			double div_factor = 1 + root2 * k + k * k;
			IIR_out[0] = (v0 + root2 * sqrt(v0)*k + k * k) / div_factor;
			IIR_out[1] = (2 * (k*k - v0)) / div_factor;
			IIR_out[2] = (v0 - root2 * sqrt(v0)*k + k * k) / div_factor;
			IIR_out[4] = (2 * (k*k - 1)) / div_factor;
			IIR_out[5] = (1 - root2 * k + k * k) / div_factor;
		}
	}
}

void wolf_function_high_shelving_new(double boost, double gain_db, int fc, int fs, double slope, double*IIR_out)
{
	double Total_gain_db = pow(10, gain_db / 20);
	if (abs(boost * 100000) < 1 || abs(slope * 100000) < 1)
	{
		IIR_out[0] = 1;
		IIR_out[1] = 0;
		IIR_out[2] = 0;
		IIR_out[3] = 1;
		IIR_out[4] = 0;
		IIR_out[5] = 0;
	}
	else
	{
		double k = tan(pi*fc * 4 / 3 / fs);
		double v0 = pow(10, boost / 20);
		if (v0 < 1)
		{
			v0 = 1 / v0;
		}
		double root2 = 1 / (slope / pow(2, 0.5));
		IIR_out[3] = 1;
		if (boost < 0)
		{
			double div_factor1 = v0 + root2 * sqrt(v0)*k + k * k;
			double div_factor2 = 1 + root2 / sqrt(v0)*k + k * k / v0;
			IIR_out[0] = (1 + root2 * k + k * k) / div_factor1;
			IIR_out[1] = (2 * (k*k - 1)) / div_factor1;
			IIR_out[2] = (1 - root2 * k + k * k) / div_factor1;
			IIR_out[4] = (2 * (k*k / v0 - 1)) / div_factor2;
			IIR_out[5] = (1 - root2 / sqrt(v0)*k + k * k / v0) / div_factor2;
		}
		else
		{
			double div_factor = 1 + root2 * k + k * k;
			IIR_out[0] = (v0 + root2 * sqrt(v0)*k + k * k) / div_factor;
			IIR_out[1] = (2 * (k*k - v0)) / div_factor;
			IIR_out[2] = (v0 - root2 * sqrt(v0)*k + k * k) / div_factor;
			IIR_out[4] = (2 * (k*k - 1)) / div_factor;
			IIR_out[5] = (1 - root2 * k + k * k) / div_factor;
		}
	}
	if (abs(Total_gain_db * 100000) > 0)
	{
		IIR_out[0] *= Total_gain_db;
		IIR_out[1] *= Total_gain_db;
		IIR_out[2] *= Total_gain_db;
	}
}

void wolf_function_low_shelving(double gain_db, int fc, int fs, double slope, double*IIR_out)
{
	if (abs(gain_db * 100000) < 1 || abs(slope * 100000) < 1)
	{
		IIR_out[0] = 1;
		IIR_out[1] = 0;
		IIR_out[2] = 0;
		IIR_out[3] = 1;
		IIR_out[4] = 0;
		IIR_out[5] = 0;
	}
	else
	{
		double k = tan(pi*fc * 4 / 3 / fs);
		double v0 = pow(10, gain_db / 20);
		if (v0 < 1)
		{
			v0 = 1 / v0;
		}
		double root2 = 1 / (slope / pow(2, 0.5));
		
		IIR_out[3] = 1;
		if (gain_db > 0)
		{
			double div_factor = 1 + root2 * k + k * k;
			//IIR_out[0] = (1 + sqrt(v0)*root2*k + v0 * k*k) / div_factor;
			IIR_out[0] = (1 + sqrt(v0)*root2*k + v0 * k*k) / div_factor;
			IIR_out[1] = (2 * (v0*k*k - 1)) / div_factor;
			IIR_out[2] = (1 - sqrt(v0)*root2*k + v0 * k*k) / div_factor;
			IIR_out[4] = (2 * (k*k - 1)) / div_factor;
			IIR_out[5] = (1 - root2 * k + k * k) / div_factor;
		}
		else
		{
			double div_factor = 1 + root2 * sqrt(v0)*k + v0 * k*k;
			IIR_out[0] = (1 + root2 * k + k * k) / div_factor;
			IIR_out[1] = (2 * (k*k - 1)) / div_factor;
			IIR_out[2] = (1 - root2 * k + k * k) / div_factor;
			IIR_out[4] = (2 * (v0*k*k - 1)) / div_factor;
			IIR_out[5] = (1 - root2 * sqrt(v0)*k + v0 * k*k) / div_factor;
		}
	}	
}

void wolf_function_low_shelving_new(double boost, double gain_db, int fc, int fs, double slope, double*IIR_out)
{
	double Total_gain_db = pow(10, gain_db / 20);
	if (abs(boost * 100000) < 1 || abs(slope * 100000) < 1)
	{
		IIR_out[0] = 1;
		IIR_out[1] = 0;
		IIR_out[2] = 0;
		IIR_out[3] = 1;
		IIR_out[4] = 0;
		IIR_out[5] = 0;
	}
	else
	{
		double k = tan(pi*fc * 4 / 3 / fs);
		double v0 = pow(10, boost / 20);
		if (v0 < 1)
		{
			v0 = 1 / v0;
		}
		double root2 = 1 / (slope / pow(2, 0.5));
		IIR_out[3] = 1;
		if (boost > 0)
		{
			double div_factor = 1 + root2 * k + k * k;
			//IIR_out[0] = (1 + sqrt(v0)*root2*k + v0 * k*k) / div_factor;
			IIR_out[0] = (1 + sqrt(v0)*root2*k + v0 * k*k) / div_factor;
			IIR_out[1] = (2 * (v0*k*k - 1)) / div_factor;
			IIR_out[2] = (1 - sqrt(v0)*root2*k + v0 * k*k) / div_factor;
			IIR_out[4] = (2 * (k*k - 1)) / div_factor;
			IIR_out[5] = (1 - root2 * k + k * k) / div_factor;
		}
		else
		{
			double div_factor = 1 + root2 * sqrt(v0)*k + v0 * k*k;
			IIR_out[0] = (1 + root2 * k + k * k) / div_factor;
			IIR_out[1] = (2 * (k*k - 1)) / div_factor;
			IIR_out[2] = (1 - root2 * k + k * k) / div_factor;
			IIR_out[4] = (2 * (v0*k*k - 1)) / div_factor;
			IIR_out[5] = (1 - root2 * sqrt(v0)*k + v0 * k*k) / div_factor;
		}
	}
	
	if (abs(Total_gain_db * 100000) > 0)
	{
		IIR_out[0] *= Total_gain_db;
		IIR_out[1] *= Total_gain_db;
		IIR_out[2] *= Total_gain_db;
	}
}

void wolf_function_high_pass(int fs, int fc, double Q, double Total_gain, double*IIR_out)
{
	double Total_gain_db = pow(10, Total_gain / 20);
	if (abs(Q * 100000) < 1 /*|| abs(Total_gain) < 0.00001*/)
	{
		IIR_out[0] = 1;
		IIR_out[1] = 0;
		IIR_out[2] = 0;
		IIR_out[3] = 1;
		IIR_out[4] = 0;
		IIR_out[5] = 0;
	}
	else
	{
		double omega = 2 * pi*fc / fs;
		double sin_1 = sin(omega);
		double cos_1 = cos(omega);
		double alpha = sin_1 / (1.5*Q);
		
		IIR_out[0] = (1 + cos_1) / 2 * Total_gain_db;
		IIR_out[1] = -(1 + cos_1)*Total_gain_db;
		IIR_out[2] = IIR_out[0];
		IIR_out[3] = 1 + alpha;
		IIR_out[4] = -2 * cos_1;
		IIR_out[5] = 1 - alpha;
	}
}
void wolf_function_low_pass(int fs, int fc, double Q, double Total_gain, double*IIR_out)
{
	double Total_gain_db = pow(10, Total_gain / 20);
	if (abs(Q * 100000) < 1 /*|| abs(Total_gain) < 0.00001*/)
	{
		IIR_out[0] = 1;
		IIR_out[1] = 0;
		IIR_out[2] = 0;
		IIR_out[3] = 1;
		IIR_out[4] = 0;
		IIR_out[5] = 0;
	}
	else
	{
		double omega = 2 * pi*fc / fs;
		double sin_1 = sin(omega);
		double cos_1 = cos(omega);
		double alpha = sin_1 / (1.5*Q);
		
		IIR_out[0] = (1 - cos_1) / 2 * Total_gain_db;
		IIR_out[1] = (1 - cos_1)*Total_gain_db;
		IIR_out[2] = IIR_out[0];
		IIR_out[3] = 1 + alpha;
		//IIR_out[4] = -2 * alpha;
		IIR_out[4] = -2 * cos_1;
		IIR_out[5] = 1 - alpha;
	}
	
}

