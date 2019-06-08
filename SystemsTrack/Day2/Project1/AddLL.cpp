#include<stdio.h>
#include<stdlib.h>

struct Node{
	int data;
	struct Node *next;
};

struct Node* createNode(int x){
	struct Node *p = (struct Node*)malloc(sizeof(struct Node));
	p->data = x;
	p->next = NULL;
	return p;
}

struct Node* createNewLL(int arr[], int size){
	int i;
	struct Node *head = createNode(arr[0]), *temp, *p;
	p = head;
	for (i = 1; i < size; i++){
		temp = createNode(arr[i]);
		p->next = temp;
		p = p->next;
	}
	return head;
}

void displayLL(struct Node *head){
	struct Node *p = head;
	while (p != NULL){
		printf("%d ", p->data);
		p = p->next;
	}
}

struct Node* getPrevious(struct Node *head,struct Node *currNode){
	struct Node *p = head;
	if (p == currNode){
		return NULL;
	}
	while (p->next != currNode){
		p = p->next;
	}
	return p;
}

struct Node* add(struct Node *head1, struct Node *head2){
	struct Node *h1_last=head1, *h2_last=head2,*temp;
	int carry = 0,sum,x;
	while (h1_last->next != NULL){
		h1_last = h1_last->next;
	}
	while (h2_last->next != NULL){
		h2_last = h2_last->next;
	}
	struct Node *p=NULL;
	while (h1_last != NULL && h2_last != NULL){
		sum =carry + h1_last->data + h2_last->data;
		temp = createNode(sum % 10);
		temp->next = p;
		p = temp;
		sum = sum / 10;
		carry = sum % 10;
		h1_last = getPrevious(head1, h1_last);
		h2_last = getPrevious(head2, h2_last);
	}

		while (h1_last != NULL){
			sum = carry + h1_last->data;
			temp = createNode(sum % 10);
			temp->next = p;
			p = temp;
			sum = sum / 10;
			carry = sum % 10;
			h1_last = getPrevious(head1, h1_last);
		}
	
		while (h2_last != NULL){
			sum = carry + h2_last->data;
			temp = createNode(sum % 10);
			temp->next = p;
			p = temp;
			sum = sum / 10;
			carry = sum % 10;
			h2_last = getPrevious(head2, h2_last);
		}
	
	if (carry > 0){
		temp = createNode(carry);
		temp->next = p;
		p = temp;
	}
	return p;
}

void test_add(){
	int arr1[3] = { 1,2,3 };
	int arr2[5] = {9,9,9,8,1 };
	struct Node *head1 = createNewLL(arr1, 3);
	printf("\nlinked list 1 - ");
	displayLL(head1);
	struct Node *head2 = createNewLL(arr2, 5);
	printf("\nlisted list 2 - ");
	displayLL(head2);
	struct Node *sum = add(head1, head2);
	printf("\nsum - ");
	displayLL(sum);
	scanf_s("%s");
	return;
}

