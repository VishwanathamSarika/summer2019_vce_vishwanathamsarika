#include<stdio.h>
#include<string.h>

// function for creating and writing in file
void create_marks_csv(char *filename){
	FILE *fp;
	int i, count, id, micro, dcn, ds, rd;

	printf("\n Creating %s.csv file", filename);
	filename = strcat(filename, ".csv");

	fp = fopen(filename, "w+");

	fprintf(fp, "Student Id, Microprocessor, RDMBMS, DCN, DS");
	printf("How many student's marks do you want to save?");
	scanf("%d", &count);

	for (i = 1; i <= count; i++){
		printf("Enter student id");
		scanf("%d", &id);
		printf("Enter Microprocessor marks");
		scanf("%d", &micro);
		printf("Enter RDBMS marks");
		scanf("%d", &rd);
		printf("Enter DCN marks");
		scanf("%d", &dcn);
		printf("Enter DS marks");
		scanf("%d", &ds);

		fprintf(fp, "\n%d,%d,%d,%d,%d", id, micro, rd, dcn, ds);
	}
	fclose(fp);
	fp = fopen(filename, "r");
	printf("\nFile contents are :\n");
	char line[1024];
	while (fgets(line, 1024, fp))
	{
		printf("%s\n",line);
	}
	fclose(fp);
	return;
}

void test_sample(){
	char str[100];
	printf("\n Enter the filename :");
	gets_s(str);
	create_marks_csv(str);
}