#ifndef THE2_H
#define THE2_H
#define MAX_VAL 999999
#define MIN_VAL -999999

void print_first_n_row(double **matrix, int n, int row_size);

double **initialize_the_data(int *row_count, int *row_size);

void calculate_distance(double **matrix, int row_size, int row1, int row2);

void calculate_dot_product(double **matrix, int row_size, int row1, int row2);

double **calculate_covariance_matrix(double **matrix, int row_count, int row_size);

double **calculate_x_transpose_times_x(double **matrix, int row_count, int row_size);

double **group_by(double **matrix, int *group_count, int row_count, int row_size, int group_column, int operation);

double **convolution(double **matrix, int row_count, int row_size, double **kernel, int kernel_height, int kernel_width);

#endif
