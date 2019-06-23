#include<stdio.h>
#include<stdlib.h>

int Numberofways(int n,int k){
	if (n<=k){
		return 1;
	}
	else{
		int result = 0, i;
		for (i = 1; i <= k; i++){
			result = result + Numberofways(n - i, k);
		}
		return result;
	}
}

void test_staircase(){
	printf("No of ways possible is %d", Numberofways(7,2));
}