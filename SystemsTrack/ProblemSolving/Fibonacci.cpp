#include<stdio.h>
#include<stdlib.h>

long fib(int n,int arr[]){
	long x, y;
	if (n == 0 || n == 1){
		return n;
	}
	else if (n < 0){
		return 0;
	}
	else{
		if (arr[n - 1] == 0){
			arr[n - 1] = fib(n - 1, arr);
		}
		if (arr[n - 2] == 0){
			arr[n - 2] = fib(n - 2, arr);
		}
		return arr[n-1]+arr[n-2];
	}
}

int ** matrix_mul(int **matrix1,int m1,int n1, int **matrix2,int m2,int n2){
	int **result = (int **)malloc(m1*sizeof(int *));
	int i,j,k,sum=0;
	for (i = 0; i < m1; i++){
		result[i] = (int *)malloc(n2*sizeof(int));
	}
	for (i = 0; i < m1; i++)
	{
		for (j = 0; j < n2; j++)
		{
			result[i][j] = 0;
			for (k = 0; k < m2; k++)
			{
				*(*(result + i) + j) += *(*(matrix1 + i) + k) * *(*(matrix2 + k) + j);
			}
		}
	}
	return result;
}

int ** power(int **matrix1, int m1, int n1, int n){
	if (n == 1){
		return matrix1;
	}
	else{
		int **result = power(matrix1, m1, n1, n - 1);
		return matrix_mul(matrix1, m1, n1, result, m1, n1);
	}
}

void display_matrix(int **matrix, int m, int n){
	int i, j;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			printf("\t%d", matrix[i][j]);
		}
		printf("\n");
	}
}

void matrix_fib(int n){
	int **A = (int **)malloc(2*sizeof(int *));
	int i, j, k, sum;
	for (i = 0; i < 2; i++){
		A[i] = (int *)calloc(2, sizeof(int));
	}
	A[0][0] = 0;
	A[0][1] = 1;
	A[1][0] = 1;
	A[1][1] = 1;
	printf("\nA\n");
	display_matrix(A, 2, 2);

	int **An = power(A, 2, 2, n);
	printf("\nAn\n");
	display_matrix(An, 2, 2);

	int **x0 = (int **)malloc(2 * sizeof(int *));
	for (i = 0; i < 2; i++){
		x0[i] = (int *)malloc(sizeof(int));
	}
	x0[0][0] = 0;
	x0[1][0] = 1;
	printf("\nx0\n");
	display_matrix(x0, 2, 1);

	int **xn = matrix_mul(An, 2, 2, x0, 2, 1);
	printf("\nxn\n");
	display_matrix(xn, 2, 1);
	printf("Fibonacci value of %d is %d", n, xn[0][0]);
}

void test_matrixfib(){
	matrix_fib(6);
}

void test_fib()
{
	int *arr = (int *)calloc(7, sizeof(int));
	printf("Fibonacci value of 7 is %d", fib(7,arr));
}