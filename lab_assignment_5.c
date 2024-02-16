#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head) {
	// TODO:
	// this is a common pattern to traverse a linked list
	// but it's O(n) time complexity. We could add a length
	// member to the linked list struct and update it every time 
	// we add or remove a node. This way we can get the length
	// in O(1) time.
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}


// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char* toCString(node* head) {
    int len = length(head);
    char* str = malloc(len + 1);
    if (str == NULL) return NULL;

    for (int i = 0; head != NULL; head = head->next, i++) {
        str[i] = head->letter;
    }
    str[len] = '\0';
    return str;
}

// appends character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	// Traversing the linked list every time to add a new node
	// is not efficient. A common optimization is to keep a pointer to the
	// last node in the linked list. This way we can add a new node
	// in O(1) time. This is called a tail pointer.
	// I'll leave it to you to implement this optimization.
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL) return;
	newNode->letter = c;
	newNode->next = NULL;

	if (*pHead == NULL){
		*pHead = newNode;
	}
	else{
		node *current = *pHead;
		// don't need to check  `current != NULL`
		// as the if next is NULL then it will break the loop
		// and the newNode will be added to the end of the list
		while(current->next != NULL){
			current = current->next;
		}
		current->next = newNode;
	}
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead) {
    while (*pHead != NULL) {
        node* todelete = *pHead;
        *pHead = (*pHead)->next;
        free(todelete);
    }
}

int main(void) {
    node* head = NULL;
    FILE* inFile = fopen("input.txt", "r");
	// Check if file is opened successfully
    if (inFile == NULL) {
		// Good practice use perror to print error message
		// It'll print the error message to stderr along with the 
		// error code
        perror("Error opening file");
		// return error codes
        return EXIT_FAILURE;
    }

    int numInputs;
    fscanf(inFile, "%d", &numInputs);

    while (numInputs-- > 0) {
        int strLen;
        fscanf(inFile, "%d", &strLen);

        for (int i = 0; i < strLen; i++) {
            char c;
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }

        char* str = toCString(head);
        if (str != NULL) {
            printf("String is: %s\n", str);
            free(str);
        }

        deleteList(&head);
		if (head != NULL)
		{
			perror("Error deleting list");
			break;
		}
    }

    fclose(inFile);
    return EXIT_SUCCESS;
}