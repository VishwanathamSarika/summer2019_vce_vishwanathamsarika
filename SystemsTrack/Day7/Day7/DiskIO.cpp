#include<stdio.h>
#include<stdlib.h>

#define blocksize (16*1024)

void read_block(int i, char *buff){
	FILE *fp = fopen("db.hdd", "rb+");
	fseek(fp, i * 16 * 1024, SEEK_SET);
	fread(&buff, blocksize, 1, fp);
	fclose(fp);
}

void write_block(int i, char *buff){
	FILE *fp = fopen("db.hdd", "rb+");
	fseek(fp, i * 16 * 1024, SEEK_SET);
	fwrite(&buff, blocksize, 1, fp);
	fclose(fp);
}

void init(){

}
