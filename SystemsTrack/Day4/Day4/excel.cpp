#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define row 10
#define col 10


int ** command_set(char *value,int **data){
	int i=0, j;
	int val = 0;
	char* p;
	p = strstr(value, "=");
	i++;
	while (p[i] != '\0'){
		if (isdigit(p[i])){
			val = val * 10 + p[i]-'0';
		}
		i++;
	}
	j = int(value[0]) - int('a');
	i = value[1]-1-'0';
	data[i][j] = val;
	//printf("%d", data[i][j]);
	return data;
}

void command_get(char *value, int **data){
	int i = 0, j;
	j = int(value[0]) - int('a');
	i = value[1]-1 - '0';
	printf("\n%d", data[i][j]);
	return ;
}

void command_print(int **data){
	int i, j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			printf("%d\t", data[i][j]);
		}
		printf("\n");
	}
}

void command_export(char *filename, int **data){
	FILE *fp;
	char* p;
	p = strstr(filename, ".csv");
	if (p == '\0'){
		filename = strcat(filename, ".csv");
	}
	fp = fopen(filename, "w");
	int i, j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			fprintf(fp,"%d,", data[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

int ** command_import(char *filename){
	FILE *fp;
	char* p;
	int i, j;
	p = strstr(filename, ".csv");
	int **data = (int **)calloc(row, sizeof(int*));
	for (i = 0; i < 10; i++){
		data[i] = (int *)calloc(col, sizeof(int));
	}
	if (p == '\0'){
		filename = strcat(filename, ".csv");
	}
	fp = fopen(filename, "r");
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			fscanf(fp, "%d", &data[i][j]);
			fscanf(fp, "%c");
		}
	}
	fclose(fp);
	return data;
}

void getCommands(){
	char *command=(char *)calloc(10,sizeof(char));
	char *value = (char *)calloc(50, sizeof(char));
	int i;
	int **data = (int **)calloc(row, sizeof(int*));
	for (i = 0; i < 10; i++){
		data[i] = (int *)calloc(col, sizeof(int));
	}
	while (1){
		printf(">");
		scanf("%s",command);
		//printf("\nthe command is %s", command);
		//printf("\nthe value is %s", value);
		command = _strlwr(command);
		if (strcmp(command, "set") == 0){
			scanf("%s", value);
			data=command_set(value, data);
		}
		else if (strcmp(command, "get") == 0){
			scanf("%s", value);
			command_get(value,data);
		}
		else if (strcmp(command, "print") == 0){
			command_print(data);
		}
		else if (strcmp(command, "export") == 0){
			scanf("%s", value);
			command_export(value,data);
			
		}
		else if (strcmp(command, "import") == 0){
			scanf("%s", value);
			data=command_import(value);
		}
		else{
			printf("\nInvalid Command\n");
		}
		printf("\n");
	}
}
void test_excel(){
	getCommands();
}