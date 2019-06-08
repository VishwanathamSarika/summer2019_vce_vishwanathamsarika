#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "DiskIO.h"

#define blocksize (16*1024)

struct file{
	char file_name[20];
	unsigned int stack_length, //start of block num
		no_of_blocks,
		file_length;
};

struct meta_data{
	int magic;
	struct file arr[32];
	int no_of_files;
	bool files[6400];
};

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


void store_file(struct meta_data *mdata,char *filename){
	char buff[16 * 1024];
	int flag=0;

	struct file newFile;
	strcpy(newFile.file_name,filename);
	newFile.file_length = get_FileSize(filename);
	newFile.no_of_blocks = ceil(double(newFile.file_length) / blocksize);

	int i,j;
	for (i = 0; i < 6400; i++){
		if (mdata->files[i] == true){
			for (j = i; j < i+newFile.no_of_blocks; j++){
				if (mdata->files[j] == false){
					flag = 1;
				}
			}
			if (j == i + newFile.no_of_blocks && flag!=1){
				newFile.stack_length = i;
				break;
			}
			else{
				continue;
			}
		}
	}
	if (i == 6400){
		printf("\nNo sufficient memory to alloate file");
	}
	else{
		mdata->arr[mdata->no_of_files + 1] = newFile;
		mdata->no_of_files = mdata->no_of_files + 1;
	}

	FILE *fp = fopen("db.hdd", "rb+");
	FILE *fp1 = fopen(filename, "rb");

	fseek(fp, (newFile.stack_length-1) * 16 * 1024, SEEK_SET);
	
	i = newFile.stack_length;
	if (newFile.no_of_blocks == double(newFile.file_length) / blocksize){
		for (j = 0; j < newFile.no_of_blocks; j++){
			fread(buff, blocksize,1, fp1 );
			memcpy(fp, buff, blocksize);
			i++;
		}
	}
	else{
		for (i = 0; i < newFile.no_of_blocks-1; i++){
			fread(buff, blocksize, 1, fp1);
			memcpy(fp, buff, blocksize);
			i++;
		}
		int offset = newFile.file_length%blocksize;
		fread(buff, offset, 1, fp1);
		memcpy(fp, buff, offset);
	}

	i = newFile.stack_length;
	for (j = 0; j < newFile.no_of_blocks; j++){
		mdata->files[i] = false;
		i++;
	}
	//fwrite(mdata, blocksize, 1, fp);
	fclose(fp);
	fclose(fp1);
}

void test_blocksFS(){
	char *command = (char *)calloc(50, sizeof(char));
	char *filename = (char *)calloc(50, sizeof(char));
	char buff[16*1024];
	int i;

	struct meta_data mdata;
	mdata.magic = 0x444E524D;
	for (i = 0; i < 6400; i++){
		mdata.files[i] = true;
	}
	mdata.no_of_files = 0;
	mdata.files[0] = false;
	FILE *fp = fopen("db.hdd", "wb");
	while (true){
		printf("\n>");

		/*struct meta_data *m_data=(struct meta_data *)calloc(1,sizeof(struct meta_data));
		read_block(0, buff);
		memcpy(m_data, buff, sizeof(meta_data));*/

		scanf("%s", command);
		if (strcmp(command, "store") == 0){
			scanf("%s", filename);
			store_file(&mdata,filename);
		}
		else if (strcmp(command, "retrieve") == 0){
			scanf("%s", filename);
		}
		/*memcpy(buff,&mdata, sizeof(meta_data));
		write_block(0, buff);*/
	}
	memcpy(buff, &mdata, sizeof(struct meta_data));
	write_block(0, buff);
	fclose(fp);
}
