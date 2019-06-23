#include<stdio.h>
#include<stdlib.h>

#define range 1000000

void file_partition(char *input_file){
	FILE *fp,*fp1,*fp2;
	char *smallFile = (char *)malloc(50 * sizeof(char));
	int i,num,j,k;
	char *occur;
	fp = fopen(input_file,"r");
	for (i = 0; i < 10; i++){
		sprintf(smallFile, "%d_%s",i,"partition1.txt");
		fp1 = fopen(smallFile,"w");
		while (!feof(fp)){
			fscanf(fp,"%d\n", &num);
			if (num / range == i){
				fprintf(fp1,"%d\n", num%range);
			}
		}
		fclose(fp1);
		fseek(fp, 0, SEEK_SET);
	}
	fclose(fp);

	fp2 = fopen("output_file.txt", "w");
	for (i = 0; i < 10; i++){
		sprintf(smallFile, "%d_%s", i, "partition1.txt");
		fp1 = fopen(smallFile, "r");
		occur = (char *)calloc(125000, sizeof(char));
		while (!feof(fp1)){
			fscanf(fp1,"%d\n", &num);
			occur[num / 8] = occur[num / 8] | 1 << (num % 8);
		}
		for (j = 0; j < 125000; j++){
			for (k = 0; k < 8; k++){
				if (occur[j] & 1 << k){
					num = i*range + j * 8 + k;
					printf("%d\n",num);
					fprintf(fp2,"%d\n",num);
				}
			}
		}
		free(occur);
	}
	fclose(fp2);
}

void test_sort(){
	char *input_file = (char *)malloc(50 * sizeof(char));
	file_partition("input.txt");
}