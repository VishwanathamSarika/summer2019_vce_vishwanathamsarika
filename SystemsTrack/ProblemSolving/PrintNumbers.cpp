#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void print(int n,int i){
	int length = 0;
	int num = i;
	if (i == pow(double(10), double(n))){
		return;
	}
	else{
		printf("\n%d", num);
		print(n, num + 1);
	}
}

void test_printnumbers(){
	printf("Numbers are\n");
	print(2, 0);
}