#include<stdio.h>
#include<stdlib.h>

#define blocksize (16*1024)

/*void init(char *filename, int block_size){
	FILE *fp = fopen(filename, "rb+");
	int num;
	fread(&num, sizeof(int), 1, fp);
}*/

void read_block(int i, void *buff){
	FILE *fp = fopen("db.hdd", "rb+");
	fseek(fp, i * 16 * 1024, SEEK_SET);
	fread(buff, blocksize, 1, fp);
	fclose(fp);
}

void write_block(int i, void *buff){
	FILE *fp = fopen("db.hdd", "rb+");
	fseek(fp, i * 16 * 1024, SEEK_SET);
	fwrite(buff, blocksize, 1, fp);
	fclose(fp);
}

void test_BlockIO(){

}