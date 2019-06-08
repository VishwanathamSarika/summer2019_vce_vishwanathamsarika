#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"StackUtils.h"

int is_register(char *operand){
	int len = strlen(operand);
	if (len == 2){ return 1; }
	return 0;
}

struct label_map{
	char label_name[10];
	int label_address;
};

struct symbol_rows{
	int lineNo;
	int opcode;
	int arr[4];
};


void update_symTable(struct symbol_rows *symbolTab,int *m,
	int line_no,int op_code,int val1,int val2,int val3,int val4){

	symbolTab[*m].lineNo = line_no;
	symbolTab[*m].opcode = op_code;
	symbolTab[*m].arr[0] = val1;
	symbolTab[*m].arr[1] = val2;
	symbolTab[*m].arr[2] = val3;
	symbolTab[*m].arr[3] = val4;

	*m = *m + 1;

	return;
}

void print_symbolTab(struct symbol_rows *symbolTab,int m){
	int i, j;
	for (i = 0; i < m; i++){
		printf("\n");
		printf("%d\t", symbolTab[i].lineNo);
		printf("%d\t", symbolTab[i].opcode);
		for (j = 0; j < 4; j++){
			if (symbolTab[i].arr[j] != -1){
				printf("%d\t", symbolTab[i].arr[j]);
			}
		}
	}
	return;
}

void read_file(char *filename){
	FILE *fp = fopen(filename, "r");
	FILE *fp1 = fopen("output1.txt", "w");

	char *command=(char *)calloc(50,sizeof(char));
	char *operand = (char *)calloc(50, sizeof(char));
	char *operand1 = (char *)calloc(50, sizeof(char));
	char *operand2 = (char *)calloc(50, sizeof(char));

	int var_values[26], var_address[26], registers[8];
	int index,memory_offset=0;
	int i,num;
	int line_no=1;

	struct Stack *my_stack = (struct Stack *)malloc(sizeof(struct Stack));

	struct symbol_rows *symbolTab=(struct symbol_rows *)malloc(50*sizeof(symbol_rows));
	int m=0;

	struct label_map labels[10];
	int no_of_labels=0;

	if (fp == NULL){
		printf("Error reading file");
		return;
	}
	if (fp1 == NULL){
		printf("Error reading output file");
		return;
	}

	while (!feof(fp)){
		fscanf(fp,"%s", command);
		printf("%s\n", command);
		command = _strlwr(command);

		if (strcmp(command, "mov") == 0){
			fscanf(fp, "%s", operand1);
			fscanf(fp, "%s", operand2);
			if (is_register(operand1) == 1){

				fprintf(fp1, "%02d ", 1);

				index = operand1[0] - 'A';
				fprintf(fp1, "%02d ", index);

				index = operand2[0] - 'A';
				fprintf(fp1, "%04d\n", var_address[index]);
				fflush(fp1);

				update_symTable(symbolTab, &m, line_no, 1, index, var_address[index], -1, -1);

			}
			else{
				fprintf(fp1, "%02d ", 2);

				index = operand1[0] - 'A';
				fprintf(fp1, "%04d ", var_address[index]);

				index = operand2[0] - 'A';
				fprintf(fp1, "%d\n", index);
				fflush(fp1);

				update_symTable(symbolTab, &m, line_no, 2, var_address[index], index, -1, -1);

			}
		}
		else if (strcmp(command, "add") == 0){

			fscanf(fp, "%s", operand);
			fscanf(fp, "%s", operand1);
			fscanf(fp, "%s", operand2);

			fprintf(fp1, "%02d ", 3);

			//For all 3 registers
			fprintf(fp1, "%02d ", operand[0]-'A');
			fprintf(fp1, "%02d ", operand1[0] - 'A');
			fprintf(fp1, "%02d\n", operand2[0] - 'A');
			fflush(fp1);

			update_symTable(symbolTab, &m, line_no, 3, operand[0] - 'A', operand1[0] - 'A', operand2[0] - 'A', -1);
		}
		else if (strcmp(command, "sub") == 0){
			fscanf(fp, "%s", operand);
			fscanf(fp, "%s", operand1);
			fscanf(fp, "%s", operand2);

			fprintf(fp1, "%02d ", 4);

			//For all 3 registers
			fprintf(fp1, "%02d ", operand[0] - 'A');
			fprintf(fp1, "%02d ", operand1[0] - 'A');
			fprintf(fp1, "%02d\n", operand2[0] - 'A');
			fflush(fp1);

			update_symTable(symbolTab, &m, line_no, 4, operand[0] - 'A', operand1[0] - 'A', operand2[0] - 'A', -1);

		}
		else if (strcmp(command, "mul") == 0){
			fscanf(fp, "%s", operand);
			fscanf(fp, "%s", operand1);
			fscanf(fp, "%s", operand2);

			fprintf(fp1, "%02d ", 5);

			//For all 3 registers
			fprintf(fp1, "%02d ", operand[0] - 'A');
			fprintf(fp1, "%02d ", operand1[0] - 'A');
			fprintf(fp1, "%02d\n", operand2[0] - 'A');
			fflush(fp1);

			update_symTable(symbolTab, &m, line_no, 5, operand[0] - 'A', operand1[0] - 'A', operand2[0] - 'A', -1);

		}
		else if (strcmp(command, "jump") == 0){
			fprintf(fp1, "%02d ", 6);
			fscanf(fp, "%s", operand);

			operand = _strlwr(operand);
			for (i = 0; i < no_of_labels; i++){
				if (strcmp(labels[i].label_name, operand) == 0){
					fprintf(fp1, "%04d\n", labels[i].label_address);
					fflush(fp1);
					break;
				}
			}

			update_symTable(symbolTab, &m, line_no, 6, labels[i].label_address,-1, -1, -1);

		}
		else if (strcmp(command, "if") == 0){
			//char expression[50];
			//fgets(expression, 50, fp);
			//processIF(expression);

			//push(my_stack, m);
			//push(my_stack, 3);

			fprintf(fp1, "%02d ", 7);

			fscanf(fp, "%s", operand);
			fscanf(fp, "%s", operand1);
			fscanf(fp, "%s", operand2);
			fscanf(fp, "%s");

			fprintf(fp1, "%02d ", operand[0] - 'A');

			operand1 = _strlwr(operand1);

			if (strcmp(operand1, "eq") == 0){
				fprintf(fp1, "%02d ", 8);

				update_symTable(symbolTab, &m, line_no, 7, operand[0] - 'A',operand2[0] - 'A', 8, -1);

			}
			else if (strcmp(operand1, "lt") == 0){
				fprintf(fp1, "%02d ", 9);

				update_symTable(symbolTab, &m, line_no, 7, operand[0] - 'A', operand2[0] - 'A', 9, -1);

			}
			else if (strcmp(operand1, "gt") == 0){
				fprintf(fp1, "%02d ", 10);

				update_symTable(symbolTab, &m, line_no, 7, operand[0] - 'A', operand2[0] - 'A', 10, -1);

			}
			else if (strcmp(operand1, "lteq") == 0){
				fprintf(fp1, "%02d ", 11);

				update_symTable(symbolTab, &m, line_no, 7, operand[0] - 'A', operand2[0] - 'A', 11, -1);

			}
			else if (strcmp(operand1, "gteq") == 0){
				fprintf(fp1, "%02d ", 12);

				update_symTable(symbolTab, &m, line_no, 7, operand[0] - 'A', operand2[0] - 'A', 12, -1);

			}
			
			fprintf(fp1, "%02d\n", operand2[0] - 'A');
			fflush(fp1);

		}
		else if (strcmp(command, "else") == 0){
			//push(my_stack, m);
			//push(my_stack, 1);

			update_symTable(symbolTab, &m, line_no, 6, -1,-1,-1, -1);
			fprintf(fp1, "\n");
			fflush(fp1);
		}
		else if (strcmp(command, "endif") == 0){
			fprintf(fp1, "\n");
			fflush(fp1);
		}
		else if (strcmp(command, "print") == 0){
			fprintf(fp1, "%02d ", 13);

			fscanf(fp, "%s", operand);
			if (strlen(operand) == 2){
				fprintf(fp1, "%02d\n", operand[0] - 'A');

				update_symTable(symbolTab, &m, line_no, 13, operand[0] - 'A',-1, -1, -1);
			}
			else{
				index = operand[0] - 'A';
				fprintf(fp1, "%04d\n",var_address[index]);

				update_symTable(symbolTab, &m, line_no, 13, var_address[index], -1, -1, -1);
			}
			fflush(fp1);
		}

		else if (strcmp(command, "read") == 0){
			fprintf(fp1, "%02d ", 14);
			fflush(fp1);
			fscanf(fp, "%s", operand);
			if (strlen(operand) == 2){
				fprintf(fp1, "%02d\n", operand[0] - 'A');
				
				update_symTable(symbolTab, &m, line_no, 14, operand[0] - 'A', -1, -1, -1);
			}
			else{
				index = operand[0] - 'A';
				fprintf(fp1, "%04d\n", var_address[index]);


				update_symTable(symbolTab, &m, line_no, 14, var_address[index], -1, -1, -1);
			}
			fflush(fp1);
		}
		else if (strcmp(command, "data") == 0){
			fscanf(fp, "%s", operand);
			index = operand[0] - 'A';
			var_address[index] = memory_offset;
			if (strlen(operand) == 1){
				memory_offset++;
			}
			else{
				num = 0;
				for (i = 2; operand[i] != ']'; i++){
					num = num * 10 + operand[i]-'0';
				}
				memory_offset = memory_offset + num;
			}
		}
		else if (strcmp(command,"const")==0){
			fscanf(fp, "%s", operand);
			fscanf(fp, "%s");// takes '='
			fscanf(fp, "%s", operand1);

			index = operand[0] - 'A';
			var_address[index] = memory_offset;
			memory_offset++;

			num = 0;
			for (i = 0; operand1[i] != '\0'; i++){
				num = num * 10 + operand1[i]-'0';
			}

			var_values[index] = num;
		}
		else{//for LABELS
			for (i = 0; command[i] != '\0'; i++){
				if (command[i] == ':'){
					command[i] = '\0';
					break;
				}
			}

			for (i = 0; i < no_of_labels; i++){
				if (strcmp(labels[i].label_name, command) == 0){
					break;
				}
			}
			if (i == no_of_labels){
				strcpy(labels[no_of_labels].label_name, command);
				labels[no_of_labels].label_address=line_no;
				no_of_labels++;
			}
		}

		line_no++;
	}

	print_symbolTab(symbolTab, m);
	
	printf("\nFile parsed");
	scanf_s("%s");

	fflush(fp1);
	fclose(fp);
	fclose(fp1);
	return;
}

void test_parsing(){
	read_file("input.txt");
	return;
}