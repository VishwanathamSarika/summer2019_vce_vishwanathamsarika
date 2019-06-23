#include<stdio.h>
#include<stdlib.h>


void printReverseNumber(int arr[], int index, int k){
	int i;
	if (index == k){
		long number = 0;
		char *reverse = (char *)malloc(k*sizeof(char));
		for (i = 0; i < k; i++){
			switch (arr[i])
			{
			case 1:reverse[i] = '1';
				break;
			case 2:reverse[i] = '2';
				break;
			case 3:reverse[i] = 'E';
				break;
			case 4:reverse[i] = 'h';
				break;
			case 5:reverse[i] = '5';
				break;
			case 6:reverse[i] = '9';
				break;
			case 7:reverse[i] = 'L';
				break;
			case 8:reverse[i] = '8';
				break;
			case 9:reverse[i] = '6';
				break;
			case 0:reverse[i] = '0';
				break;
			}
		}
		reverse[i] = '\0';
		printf("\n%s",reverse);
		return;
	}
	else{
		for (i = 0; i < 10; i++){
			arr[index] = i;
			printReverseNumber(arr, index + 1, k);
		}
	}
}

void printNumber(int arr[],int index,int k){
	int i;
	if (index == k){
		long number=0;
		for (i = 0; i < k; i++){
			number = number * 10 + arr[i];
		}
		printf("%d\n", number);
		return;
	}
	else{
		for (i = 0; i < 10; i++){
			arr[index] = i;
			printNumber(arr, index + 1, k);
		}
	}
}

void NoOfdigits(int arr[], int index, int k){
	printNumber(arr, 0, k-1);
	printf("\nReverse numbers are:\n");
	printReverseNumber(arr, 0, k - 1);
}
void test_printKdigitnos(){
	int *arr = (int *)calloc(6,sizeof(int));
	NoOfdigits(arr, 0, 4);
}