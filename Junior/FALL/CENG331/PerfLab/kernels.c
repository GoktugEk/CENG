/********************
 * Kernels to be optimized for the Metu Ceng Performance Lab
 ********************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following team struct
 */
team_t team = {
        "Team",                     /* Team name */

        "Göktuğ ekinci",             /* First member full name */
        "e2380343",                 /* First member id */

        "Hasan Bal",                         /* Second member full name (leave blank if none) */
        "e2380160",                         /* Second member id (leave blank if none) */

        "Mustafa Gilli",                         /* Third member full name (leave blank if none) */
        "e2310035"                          /* Third member id (leave blank if none) */
};

/******
 * EXPOSURE FUSION KERNEL *
 ******/

/*******************
 * Your different versions of the exposure fusion kernel go here
 *******************/

/*
 * naive_fusion - The naive baseline version of exposure fusion
 */
char naive_fusion_descr[] = "naive_fusion: Naive baseline exposure fusion";
void naive_fusion(int dim, int *img, int *w, int *dst) {

    int i, j, k;
    for(k = 0; k < 4; k++){
        for(i = 0; i < dim; i++) {
            for(j = 0; j < dim; j++) {
                dst[i*dim+j] += w[k*dim*dim+i*dim+j] * img[k*dim*dim+i*dim+j];
            }
        }
    }



}

/*
 * fusion - Your current working version of fusion
 * IMPORTANT: This is the version you will be graded on
 */
char fusion_descr[] = "fusion: Current working version";
void fusion(int dim, int *img, int *w, int *dst)
{
    int i, j, k,t2,dimdim,t3,t4,t22,t44,temp1,temp2;
    dimdim = dim*dim;
    for(k = 0; k < 4; k++){
        t3 = k*dimdim;
        for(i = 0; i < dim; i+=2) {
            t2 = i*dim;
            t22 = (i+1)*dim;
            for(j = 0; j < dim; j+=2) {
                t4 = t3 +t2 +j;
                t44 = t3 +t22 +j;
                temp1 = t2 +j;
                temp2 = t22 + j;
                dst[temp1] += w[t4] * img[t4];
                dst[temp1 + 1] += w[t4+1] * img[t4+1];
                dst[temp2]  += w[t44] * img[t44];
                dst[temp2+1]  += w[t44+1] * img[t44+1];
            }
        }
    }
}

/***********************
 * register_fusion_functions - Register all of your different versions
 *     of the fusion kernel with the driver by calling the
 *     add_fusion_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 ***********************/

void register_fusion_functions()
{
    add_fusion_function(&naive_fusion, naive_fusion_descr);
    add_fusion_function(&fusion, fusion_descr);
    /* ... Register additional test functions here */
}

/*********
 * GAUSSIAN BLUR KERNEL *
 *********/

/******************
 * Your different versions of the Gaussian blur functions go here
 ******************/

/*
 * naive_blur - The naive baseline version of Gussian blur
 */
char naive_blur_descr[] = "naive_blur The naive baseline version of Gaussian blur";
void naive_blur(int dim, float *img, float *flt, float *dst) {

    int i, j, k, l;

    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
            for(k = 0; k < 5; k++){
                for(l = 0; l < 5; l++) {
                    dst[i*dim+j] = dst[i*dim+j] + img[(i+k)*dim+j+l] * flt[k*dim+l];
                }
            }
        }
    }

}

/*
 * blur - Your current working version of Gaussian blur
 * IMPORTANT: This is the version you will be graded on
 */
char blur_descr[] = "blur: Current working version";
void blur(int dim, float *img, float *flt, float *dst)
{
    unsigned short i,j,i1;
    int idx,fltidx;
    float sum1,sum2,sum3,sum4,sum5,sum6,sum7,sum8,f0,f1,f2,f3,f4;
    //general loops
    for ( i = 0; i < dim - 4; ++i) {
        for (j = 0; j < dim - 7; j += 8) {
            //block loops
            sum1 = 0;
            sum2 = 0;
            sum3 = 0;
            sum4 = 0;
            sum5 = 0;
            sum6 = 0;
            sum7 = 0;
            sum8 = 0;

            for (i1 = i; i1 < i + 5; ++i1) {
                idx = i1 * dim + j;
                fltidx = (i1 - i) * dim;

                f0 = flt[fltidx];
                f1 = flt[fltidx + 1];
                f2 = flt[fltidx + 2];
                f3 = flt[fltidx + 3];
                f4 = flt[fltidx + 4];


                sum1 += img[idx] * f0;
                sum2 += img[idx + 1] * f0;
                sum3 += img[idx + 2] * f0;
                sum4 += img[idx + 3] * f0;
                sum5 += img[idx + 4] * f0;
                sum6 += img[idx + 5] * f0;
                sum7 += img[idx + 6] * f0;
                sum8 += img[idx + 7] * f0;

                sum1 += img[idx + 1] * f1;
                sum2 += img[idx + 2] * f1;
                sum3 += img[idx + 3] * f1;
                sum4 += img[idx + 4] * f1;
                sum5 += img[idx + 5] * f1;
                sum6 += img[idx + 6] * f1;
                sum7 += img[idx + 7] * f1;
                sum8 += img[idx + 8] * f1;

                sum1 += img[idx + 2] * f2;
                sum2 += img[idx + 3] * f2;
                sum3 += img[idx + 4] * f2;
                sum4 += img[idx + 5] * f2;
                sum5 += img[idx + 6] * f2;
                sum6 += img[idx + 7] * f2;
                sum7 += img[idx + 8] * f2;
                sum8 += img[idx + 9] * f2;

                sum1 += img[idx + 3] * f3;
                sum2 += img[idx + 4] * f3;
                sum3 += img[idx + 5] * f3;
                sum4 += img[idx + 6] * f3;
                sum5 += img[idx + 7] * f3;
                sum6 += img[idx + 8] * f3;
                sum7 += img[idx + 9] * f3;
                sum8 += img[idx + 10] * f3;

                sum1 += img[idx + 4] * f4;
                sum2 += img[idx + 5] * f4;
                sum3 += img[idx + 6] * f4;
                sum4 += img[idx + 7] * f4;
                sum5 += img[idx + 8] * f4;
                sum6 += img[idx + 9] * f4;
                sum7 += img[idx + 10] * f4;
                sum8 += img[idx + 11] * f4;


            }
            idx = i * dim + j;

            dst[(idx)] = sum1;
            dst[(idx) + 1] = sum2;
            dst[(idx) + 2] = sum3;
            dst[(idx) + 3] = sum4;
            dst[(idx) + 4] = sum5;
            dst[(idx) + 5] = sum6;
            dst[(idx) + 6] = sum7;
            dst[(idx) + 7] = sum8;


        }
    }

}

/************************
 * register_blur_functions - Register all of your different versions
 *     of the gaussian blur kernel with the driver by calling the
 *     add_blur_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 ***********************/

void register_blur_functions()
{
    add_blur_function(&naive_blur, naive_blur_descr);
    add_blur_function(&blur, blur_descr);
    /* ... Register additional test functions here */
}
