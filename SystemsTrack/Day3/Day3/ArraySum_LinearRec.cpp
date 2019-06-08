#include<stdio.h>
#include<stdlib.h>

long sum(int arr[], int index, int size){
	if (index == size){
		return 0;
	}
	else{
		return arr[index] + sum(arr, index + 1, size);
	}
}

void test_ArraySum_LRec(){
	int arr1[5] = { 1, 2, 3, 4, 5 };
	printf("\nSum is %d", sum(arr1, 0, 5));
}