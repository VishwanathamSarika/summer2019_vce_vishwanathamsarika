#include<stdio.h>
#include<stdlib.h>

void convertString(char arr[], int size){
	int i,count=1;
	for (i = 0; i < size-1; i++){
		if (arr[i] != arr[i + 1]){
			printf("%c%d", arr[i], count);
			count = 1;
		}
		else{
			count++;
		}
	}
	if (arr[i - 1] == arr[i]){
		count++;
	}
	else{
		count = 1;
	}
	printf("%c%d", arr[i], count);
}

void test_convert(){
	char arr[8] = {'a','a','b','b','b','c','c','d'};
	convertString(arr, 8);
}