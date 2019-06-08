#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define row 10
#define col 10

struct cell{
	char formula[50];
};

struct cell ** command_setL2(char *value, struct cell **data){
	int i = 0, j=0;
	int val = 0;
	char attribute[50];
	int flag = 0;
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
	strcpy(data[i][j].formula,attribute);
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
int command_getL2(char *value, struct cell **data,int index=0){
	int i = 0, j = 0,x,y,flag=0;
	int val = 0;
	char *attribute = (char *)calloc(50, sizeof(char));
	y = int(value[index]) - int('a');
	if (isdigit(value[index+2])){
		x = value[index+1] - '0';
		x = (x * 10) + value[index+2] - '0';
		x--;
	}
	else{
		x = value[index+1] - 1 - '0';
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
		int operand1 = 0;
		int operand2 = 0;
		char op;
		i = 0;
		if (isdigit(attribute[i])){
			while (isdigit(attribute[i])){
				operand1 = operand1*10 + attribute[i] - '0';
				i++;
				if (attribute[i] == '\0'){
					return operand1;
				}
			}
		}
		else{
			operand1 = command_getL2(attribute, data);
			while (isalpha(attribute[i]) || isdigit(attribute[i])){
				i++;
			}
		}
		if (attribute[i] != '\0'){
			op = attribute[i];
			i++;
			if (isdigit(attribute[i])){
				while (isdigit(attribute[i])){
					operand2 = operand2 * 10 + attribute[i] - '0';
					i++;
				}
			}
			else{
				operand2 = command_getL2(attribute, data,i);
			}
			return perform_op(operand1, operand2, op);
		}
		else{
			return operand1;
		}
	}
}

void command_printL2(struct cell **data){
	int i, j;
	char *index = (char *)malloc(4*sizeof(char));
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
			printf("%d\t", command_getL2(index,data));
		}
		printf("\n");
	}
}

struct cell ** initiaizeCells(struct cell **data){
	int i, j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			strcpy(data[i][j].formula, "0");
		}
	}
	return data;
}

void command_exportL2(char *filename, struct cell **data){
	FILE *fp,*fp1;
	char *p;
	char *meta = "meta_";
	p = strstr(filename, ".csv");
	if (p == '\0'){
		filename = strcat(filename, ".csv");
	}
	char *metafile = (char *)malloc(strlen(filename) + strlen(meta)+1);
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
			fprintf(fp,"%d,", command_getL2(index, data));
			fprintf(fp1, "%s,", data[i][j].formula);
		}
		fprintf(fp,"\n");
		fprintf(fp1,"\n");
	}
	fclose(fp);
	fclose(fp1);
}

struct cell ** command_importL2(char *filename,struct cell** data){
	int i, j;
	char frmla[50];
	
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
	fp1 = fopen(metafile, "r");
	char *index = (char *)malloc(4 * sizeof(char));
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			fscanf(fp1, "%c");
			fscanf(fp1, "%s", frmla);
			//printf("%s\t", frmla);
			strcpy(data[i][j].formula,frmla);
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
			data = command_setL2(value,data);
		}
		else if (strcmp(command, "get") == 0){
			scanf("%s", value);
			printf("%d",command_getL2(value, data));
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
			strcpy(filename, value);
			data=command_importL2(value,data);
		}
		else if (strcmp(command, "save") == 0){
			if (filename[0] != '\0'){
				command_exportL2(filename, data);
			}
		}
		else{
			printf("\nInvalid Command\n");
		}
		printf("\n");
	}
}
void test_excel_L2(){
	getCommandsL2();
}