/************************************************************************************
   Copyright (C) 2021 tsingmicro
*   Written by Jiayu Su 2021                                                        *
*	Function:                                                                       *
*		The function for ANC and EQ
*
*				                                                                    *
*************************************************************************************/

#ifndef SKV_WOLF_FUNCTION_H
#define SKV_WOLF_FUNCTION_H



#ifdef __cplusplus
extern "C" {
#endif
	/**
	 * @brief wolf_function_peak    计算峰值算法
	 * @param fc                    中心频点
	 * @param boost                 增益值
	 * @param Q                     波的宽窄设置bundWidth
	 * @param fs                    采样频率
	 * @param Total_gain            总音量
	 * @param IIR_out               输出6个double组成的IIR值[b0,b1,b2,a0,a1,a2]
	 */
	void wolf_function_peak(int fc, double boost, double Q, int fs, double Total_gain, double*IIR_out);
	/**
	 * @brief wolf_function_high_shelving   计算高搁置算法
	 * @param gain_db                       总音量
	 * @param fc                            中心频点
	 * @param fs                            采样频率
	 * @param slope                         坡度
	 * @param IIR_out                       输出6个double组成的IIR值[b0,b1,b2,a0,a1,a2]
	 */
	void wolf_function_high_shelving(double gain_db, int fc, int fs, double slope, double*IIR_out);
	/**	20210708应张晓辉要求添加boost，将gain改名boost,添加一个gain控制波形上下平移
	 * @brief wolf_function_high_shelving   计算高搁置算法
	 * @param boost							增益值
	 * @param gain_db                       总音量
	 * @param fc                            中心频点
	 * @param fs                            采样频率
	 * @param slope                         坡度
	 * @param IIR_out                       输出6个double组成的IIR值[b0,b1,b2,a0,a1,a2]
	 */
	void wolf_function_high_shelving_new(double boost, double gain_db, int fc, int fs, double slope, double*IIR_out);
	/**
	 * @brief wolf_function_low_shelving    计算低搁置算法
	 * @param gain_db                       总音量
	 * @param fc                            中心频点
	 * @param fs                            采样频率
	 * @param slope                         坡度
	 * @param IIR_out                       输出6个double组成的IIR值[b0,b1,b2,a0,a1,a2]
	 */
	void wolf_function_low_shelving(double gain_db, int fc, int fs, double slope, double*IIR_out);
	/**	20210708应张晓辉要求添加boost，将gain改名boost,添加一个gain控制波形上下平移
	 * @brief wolf_function_low_shelving    计算低搁置算法
	 * @param boost							增益值
	 * @param gain_db                      总音量
	 * @param fc                            中心频点
	 * @param fs                            采样频率
	 * @param slope                         坡度
	 * @param IIR_out                       输出6个double组成的IIR值[b0,b1,b2,a0,a1,a2]
	 */
	void wolf_function_low_shelving_new(double boost, double gain_db, int fc, int fs, double slope, double*IIR_out);
	/**
	 * @brief wolf_function_high_pass       计算高通过算法
	 * @param fs                            采样频率
	 * @param fc                            中心频点
	 * @param Q                             波的宽窄设置bundWidth
	 * @param Total_gain                    总音量
	 * @param IIR_out                       输出6个double组成的IIR值[b0,b1,b2,a0,a1,a2]
	 */
	void wolf_function_high_pass(int fs, int fc, double Q, double Total_gain, double*IIR_out);
	/**
	 * @brief wolf_function_low_pass        计算低通过算法
	 * @param fs                            采样频率
	 * @param fc                            中心频点
	 * @param Q                             波的宽窄设置bundWidth
	 * @param Total_gain                    总音量
	 * @param IIR_out                       输出6个double组成的IIR值[b0,b1,b2,a0,a1,a2]
	 */
	void wolf_function_low_pass(int fs, int fc, double Q, double Total_gain, double*IIR_out);
	/**
	 * @brief print_freqz       模拟matlab的freqz函数，计算nWavePoints个点的freqz_IIR1
	 * @param frequency         caiyangpinl
	 * @param order             设置分子分母数 从0开始
	 * @param a                 分母集合
	 * @param b                 分子集合
	 * @param H_z               复数集合nWavePoints*2
	 * @param nWavePoints       生成数据总数
	 * @return
	 */
	int print_freqz(int frequency, int order, double * a, double* b, double*H_z, int nWavePoints);
#ifdef __cplusplus
}
#endif

#endif
