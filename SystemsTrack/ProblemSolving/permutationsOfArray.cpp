#include<stdio.h>
#include<stdlib.h>

void printPermuations(int arr[], int index, int k,int numbers[],int size,int visited[]){
	int i,num;
	if (index == k ){
		int number = 0;
		for (i = 0; i < index; i++){
			number = number * 10 + arr[i];
		}
		printf("%d\n", number);
	}
	else if (index > k){
		return;
	}
	for (i = 0; i < size; i++){
		num = numbers[i];
		if (visited[num] == 0){
			visited[num] = 1;
			arr[index] = num;
			printPermuations(arr, index + 1, k, numbers, size, visited);
			visited[num] = 0;
		}
	}
}

void test_printPermuations(){
	int *arr = (int *)calloc(4, sizeof(int));
	int numbers[4] = { 1, 3, 4, 5};
	int visited[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	printPermuations(arr, 0, 4,numbers,4,visited);
}