#include<stdio.h>
#include<stdlib.h>

#include "DLLUtils.h"

struct DLLNode{
	int data;
	struct DLLNode *next;
	struct DLLNode *prev;
};

struct DLLNode* Merge(struct DLLNode *head1, struct DLLNode *head2){
	struct DLLNode *p = head1,*q=head2;
	struct DLLNode *newHead = (p->data < q->data) ? p : q;
}

struct DLLNode* Partition(struct DLLNode *head,struct DLLNode *end){
	int length = getDLLLength(head);
	struct DLLNode *mid,*left,*right;
	if (length > 1){
		mid = getMidNode(head, end);
		left = Partition(head, mid->prev);
		right = Partition(mid, end);
	}
	Merge(left, right);
	return NULL;
}

void test_MergeSortDLL(){
	int arr1[7] = { 1, 2, 3, 4, 5, 6 ,7};
	struct DLLNode *head = createNewDLL(arr1, 7),*mid;
	displayDLL(head);
	mid = getMidNode(head);
	return;
}