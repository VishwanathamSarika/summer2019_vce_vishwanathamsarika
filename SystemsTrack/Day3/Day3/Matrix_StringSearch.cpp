#include<stdio.h>
#include<stdlib.h>

int isValidPosition(int m, int n, int i, int j){
	if (i >= m || i<0 || j>=n || j < 0){
		return -1;
	}
	return 1;
}
int bottom(char **matrix,int m,int n,int i,int j,char *string,int index){
	if (string[index] == '\0'){
		printf("\nStart : (%d,%d)",(i-index),j);
		printf("\nEnd: (%d,%d)", i - 1, j);
		return 1;
	}
	if (isValidPosition(m, n, i, j)==1){
		if (matrix[i][j] == string[index]){
			return bottom(matrix, m, n, i + 1, j, string, index + 1);
		}
		else return -1;
	}
	else return -1;
}

int top(char **matrix, int m, int n, int i, int j, char *string, int index){
	if (string[index] == '\0'){
		printf("\nStart : (%d,%d)", (i + index), j);
		printf("\nEnd: (%d,%d)", i + 1, j);
		return 1;
	}
	if (isValidPosition(m, n, i, j) == 1){
		if (matrix[i][j] == string[index]){
			return top(matrix, m, n, i-1 , j, string, index + 1);
		}
		else return -1;
	}
	else return -1;
}

int right(char **matrix, int m, int n, int i, int j, char *string, int index){
	if (string[index] == '\0'){
		printf("\nStart : (%d,%d)", i, (j-index));
		printf("\nEnd: (%d,%d)", i , j-1);
		return 1;
	}
	if (isValidPosition(m, n, i, j) == 1){
		if (matrix[i][j] == string[index]){
			return right(matrix, m, n, i , j+1, string, index + 1);
		}
		else return -1;
	}
	else return -1;
}

int left(char **matrix, int m, int n, int i, int j, char *string, int index){
	if (string[index] == '\0'){
		printf("\nStart : (%d,%d)", i, (j + index));
		printf("\nEnd: (%d,%d)", i, j + 1);
		return 1;
	}
	if (isValidPosition(m, n, i, j) == 1){
		if (matrix[i][j] == string[index]){
			return left(matrix, m, n, i, j - 1, string, index + 1);
		}
		else return -1;
	}
	else return -1;
}

int bottom_left(char **matrix, int m, int n, int i, int j, char *string, int index){
	if (string[index] == '\0'){
		printf("\nStart : (%d,%d)", (i-index), (j + index));
		printf("\nEnd: (%d,%d)", (i-1), j + 1);
		return 1;
	}
	if (isValidPosition(m, n, i, j) == 1){
		if (matrix[i][j] == string[index]){
			return bottom_left(matrix, m, n, i+1, j - 1, string, index + 1);
		}
		else return -1;
	}
	else return -1;
}

int top_right(char **matrix, int m, int n, int i, int j, char *string, int index){
	if (string[index] == '\0'){
		printf("\nStart : (%d,%d)", (i + index), (j - index));
		printf("\nEnd: (%d,%d)", (i + 1), j - 1);
		return 1;
	}
	if (isValidPosition(m, n, i, j) == 1){
		if (matrix[i][j] == string[index]){
			return top_right(matrix, m, n, i - 1, j + 1, string, index + 1);
		}
		else return -1;
	}
	else return -1;
}

int bottom_right(char **matrix, int m, int n, int i, int j, char *string, int index){
	if (string[index] == '\0'){
		printf("\nStart : (%d,%d)", (i-index), (j - index));
		printf("\nEnd: (%d,%d)", i-1, j-1);
		return 1;
	}
	if (isValidPosition(m, n, i, j) == 1){
		if (matrix[i][j] == string[index]){
			return bottom_right(matrix, m, n, i + 1, j + 1, string, index + 1);
		}
		else return -1;
	}
	else return -1;
}

int top_left(char **matrix, int m, int n, int i, int j, char *string, int index){
	if (string[index] == '\0'){
		printf("\nStart : (%d,%d)", (i + index), (j + index));
		printf("\nEnd: (%d,%d)", i + 1, j + 1);
		return 1;
	}
	if (isValidPosition(m, n, i, j) == 1){
		if (matrix[i][j] == string[index]){
			return top_left(matrix, m, n, i - 1, j - 1, string, index + 1);
		}
		else return -1;
	}
	else return -1;
}


void stringsearch(char **matrix, int m, int n, char *string){
	int i, j;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			if (matrix[i][j] == string[0]){
				if (bottom(matrix, m, n, i + 1, j, string, 1) == 1){
					printf("\nFound Bottom\n");
				}
				if (top(matrix, m, n, i - 1, j, string, 1) == 1){
					printf("\nFound Top\n");
				}
				if (right(matrix, m, n, i , j+1, string, 1) == 1){
					printf("\nFound Right\n");
				}
				if (left(matrix, m, n, i, j - 1, string, 1) == 1){
					printf("\nFound Left\n");
				}
				if (bottom_left(matrix, m, n, i + 1, j - 1, string, 1) == 1){
					printf("\nFound Bottom Left\n");
				}
				if (top_right(matrix, m, n, i - 1, j + 1, string, 1) == 1){
					printf("\nFound Top Right\n");
				}
				if (bottom_right(matrix, m, n, i + 1, j + 1, string, 1) == 1){
					printf("\nFound Bottom Right\n");
				}
				if (top_left(matrix, m, n, i - 1, j - 1, string, 1) == 1){
					printf("\nFound Top Left\n");
				}
			}
		}
	}
}

void test_stringsearch(){
	int m=3, n=3,i,j;
	char **matrix = (char **)calloc(m,sizeof(char*));
	for (i = 0; i < m; i++){
		matrix[i] = (char *)calloc(n,sizeof(char));
	}
	for (i = 0; i < 3; i++){
		matrix[i] = "abc";
	}
	printf("\nMatrix values are :\n");
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			printf("%c ", matrix[i][j]);
		}
		printf("\n");
	}
	char *s = (char *)malloc(10 * sizeof(char));
	s = "ba";
	printf("\nString is '%s'\n", s);
	stringsearch(matrix, m, n, s);
	scanf_s("%s");
}