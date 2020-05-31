#include <stdio.h>
#include "../the2.h"
#include<stdlib.h>

int main()
{
    double **matrix, **result, **group_matrix;
    int row_size = 0, row_count = 0,group_count;

    matrix = initialize_the_data(&row_count, &row_size);


    




    print_first_n_row(matrix, row_count, row_size);
    printf("\n\n");
    print_first_n_row(matrix, 1, row_size);
    printf("\n\n");




    calculate_dot_product(matrix, row_size, 0, 0);
    printf("\n\n"); 

    result = calculate_x_transpose_times_x(matrix, row_count, row_size);
    print_first_n_row(result, row_size, row_size);
    printf("\n\n");


    group_matrix = group_by(matrix, &group_count, row_count, row_size, 0, 0);
    print_first_n_row(group_matrix, group_count, row_size);
    printf("\n\n");



    
    return 0;
}
