#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "the2.h"



/*
INPUT:
    int *row_count: vertical size of the matrix to be assigned (passed by reference from the main function)
    int *row_size: horizontal size of the matrix to be assigned (passed by reference from the main function)

OUTPUT:
    double **matrix: created data matrix

METHOD:
    This function creates the matrix streamed via stdin. 
    During this process, assigns row_count and row_size variables.
*/
double **initialize_the_data(int *row_count, int *row_size) { 
    double **matrix;
    int i,j;
    double number;
    matrix = malloc(16*sizeof(double));
    matrix[0] = (double*)malloc(16*sizeof(double));
    
    for(i=0;;i++){
        scanf("%lf",&number);
        if(number == -1){
            *row_size = i+1;
            matrix[0][*row_size-1] = -1;
            break;
        }
        else{
            matrix[0][i] = number;
        }
        if((i+1)%16 == 0){
            matrix[0] = realloc(matrix[0], (i+16)*sizeof(double));
        }
    }
    
    matrix[0] = realloc(matrix[0],*row_size*sizeof(double));
    
    for(i=1;*row_count == 0;i++){
        if((i+1)%16 == 0){
            matrix = realloc(matrix,(i+16)*sizeof(double));
        }
        matrix[i] = malloc(*row_size*sizeof(double));
        for(j=0;j<*row_size; j++){
            scanf("%lf",&number);
            if(number == -1 && j ==0){
                *row_count = i;
                matrix = realloc(matrix,(*row_count+1)*sizeof(double));
                matrix[i][j] = number;
                break;
            }
            matrix[i][j] = number;
        }
    }
    *row_size -= 1;

    return matrix; 
}

/*
INPUT:
    double **matrix: data matrix
    int n: number of rows to be printed
    int row_size: horizontal size of the matrix

METHOD:
    This function prints first n row of the matrix.
*/
void print_first_n_row(double **matrix, int n, int row_size) {
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<row_size;j++){
            if(i == n-1 && j == row_size -1) printf("%.4f",matrix[i][j]);
            else if(j== row_size-1 && i != n-1) printf("%.4f\n",matrix[i][j]);
            else printf("%.4f ",matrix[i][j]);
        }
    }
}

/*
INPUT:
    double **matrix: data matrix
    int row_size: horizontal size of the data matrix
    int row1: index of the first row in the calculation
    int row2: index of the second row in the calculation

METHOD:
    This function calculates dot product of the row1 and the row2 and prints it in the following format:
        Dot product of rows <row1>, <row2>: <dot_product>
*/
void calculate_dot_product(double **matrix, int row_size, int row1, int row2) {
    int i;
    double res =0;
    double a,b;
    if(row_size == 0) return;
    for(i=0;i<row_size;i++){
        a = matrix[row1][i];
        b = matrix[row2][i];
        res += a*b;
    }
    printf("Dot product of rows %d, %d: %.4f",row1,row2,res);
}

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix

OUTPUT:
    double **covariance_matrix: Created covariance matrix with size of row_size X row_size

METHOD:
    This function creates covariance matrix of the original data matrix and returns it.

*/
double mean(double col[],int n){
    int i;
    double sum=0;
    if(n == 1) return col[0];
    for(i=0;i<n;i++){
        sum += col[i];
    }
    return sum/n;
}





double covariance(double col1[],double col2[], int n){
    double sum = 0;
    int i;
    double mean1,mean2;
    mean1 = mean(col1,n);
    mean2 = mean(col2,n);
    for(i= 0; i<n;i++){
        sum += (col1[i] - mean1) * (col2[i] - mean2);
    }
    return sum/ (n-1);
}

double* column(double**matrix, int column, int row_count){
    double* col;
    int i;
    col = malloc(row_count * sizeof(double));
    for(i = 0 ; i < row_count; i++){
        col[i] = matrix[i][column];
    }
    return col;
}

double **calculate_covariance_matrix(double **matrix, int row_count, int row_size) { 
    double *col1;
    double *col2;
    double **covariance_matrix;
    int i,j;


    
    covariance_matrix = malloc(row_size*sizeof(double));

    for(i=0;i<row_size;i++){
        covariance_matrix[i] = malloc(row_size*sizeof(double));
    }

    
    for(i=0; i< row_size;i++){
        for(j = 0; j<row_size; j++){
            col1 = column(matrix,i,row_count);
            col2 = column(matrix,j,row_count);
            covariance_matrix[i][j] = covariance(col1,col2,row_count);
        }
    }

    return covariance_matrix; 
}

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix

OUTPUT:
    double **result: Created result matrix with size of row_size X row_size

METHOD:
    This function calculates x^T * x. First finds the transpose of the original data matrix and apply matrix multiplication.
    At the end it returns the calculated matrix with size of row_size X row_size.

*/


double matrix_multipication(double* col, double *row,int n){
    int i;
    double sum =0;
    for(i=0; i<n;i++){
        sum += col[i] * row[i];
    }
    return sum;
}



double **calculate_x_transpose_times_x(double **matrix, int row_count, int row_size) { 
    int i,j;
    double** res;
    double* col1,*col2;
    res = malloc(row_size*sizeof(double));
    
    for(i=0; i<row_size; i++){
        res[i] = malloc(row_size * sizeof(double));
    }

    
    for(i=0; i<row_size;i++){
        for(j=0; j<row_size;j++){
            col1 = column(matrix,j,row_count);
            col2 = column(matrix,i,row_count);
            res[i][j] =  matrix_multipication(col1, col2, row_count);
        }
    }
    
    
    return res; 
}

/*
INPUT:
    double **matrix: data matrix
    int *group_count: number of the groups to be assigned (passed by reference from the main function)
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix
    int group_column: index of the column to apply grouping over
    int operation: index of the operation to apply during grouping
        SUM -> 0
        AVG -> 1
        MAX -> 2
        MIN -> 3

OUTPUT:
    double **grouped_matrix: Created grouped matrix with size of group_count X row_size

METHOD:
    This function applies grouping over desired column index, creates a grouped matrix. It returns this grouped matrix.
    During this process it calculates group count and assigns to the variable.

*/
double absolute(double a){ /*This function gives the absolute value of value*/
    if(a<0){
        return -a;
    }
    return a;
}
double max(double a, double b){/*This function gives the max of two double variables*/
    return (a + b + absolute(a-b) ) /2;
}
double min(double a, double b){/*This function gives the min of two double variables*/
    return absolute((a + b - absolute(a-b) ) /2);
}

int isempty(int arr[],int length){/*This function checks if array is empty*/
    int i;
    for(i=0;i<length;i++){
        if(arr[i] != 0) return 0;
    }
    return 1;
}
int is_in(int arr[],int n,int number){ /*This function checks if the given value is in the array*/
    int i;
    for(i=0;i<n;i++){
        if(arr[i] == number){
            return 1;
        }
    }
    return 0;
}

int changings(int arr[],int n){ /*This function returns how many row we deleted in the matrix*/
    int i,change=0;
    for(i=0;i<n;i++){
        if(arr[i] != 0) change++;
    }
    return change;
}

int time_counter(int arr[],int length,int index){ /*This function gives how many times it is repeating in the given column*/
    if(arr[index] == 0 || index >= length){
        return 1;
    }
    return 1 + time_counter(arr,length,arr[index]);
}

double **group_by(double **matrix, int *group_count, int row_count, int row_size, int group_column, int operation) { 
    double* col, **backup;
    int i,j,k;
    int *count,*count_backup,row,*feature_numbers;

    backup = malloc(row_count*sizeof(double));
    count = malloc(row_count*sizeof(int)); /*Memory allocation*/
    count_backup = malloc(row_count*sizeof(int));
    feature_numbers = malloc(row_count*sizeof(int));
    for(i=0; i<row_count; i++){
        count[i] = 0;
        backup[i] = malloc(row_size*sizeof(double));
    }

    for(i=0;i<row_count;i++){
        for(j=0;j<row_size;j++){
            backup[i][j] = matrix[i][j];
        }
    }




    col = column(backup,group_column,row_count);
    for(i=0; i< row_count; i++){ /*Finding which rows we have to process and delete*/
        for(j=i+1; j<row_count+1;j++){
            if(col[j] == col[i]){
                count[i] = j;
                count_backup[i] = j;
                i++;
                j = i;
                continue;
            }
        }
    }
    
    
    for(i=0;i<row_count;i++){ /*Finding which variables repeats how many time*/
        feature_numbers[i] = time_counter(count,row_count,i);
    }


    
    while(!isempty(count,row_count)){ /*By using count array, processing the array with given operation*/
        for(i=0; i<row_count; i++){
            row = count[i];
            if(row == 0) ;
            else if(count[row] != 0);
            else{
                if(row != i){
                    for(k=0; k<row_size; k++){
                        if(k == group_column);
                        else if(operation == 0){
                            backup[i][k] += backup[row][k];
                        }
                        else if(operation == 1){
                            backup[i][k] += backup[row][k];
                        }
                        else if(operation == 2){
                            backup[i][k]  = max(backup[i][k],backup[row][k]);
                        }
                        else if(operation == 3){
                            backup[i][k]  = min(backup[i][k],backup[row][k]);
                        }
                    }
                count[i] = 0;
                }
            }
        }
    }
    free(count);
    
    if(operation==1){/*For the average operation. It divides the feature by N*/
        for(i=0;i<row_count;i++){
            if(feature_numbers[i] == 1);
            else if(count_backup[i] != 0 ){
                for(k=0; k<row_size; k++){
                    if(k== group_column) continue;
                    backup[i][k] /= feature_numbers[i];
                }
            }
        }
    }
    
    for(i=row_count-1;i>0;i--){
        if(is_in(count_backup,row_count,i)){
            for(j=i;j<row_count;j++){
               backup[j] = backup[j+1];
            }
        }
        
    }    
    *group_count = row_count - changings(count_backup,row_count);
    
    return backup;
}

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix
    double **kernel: kernel matrix
    int kernel_height: vertical size of the kernel matrix
    int kernel_width: horizontal size of the kernel matrix

OUTPUT:
    double **convoluted_matrix: Created convoluted matrix

METHOD:
    This function applies convolution over data matrix using kernel matrix and returns created matrix.

*/
double **convolution(double **matrix, int row_count, int row_size, double **kernel, int kernel_height, int kernel_width) {
    int i,j,x,y,conv_height,conv_width;
    double **convolution,sum = 0;
    
    conv_height = row_count-kernel_height+1;
    conv_width  = row_size-kernel_width+1;
    
    convolution = malloc(conv_height*sizeof(double));
    
    for(i=0;i<conv_height;i++){
        convolution[i] = malloc(conv_width * sizeof(double));
    }
    

    for(i=0;i<conv_height;i++){
        for(j=0;j<conv_width;j++){
            for(x=0;x<kernel_height;x++){
                for(y=0;y<kernel_width;y++){
                    sum += kernel[x][y] * matrix[i+x][j+y];
                }
            }
            convolution[i][j] = sum;
            sum = 0;
        }
    }

    
    return convolution; 
}
