#include<stdio.h>
#include<stdlib.h>

void print_array(int arr[], int size){
	int i;
	printf("\n");
	for (i = 0; i < size; i++){
		printf("%d ", arr[i]);
	}
}

void ByCountOf1(int arr[],int size){
	int i,count=0;
	for (i = 0; i < size; i++){
		if (arr[i] == 1) count++;
	}
	arr[size] = { 0 };
	for (i = size-1; i >=0; i--){
		if (count > 0){
			arr[i] = 1;
			count--;
		}
		else{
			arr[i] = 0;
		}
	}
	print_array(arr, size);
}

int comparator(const void *x, const void *y){
	if (x <= y) return 0;
	else return 1;
}

void BySort(int arr[], int size){
	qsort((void *)arr, size, sizeof(int), comparator);
	print_array(arr, size);
}

void BySwap(int arr[], int size){
	int i, j;
	for (i = 0, j = size - 1; i < j; i++, j--){
		if (arr[i] > arr[j]){
			arr[i] = 0;
			arr[j] = 1;
		}
	}
	print_array(arr,size);
}

void test_01sort(){
	int n,i;
	printf("\nEnter the size of array: ");
	scanf_s("%d", &n);
	int *arr = (int *)malloc(n*sizeof(int));
	printf("Enter array elements: ");
	for (i = 0; i < n; i++){
		scanf_s("%d", &arr[i]);
	}
	ByCountOf1(arr, n);
	BySort(arr, n);
	BySwap(arr, n);
}