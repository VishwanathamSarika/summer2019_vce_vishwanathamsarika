#ifndef BlockIO_h
#define BlockIO_h

struct file{
	char filename[20];
	int file_size;
	int no_of_blocks;
	int start_block;
};

struct meta_data{
	int magic;
	int block_size;
	int total_no_of_blocks;
	int total_no_of_files;
	bool blocks[6400];
	struct file bitVector[1];
};

void test_BlockIO();
void read_block(int i, void *buff);
void write_block(int i, void *buff);

#endif