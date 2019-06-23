#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define PAGE_SIZE 32

#pragma pack(4)

struct LeafPage{
	int sid[3];
	char name[3][5];
	char pageType;
	char unused[3];
};

struct NonLeafPage{
	char pageType;
	char unused[3];
	int childPageId[4];
	int value[3];
};

struct pageInfo{
	char page_buffer[PAGE_SIZE];
	bool used;
	time_t timestamp;
	int pageId;
};

int search_Leaf(struct LeafPage *LeafP, int m){
	int i;
	for (i = 0; i < 3; i++){
		if (LeafP->sid[i] == m){
			printf("\nFound");
			return 1;
		}
	}
	return -1;
}

void search_Sid(struct pageInfo *pagePool,int key){
	FILE *fp = fopen("test.txt", "rb+");
	int i, j;

	struct LeafPage LPS[4];
	for (i = 0; i < 4; i++){
		fread(&LPS[i], sizeof(LeafPage), 1, fp);
	}

	struct NonLeafPage NLP;
	fread(&NLP, sizeof(NonLeafPage), 1, fp);

	for (i = 0; i < 3; i++){
		if (NLP.value[i] > key && search_Leaf(&LPS[i], key) == 1){
			//If found in left pages
			LRU_Algorithm(pagePool, &LPS[i]);
		}
	}
	//If found in last page
	if (search_Leaf(&LPS[3], key) == 1){
		LRU_Algorithm(pagePool, &LPS[3]);
	}
}

void LRU_Algorithm(struct pageInfo *pagePool,struct LeafPage *LeafP){
	int i,max=0;
	time_t time;
	for (i = 1; i < 3; i++){
		
	}
}

void test_BTrees01(){
	//printf("%d %d", sizeof(LeafPage), sizeof(NonLeafPage));
	int i, j,k;
	char names[12][5] = { "anu", "sita", "gita", "ram", "sam", "joe", "abc", "def", "ghi", "jkl", "mno", "pqr" };
	int sids[12] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120 };
	FILE *fp;
	fp = fopen("test.txt", "wb+");

	struct pageInfo pagePool[3];

	//One NonLeaf and 4 leafs

	k = -1;
	struct LeafPage LPS[4];
	for (i = 0; i < 4; i++){
		for (j = 0; j < 3; j++){
			LPS[i].pageType = '1';
			strcpy(LPS[i].name[j],names[++k]);
			LPS[i].sid[j] = sids[k];
		}
	}

	for (i = 0; i < 4; i++){
		fwrite(&LPS[i], sizeof(LeafPage), 1, fp);
	}

	fseek(fp, 0, SEEK_SET);
	//For Updating Non Leaf Node
	struct LeafPage tempLPS;
	struct NonLeafPage newNLP;
	newNLP.pageType = '0';
	newNLP.childPageId[0] = 0;
	fread(&tempLPS, sizeof(LeafPage), 1, fp);
	for (i = 1; i < 4; i++){
		fread(&tempLPS, sizeof(LeafPage), 1, fp);
		newNLP.value[i-1] = tempLPS.sid[0];
		newNLP.childPageId[i] = newNLP.childPageId[i-1] +32 ;
	}
	fflush(fp);
	fseek(fp, 128, SEEK_SET);
	fwrite(&newNLP, sizeof(NonLeafPage), 1, fp);
	fflush(fp);

	fclose(fp);
}