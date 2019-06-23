#include<stdio.h>
#include<stdlib.h>

/*EXCEL LEVEL 5- Extends ExcelL2 with expression evaluation and Loop Detection*/

#include "ExpressionEvaluation.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define row 10
#define col 10

int parseFormula(char *formula, struct cell **data);

struct cell{
	char *formula;
};

int command_getL2(struct cell **data,int x,int y){
	int i = 0, j = 0, flag = 0;
	int val = 0;
	char *attribute = (char *)calloc(50, sizeof(char));
	attribute = data[x][y].formula;

	i = 0;
	while (attribute[i] != '\0'){
		if (isdigit(attribute[i])){
			val = val * 10 + attribute[i] - '0';
		}
		else{
			flag = 1;
			break;
		}
		i++;
	}
	if (flag == 0){
		return val;
	}
	else{
		return parseFormula(attribute, data);
	}
}

int parseFormula(char *formula,struct cell **data){
	int i,k,row_num,col_num;
	char *infixNotation=(char *)malloc(50*sizeof(char));
	int result,length,r,j;
	k = -1;
	for (i = 0; formula[i] != '\0'; i++){
		if (isalpha(formula[i])){
			col_num = int(formula[i]) - int('a');
			i++;
			row_num = 0;
			while (isdigit(formula[i])){
				row_num = row_num * 10 + formula[i] - '0';
				i++;
			}
			row_num--;
			i--;
			if (row_num >= 10){
				return -1;
			}
			else{
				result = command_getL2(data, row_num, col_num);
				length = 0;
				r = result;
				while (r > 0){
					r = r / 10;
					length++;
				}
				j=k+length;
				while (result > 0){
					infixNotation[k+length] = result % 10 + '0';
					result = result / 10;
					length--;
				}
				k = j;
			}
		}
		else{
			infixNotation[++k] = formula[i];
		}
	}
	infixNotation[++k] = '\0';
	//printf("\nInfix Notation is %s\n", infixNotation);
	return infixToPostfix(infixNotation);
}

char * command_getFormula(char *value, struct cell **data, int index = 0){
	int i = 0, j = 0, x, y, flag = 0;
	int val = 0;
	char *attribute = (char *)calloc(50, sizeof(char));
	y = int(value[index]) - int('a');
	if (isdigit(value[index + 2])){
		x = value[index + 1] - '0';
		x = (x * 10) + value[index + 2] - '0';
		x--;
	}
	else{
		x = value[index + 1] - 1 - '0';
	}
	attribute = data[x][y].formula;
	return attribute;
}

int loop_detection(char *value,struct cell **data,char **arr,int index){
	char *cell_no = (char *)calloc(50, sizeof(char));
	char *formula = (char *)calloc(50, sizeof(char));
	char *sub_formula = (char *)calloc(50, sizeof(char));
	int i=0,j=0;
	while (isalpha(value[i])){
		cell_no[i] = value[i];
		i++;
	}
	if (i != 0){
		while (isdigit(value[i])){
			cell_no[i] = value[i];
			i++;
			cell_no[i] = '\0';
		}

		j = 0;
		while (arr[j][0] != '\0'){
			if (strcmp(arr[j], cell_no) == 0){
				return 1;
			}
			j++;
		}
		arr[j] = cell_no;
	}
	
	for (j = 0; value[i] != '\0'; j++){
		formula[j] = value[i];
		i++;
	}
	formula[j] = '\0';

	
	
	for (i = 0; formula[i] != '\0'; i++){
		if (isalpha(formula[i])){
			sub_formula = command_getFormula(formula, data,i);
			if (loop_detection(sub_formula, data, arr,index) == 1){
				return 1;
			}
		}
	}
	return -1;
}

struct cell ** command_setL2(char *value, struct cell **data){
	int i = 0, j = 0;
	int val = 0;
	char *attribute = (char *)calloc(50, sizeof(char));
	char **arr = (char **)calloc(10, sizeof(char *));
	for (i = 0; i < 10; i++){
		arr[i] = (char *)calloc(10, sizeof(char));
	}
	int flag = 0;

	if (loop_detection(value, data, arr, 0) == 1){
		printf("\nLoop Detected");
		return data;
	}
	for (i = 0; value[i] != '\0'; i++){
		if (value[i] == '='){
			flag = 1;
			continue;
		}
		if (flag == 1){
			attribute[j] = value[i];
			j++;
		}
	}
	attribute[j] = '\0';
	j = int(value[0]) - int('a');
	if (isdigit(value[2])){
		i = value[1] - '0';
		i = (i * 10) + value[2] - '0';
		i--;
	}
	else{
		i = value[1] - 1 - '0';
	}
	data[i][j].formula = attribute;
	return data;
}

int perform_op(int x, int y, char op){
	switch (op){
	case '+':return x + y;
	case '-':return x - y;
	case '*':return x*y;
	case '/':return x / y;
	default:return 0;
	}
}
int command_getL2(char *value, struct cell **data, int index = 0){
	int i = 0, j = 0, x, y, flag = 0;
	int val = 0;
	char *attribute = (char *)calloc(50, sizeof(char));
	y = int(value[index]) - int('a');
	if (isdigit(value[index + 2])){
		x = value[index + 1] - '0';
		x = (x * 10) + value[index + 2] - '0';
		x--;
	}
	else{
		x = value[index + 1] - 1 - '0';
	}
	attribute = data[x][y].formula;

	i = 0;
	while (attribute[i] != '\0'){
		if (isdigit(attribute[i])){
			val = val * 10 + attribute[i] - '0';
		}
		else{
			flag = 1;
			break;
		}
		i++;
	}
	if (flag == 0){
		return val;
	}
	else{
		return parseFormula(attribute, data);
	}
}

void command_printL2(struct cell **data){
	int i, j;
	char *index = (char *)malloc(4 * sizeof(char));
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			index[0] = j + 'a';
			if (i + 1>9){
				index[2] = (i + 1) % 10 + '0';
				index[1] = (i + 1) / 10 + '0';
				index[3] = '\0';
			}
			else{
				index[1] = i + 1 + '0';
				index[2] = '\0';
			}
			printf("%d\t", command_getL2(index, data));
		}
		printf("\n");
	}
}

struct cell ** initiaizeCells(struct cell **data){
	int i, j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			data[i][j].formula = "0";
		}
	}
	return data;
}

void command_exportL2(char *filename, struct cell **data){
	FILE *fp, *fp1;
	char *p;
	char *meta = "meta_";
	p = strstr(filename, ".csv");
	if (p == '\0'){
		filename = strcat(filename, ".csv");
	}
	char *metafile = (char *)malloc(strlen(filename) + strlen(meta) + 1);
	strcpy(metafile, meta);
	strcat(metafile, filename);
	fp = fopen(filename, "w");
	fp1 = fopen(metafile, "w");
	int i, j;
	char *index = (char *)malloc(4 * sizeof(char));
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			index[0] = j + 'a';
			if (i + 1>9){
				index[2] = (i + 1) % 10 + '0';
				index[1] = (i + 1) / 10 + '0';
				index[3] = '\0';
			}
			else{
				index[1] = i + 1 + '0';
				index[2] = '\0';
			}
			fprintf(fp, "%d,", command_getL2(index, data));
			fprintf(fp1, "%s,", data[i][j].formula);
		}
		fprintf(fp, "\n");
		fprintf(fp1, "\n");
	}
	fclose(fp);
	fclose(fp1);
}

struct cell ** command_importL2(char *filename){
	int i, j;
	struct cell **data = (struct cell **)malloc(row * sizeof(struct cell *));
	for (i = 0; i < 10; i++){
		data[i] = (struct cell *)malloc(col * sizeof(struct cell));
	}
	FILE *fp,*fp1;
	char *p;
	char *meta = "meta_";
	p = strstr(filename, ".csv");
	if (p == '\0'){
		filename = strcat(filename, ".csv");
	}
	char *metafile = (char *)malloc(strlen(filename) + strlen(meta) + 1);
	strcpy(metafile, meta);
	strcat(metafile, filename);
	fp1 = fopen(metafile, "r");
	char *index = (char *)malloc(4 * sizeof(char));
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			fscanf(fp1, "%s", data[i][j].formula);
			fscanf(fp1, "%c");
		}
	}
	fclose(fp1);
	return data;
}

void getCommandsL2(){
	char *command = (char *)calloc(10, sizeof(char));
	char *value = (char *)calloc(50, sizeof(char));
	char *filename = (char *)calloc(50, sizeof(char));
	int i;
	struct cell **data = (struct cell **)malloc(row * sizeof(struct cell *));
	for (i = 0; i < 10; i++){
		data[i] = (struct cell *)malloc(col * sizeof(struct cell));
	}
	data = initiaizeCells(data);
	while (1){
		printf(">");
		scanf("%s", command);
		command = _strlwr(command);
		if (strcmp(command, "set") == 0){
			scanf("%s", value);
			data = command_setL2(value, data);
		}
		else if (strcmp(command, "get") == 0){
			scanf("%s", value);
			printf("%d", command_getL2(value, data));
		}
		else if (strcmp(command, "print") == 0){
			command_printL2(data);
		}
		else if (strcmp(command, "export") == 0){
			scanf("%s", filename);
			command_exportL2(filename, data);

		}
		else if (strcmp(command, "import") == 0){
			scanf("%s", value);
			command_importL2(value);
		}
		else if (strcmp(command, "exit") == 0){
			break;
		}
		else{
			printf("\nInvalid Command\n");
		}
		printf("\n");
	}
}
void test_ExcelL5(){
	getCommandsL2();
}