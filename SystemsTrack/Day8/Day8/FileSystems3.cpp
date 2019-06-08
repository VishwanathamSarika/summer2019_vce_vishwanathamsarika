#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "BlockIO.h"

#define blocksize (16*1024)

long int get_FileSize(char *filename){
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("File Not Found!\n");
		return -1;
	}
	fseek(fp, 0L, SEEK_END);
	long int res = ftell(fp);
	fclose(fp);
	return res;
}

void retrieve_file(struct meta_data *meta,char *src,char *dest){
	FILE *fp = fopen("db.hdd", "wb+");
	FILE *fp1 = fopen(dest, "wb+");

	char buff[blocksize];
	int i, j;
	struct file *fileP = meta->bitVector;
	for (i = 0; i < meta->total_no_of_files; i++){
		if (strcmp(fileP->filename,src)==0){

		}
		fileP = fileP + 1;
	}
}

void store_file(struct meta_data *meta,char *filename){
	FILE *fp = fopen("db.hdd", "wb+");
	FILE *fp1 = fopen(filename, "rb+");
	char buff[blocksize];
	struct file newFile;
	
	int i,j,flag=0;
	for (i = 0; i < 6400; i++){
		if (meta->blocks[i] == true){
			newFile.start_block = i;
			meta->blocks[i] = false;
			break;
		}
	}
	newFile.file_size = get_FileSize(filename);
	newFile.no_of_blocks = ceil(double(newFile.file_size) / blocksize);
	int noOfBlocks = newFile.no_of_blocks;
	int arr[10] = { 0 };

	if (noOfBlocks != newFile.file_size / blocksize){
		noOfBlocks--;
		flag = 1;
	}
	j = -1;
	for (i = 0; i < 6400; i++){
		if (meta->blocks[i] == true){
			printf("\nBlock number is %d", i);
			arr[++j] = i;
			fread(buff, blocksize, 1, fp1);
			write_block(i, buff);
			meta->blocks[i] = false;
			noOfBlocks--;
		}
		if (noOfBlocks == 0){
			break;
		}
	}
	if (flag == 1){
		printf("\nBlock number is %d", i);
		int offset = newFile.file_size%blocksize;
		for (i = 0; i < 6400; i++){
			if (meta->blocks[i] == true){
				arr[++j] = i;
				fread(buff, blocksize, 1, fp1);
				write_block(i, buff);
				meta->blocks[i] = false;
				break;
			}
		}
	}

	write_block(newFile.start_block, arr);

	struct file *fileP = meta->bitVector;
	for (i = 0; i < meta->total_no_of_files; i++){
		fileP = fileP + 1;
	}
	*fileP = newFile;
	meta->total_no_of_files = meta->total_no_of_files + 1;

	memcpy(buff, meta, sizeof(meta_data));
	write_block(0, buff);

	fclose(fp);
	fclose(fp1);
}

void test_FileSys3(){
	char *command = (char *)calloc(50, sizeof(char));
	char *filename = (char *)calloc(50, sizeof(char));
	char buff[blocksize+5];
	int i;
	
	struct meta_data *mdata=(struct meta_data *)calloc(1,sizeof(meta_data));
	
	while (true){

		printf("\n>");
		read_block(0, buff);
		memcpy(mdata,buff, sizeof(meta_data));

		scanf("%s", command);
		if (strcmp(command, "store") == 0){
			scanf("%s", filename);
			store_file(mdata, filename);
		}
		else if (strcmp(command, "retrieve") == 0){
			scanf("%s", filename);
		}
		else if (strcmp(command, "format") == 0){

			char buff[blocksize] = { 0 };
			for (i = 0; i < 6400; i++){
				write_block(i, buff);
			}

			//mdata = (struct meta_data *)calloc(1, sizeof(meta_data));
			struct meta_data m_data;
			m_data.magic = 0x444E524D;
			m_data.block_size = blocksize;
			m_data.blocks[0] = false;
			for (i = 1; i < 6400; i++){
				m_data.blocks[i] = true;
			}
			m_data.total_no_of_blocks = 6400;
			m_data.total_no_of_files = 0;

			memcpy(buff, &m_data, sizeof(meta_data));
			write_block(0, buff);
		}
		else if (strcmp(command, "reset") == 0){
			char buff[blocksize] = { 0 };
			for (i = 0; i < 6400; i++){
				write_block(i, buff);
			}
		}
	}
	//memcpy(buff, mdata, blocksize);
	//write_block(0, buff);
	return;
}