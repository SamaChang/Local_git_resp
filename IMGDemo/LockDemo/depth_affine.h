#pragma once

#include "matrix/SquareMatrix.hpp"
#include "matrix/Vector3.hpp"


typedef struct
{
    int x;
    int y;
    int w;
    int h;
}TsmRoi;

void get_RT(matrix::SquareMatrix<float, 3> &align_R,
                   matrix::Vector3<float> &align_T);

void depth_affine(uint16_t *src, uint16_t *dst, int h, int w,
                        matrix::SquareMatrix<float, 3> &R,
                        matrix::Vector3<float> &T);

void depth_affine_api(uint16_t *src, uint16_t *dst, int h, int w,TsmRoi *roi);