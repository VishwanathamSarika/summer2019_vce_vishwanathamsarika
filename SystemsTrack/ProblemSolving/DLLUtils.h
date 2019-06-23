#ifndef DLLUtils_h
#define DLLUtils_h

struct DLLNode* createNewDLLNode(int x);
struct DLLNode* createNewDLL(int arr[], int size);
void displayDLL(struct DLLNode *head);
struct DLLNode* getMidNode(struct DLLNode *head);
struct DLLNode* getMidNode(struct DLLNode *head, struct DLLNode *end);
int getDLLLength(struct DLLNode *head);
int getDLLLength(struct DLLNode *head, struct DLLNode *end);

#endif