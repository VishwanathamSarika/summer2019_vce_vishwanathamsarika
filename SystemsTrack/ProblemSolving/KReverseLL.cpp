#include<stdio.h>
#include<stdlib.h>
#include "AddLL.h"

struct Node{
	int data;
	struct Node *next;
};

struct Node* kReverse(struct Node *head,int k){
	struct Node* current = head;
	struct Node* next = NULL;
	struct Node* prev = NULL;
	int count = 0;
	while (current != NULL && count < k){
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
		count++;
	}
	if (next != NULL){
		head->next = kReverse(next, k);
	}
	return prev;
}
void test_kRevLL(){
	int arr1[8] = { 1, 2, 3, 9, 9, 9, 8, 1 };
	struct Node *head1 = createNewLL(arr1, 8);
	printf("\nOriginal linked list 1 - ");
	displayLL(head1);
	printf("\n");
	displayLL(kReverse(head1,3));
	return;
}