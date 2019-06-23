#include<stdio.h>
#include<stdlib.h>

void print_spiral(){
	int m, n, i, j;
	printf("\nEnter the size of matrix: ");
	scanf_s("%d %d", &m, &n);
	int **original = (int **)malloc(m*sizeof(int *));
	for (i = 0; i < m; i++){
		original[i] = (int *)malloc(n*sizeof(int));
	}
	printf("\nEnter the data for the matrix: ");
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			printf("\nEnter value of [%d][%d]: ", i, j);
			scanf_s("%d", &original[i][j]);
		}
	}
	int row_start=0, row_end=m, col_start=0, col_end=n;
	while (row_start < row_end && col_start < col_end){
		for (i = col_start; i < col_end; i++){
			printf("%d ", original[row_start][i]);
		}
		row_start++;
		for (i = row_start; i < row_end; i++){
			printf("%d ", original[i][col_end-1]);
		}
		col_end--;
		if (col_start < col_end){
			for (i = col_end-1; i >= col_start; i--){
				printf("%d ", original[row_end-1][i]);
			}
		}
		row_end--;
		if (row_start < row_end){
			for (i = row_end-1; i >= row_start; i--){
				printf("%d ", original[i][col_start]);
			}
		}
		col_start++;
	}
}

/*void main(){
	print_spiral();
	scanf_s("%s");
}*/