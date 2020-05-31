#include <stdio.h>
#include "../the2.h"
#include<stdlib.h>

int main()
{
    double **matrix, **result, **covariance_matrix, **group_matrix, **kernel, **convoluted;
    int i,row_size = 0, row_count = 0, kernel_height = 3, kernel_width = 3,group_count;

    matrix = initialize_the_data(&row_count, &row_size);

    kernel = (double**)malloc(3*sizeof(double));
    
    for(i=0;i<3;i++){
        kernel[i] = malloc(3*sizeof(double));
    }
    kernel[0][0] = 1;
    kernel[0][1] = 0;
    kernel[0][2] = 1;
    kernel[1][0] = 0;
    kernel[1][1] = 1;
    kernel[1][2] = 0;
    kernel[2][0] = 1;
    kernel[2][1] = 0;
    kernel[2][2] = 1;



    print_first_n_row(matrix, row_count, row_size);
    printf("\n\n");
    print_first_n_row(matrix, 1, row_size);
    printf("\n\n");



    calculate_dot_product(matrix, row_size, 1, 3);
    printf("\n"); 
    calculate_dot_product(matrix, row_size, 1, 1);
    printf("\n\n"); 

    result = calculate_x_transpose_times_x(matrix, row_count, row_size);
    print_first_n_row(result, row_size, row_size);
    printf("\n\n");

    covariance_matrix = calculate_covariance_matrix(matrix, row_count, row_size);
    print_first_n_row(covariance_matrix, row_size, row_size);
    printf("\n\n");

    group_matrix = group_by(matrix, &group_count, row_count, row_size, 2, 0);
    print_first_n_row(group_matrix, group_count, row_size);
    printf("\n\n");

    group_matrix = group_by(matrix, &group_count, row_count, row_size, 2, 1);
    print_first_n_row(group_matrix, group_count, row_size);
    printf("\n\n");

    group_matrix = group_by(matrix, &group_count, row_count, row_size, 5, 2);
    print_first_n_row(group_matrix, group_count, row_size);   
    printf("\n\n");

    group_matrix = group_by(matrix, &group_count, row_count, row_size, 5, 3);
    print_first_n_row(group_matrix, group_count, row_size); 
    printf("\n\n");

    convoluted = convolution(matrix, row_count, row_size, kernel, kernel_height, kernel_width);
    print_first_n_row(convoluted, row_count - kernel_height + 1, row_size - kernel_width + 1);
    printf("\n\n");

    convoluted = convolution(matrix, row_count, row_size, kernel, kernel_height, kernel_width);
    print_first_n_row(convoluted, row_count - kernel_height + 1, row_size - kernel_width + 1);
    
    return 0;
}