#include<stdio.h>
#include<stdlib.h>

void Permuations_WithoutRep(int arr[], int index, int k, int numbers[], int size,int flags[]){
	int i,num;
	if (index == k){
		int number = 0;
		for (i = 0; i < index; i++){
			number = number * 10 + arr[i];
		}
		printf("%d\n", number);
	}
	else if (index > k){
		return;
	}
	int visited[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (i = 0; i < size; i++){
		num = numbers[i];
		if (visited[num] == 0 && flags[i]==0){
			visited[num]= flags[i] = 1;
			arr[index] = num;
			Permuations_WithoutRep(arr, index + 1, k, numbers, size, flags);
			flags[i] = 0;
		}
		
	}
}

void test_Permuations_WithoutRep(){
	int *arr = (int *)calloc(5, sizeof(int));
	int numbers[5] = { 1, 3, 4, 5, 3 };
	int *flags = (int *)calloc(5, sizeof(int));
	Permuations_WithoutRep(arr, 0, 5, numbers, 5,flags);
}