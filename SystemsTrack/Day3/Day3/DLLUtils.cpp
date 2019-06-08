#include<stdio.h>
#include<stdlib.h>

struct DLLNode{
	int data;
	struct DLLNode *next;
	struct DLLNode *prev;
};

struct DLLNode* createNewDLLNode(int x){
	struct DLLNode *newNode = (struct DLLNode *)malloc(sizeof(DLLNode));
	newNode->data = x;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

struct DLLNode* createNewDLL(int arr[], int size){
	int i;
	if (size > 0){
		struct DLLNode *head = createNewDLLNode(arr[0]);
		struct DLLNode *p = head, *temp;
		for (i = 1; i < size; i++){
			temp = createNewDLLNode(arr[i]);
			temp->prev = p;
			p->next = temp;
			p = p->next;
		}
		return head;
	}
	else{
		return NULL;
	}
}

void displayDLL(struct DLLNode *head){
	struct DLLNode *p = head;
	printf("\nThe list contents are :\n");
	while (p != NULL){

		if (p->prev != NULL){
			printf("\n%d <- ", p->prev->data);
		}
		else{
			printf("\nNULL <- ");
		}

		printf("%d -> ", p->data);

		if (p->next != NULL){
			printf("%d\n", p->next->data);
		}
		else{
			printf("NULL\n");
		}

		p = p->next;
	}
}

struct DLLNode* getMidNode(struct DLLNode *head){
	struct DLLNode *slow = head;
	struct DLLNode *fast = head;
	while (fast != NULL && fast->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
	}
	printf("\nMidvalue is %d", slow->data);
	return slow;
}

struct DLLNode* getMidNode(struct DLLNode *head,struct DLLNode *end){
	struct DLLNode *slow = head;
	struct DLLNode *fast = head;
	while (fast != end && fast->next != end){
		fast = fast->next->next;
		slow = slow->next;
	}
	printf("\nMidvalue is %d", slow->data);
	return slow;
}

int getDLLLength(struct DLLNode *head){
	struct DLLNode *p = head;
	int length = 0;
	while (p != NULL){
		p = p->next;
		length++;
	}
	return length;
}

int getDLLLength(struct DLLNode *head,struct DLLNode *end){
	struct DLLNode *p = head;
	int length = 0;
	while (p != end){
		p = p->next;
		length++;
	}
	return length;
}