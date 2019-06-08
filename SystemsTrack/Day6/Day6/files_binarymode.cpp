#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
	char name[6];
	int marks;
	int friend_count;
};

void test_binmode(){
	int num = 0x31323334;
	FILE *fp;
	fp = fopen("bin_file.txt", "wb+");
	/*fwrite(&num, sizeof(num), 1, fp);
	num = 4321;
	fwrite(&num, sizeof(num), 1, fp);
	fprintf(fp, "\n%d", num);*/

	/*struct student s,s1;
	strcpy(s.name,"sarika");
	s.marks = 70;
	s.friend_count = 5;

	fwrite(&s, sizeof(struct student), 1, fp);
	fclose(fp);
	fp = fopen("bin_file.txt", "rb+");
	fread(&s1, sizeof(struct student), 1, fp);
	printf("%s\n%d\n%d\n", s1.name,s1.marks,s1.friend_count);*/
	int magic[6] = { 1920409673, 543519849, 543449442, 1701080931, 1767990304, 3045740 };
	fwrite(&magic, sizeof(magic), 1, fp);
	fclose(fp);
}