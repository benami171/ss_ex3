#include "StrList.h"
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>



/**
 * Node structure for a singly linked list.
 * Each node contains a line of text and a pointer to the next and previous nodes in the list.
 */
typedef struct Node {
    char* line;
    struct Node* next;
    struct Node* prev;
} Node;

/**
 * StringList structure, which is a singly linked list of Node.
 * Contains a pointer to the head of the list and the size of the list.
 */
struct _StrList {
    Node* head;
    Node* tail;
    size_t size;
};

/**
 * Allocates a new Node with the given line, nextNode, and prevNode.
 * The function will allocate memory for the new Node and its line.
 * It's the user's responsibility to free the memory with Node_free.
 *
 * @param line The line to be stored in the Node. The function will create a copy of this line.
 * @param nextNode The next Node in the list.
 * @param prevNode The previous Node in the list.
 * @return A pointer to the newly allocated Node, or NULL if the allocation failed.
 */
Node* Node_alloc(const char* line, Node* nextNode, Node* prevNode){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        return NULL;
    }
    newNode->line = (char*)malloc(strlen(line) + 1); // Allocate memory for the string
    if (newNode->line == NULL){
        free(newNode);
        return NULL;
    }
    strcpy(newNode->line, line); // Copy the string
    newNode->next = nextNode;
    newNode->prev = prevNode;
    return newNode;
}

/**
 * Frees the memory used by a Node and its line.
 * @param node The node to free.
 */
void Node_free(Node* node) {
    free(node->line);
    free(node);
}

/**
 * Allocates memory for a new StringList and initializes its fields.
 * @return A pointer to the newly allocated StringList, or NULL if allocation failed.
 */
StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (list == NULL) {
        return NULL; // in case malloc failed
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * Frees the memory used by a StringList and all its Nodes.
 * the function enters a loop that traverses the list until it
 * reaches the end of the list.
 *
 * For each Node the function first saves a pointer to the next Node, then frees
 * the current Node
 *
 * After all Nodes have been freed, the function frees the StringList
 * itself.
 *
 * @param list The StringList to free.
 */
void StrList_free(StrList* StrList) {
    if (StrList == NULL) return;
    Node* currNode = StrList->head;
    Node* nextNode;
    while(currNode) {
        nextNode = currNode;
        currNode = currNode-> next;
        Node_free(nextNode);
    }
    free(StrList);
}


size_t StrList_size(const StrList* StrList) {
    if (StrList == NULL) return 0;
    return StrList->size;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    Node* newNode = Node_alloc(data,NULL,NULL);
    if(newNode == NULL) {
        return; // malloc failed
    }
    // if list was empty, insert in the beginning
    if (StrList->head == NULL) {
        StrList->head = newNode;
        StrList->tail = newNode;
    }
        // if list was not empty, insert at the end
    else {
        newNode->prev = StrList->tail;
        StrList->tail->next = newNode;
        StrList->tail = newNode;
    }
    StrList->size++;
}

/**
 * Inserts a new Node at the given index in the list.
 * If the index is out of range, the function does nothing.
 * If the index is 0, the function inserts the new Node at the beginning of the list.
 * If the index is the size of the list, the function inserts the new Node at the end of the list.
 * Otherwise, the function traverses the list to find the Node at the given index and inserts the new Node after it.
 * @param list The list to insert into.
 * @param data The line of text to store in the new Node.
 * @param index The index to insert the new Node at.

*/
void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if(index < 0 || (size_t)index > StrList->size) {
        return;
    }
    Node* newNode = Node_alloc(data,NULL,NULL);
    if (newNode == NULL) {
        return;
    }

    // if list was empty or index = 0, insert in the beginning
    if (StrList->head == NULL || index == 0){
        newNode->next = StrList->head;
        if (StrList->head != NULL) {
            StrList->head->prev = newNode;
        }
        StrList->head = newNode;
        // in case list was empty
        if (StrList->tail == NULL) {
            StrList->tail = newNode;
        }
    } else {

        Node* currNode = StrList->head;
        for ( int i=0; i<index - 1 ; i++) {
            currNode = currNode->next;
        }
        newNode->next = currNode->next;
        newNode->prev = currNode;
        if(currNode->next != NULL) {
            currNode->next->prev = newNode;
        }
        currNode->next = newNode;
        if(newNode->next == NULL){
            StrList->tail = newNode;
        }
    }

    StrList->size++;
}

/**
 * Returns the data of the first node in the StrList.
 * If the list is empty, the function returns NULL.
 * @param StrList The list to get the data from.
 * @return The data of the first node in the list.
 */
char* StrList_firstData(const StrList* StrList) {
    if( StrList == NULL || StrList->head == NULL) {
        return NULL;
    }
    return StrList->head->line;
}

/** A HELPER FUNCTION
 * Returns a pointer to the node at a given index in the StrList.
 * If the list is NULL, the index is negative, or the index is greater than or equal to the size of the list, the function returns NULL.
 * Otherwise, the function traverses the list until it reaches the specified index and returns a pointer to the node at that index.
 * @param StrList The list to get the node from.
 * @param index The index of the node to get.
 * @return A pointer to the node at the specified index in the list, or NULL if the index is out of bounds.
 */
Node* getNodeAt(const StrList* StrList, int index) {
    if (StrList == NULL || index < 0 || (size_t)index >= StrList->size) {
        return NULL;
    }
    Node* currNode = StrList->head;
    for (int i = 0; i < index; i++) {
        currNode = currNode->next;
    }
    return currNode;
}

/*
 * iterates through all nodes and prints their data.
 */
void StrList_print(const StrList* StrList) {
    if( StrList == NULL || StrList->head == NULL) {
        printf("\n");
        return;
    }
    Node* currNode = StrList->head;
    printf("%s", currNode->line);
    currNode = currNode->next;

    while (currNode){
        printf(" %s", currNode->line);
        currNode = currNode->next;
    }
    printf("\n");
}

/**
 * Prints the data of the node at a given index in the StrList to the standard output.
 * If the index is out of bounds, the function does nothing.
 * @param StrList The list to print the data from.
 * @param index The index of the node to print.
 */
void StrList_printAt(const StrList* StrList, int index) {
    if (StrList==NULL || StrList->head == NULL) {
        return;
    }
    if (StrList->size < (size_t)index || index < 0) {
        return;
    }

    Node* currNode = getNodeAt(StrList,index);
    if(currNode == NULL) {
        return;
    }
    printf("%s\n",currNode->line);
}

/**
 * Returns the amount of characters in the list.
 * If the list is empty, the function returns 0.
 * @param StrList The list to count the characters in.
 * @return The amount of characters in the list.
 */
int StrList_printLen(const StrList* StrList) {
    if (StrList->head == NULL || StrList == NULL){
        return 0;
    }
    int charLenCounter = 0;
    Node* currNode = StrList->head;
    while(currNode!= NULL){
        charLenCounter += strlen(currNode->line);
        currNode = currNode->next;
    }

    if (charLenCounter > INT_MAX) {
        return INT_MAX;
    } else {
        return (int)charLenCounter;
    }
}

int StrList_count(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) {
        return 0; // nothing to check
    }

    int count = 0;
    Node *current = StrList->head;
    while(current != NULL){
        if(strcmp(current->line,data) == 0){
            count++;
        }
        current = current->next;
    }

    return count;
}

/**
 * @param StrList: A pointer to the StrList.
 * @param data: The string to match with node's line.
 * The function iterates over the StrList. If a node's line matches the input string,
 * the node is removed and its memory is freed. If not, the function moves to the next node.
 */
void StrList_remove(StrList* StrList, const char* data) {
    if (StrList == NULL || StrList->head == NULL || data == NULL) {
        return;
    }

    Node* currNode = StrList->head;
    Node* prevNode = NULL;
    while(currNode != NULL) {
        if(strcmp(currNode->line, data) == 0) {
            if(prevNode == NULL) {
                // if the node to remove is the first node
                StrList->head = currNode->next;
            } else {
                // if the node to remove is not the first node
                prevNode->next = currNode->next;
            }
            Node* tempNode = currNode;
            currNode = currNode->next;
            free(tempNode->line);
            free(tempNode);
        } else {
            prevNode = currNode;
            currNode = currNode->next;
        }
    }
}

void StrList_removeAt(StrList* StrList, int index) {
    if (StrList == NULL || index < 0 || (size_t)index >= StrList->size) {
        return; // Invalid input or index out of bounds
    }
    Node* current = StrList->head;
    Node* prev = NULL;
    int i = 0;
    // Traverse the list to find the node at the given index
    while(current != NULL && i < index){
        prev = current;
        current = current -> next;
        i++;
    }
    // If the node was found, remove it
    if(current != NULL){
        if(prev != NULL){
            // If the node to remove is not the first node
            prev -> next = current -> next;
            if(current -> next == NULL) {
                // If the node to remove is the last node
                StrList -> tail = prev;
            }
        }else{
            // If the node to remove is the first node
            StrList -> head = current -> next;
            if(StrList -> head == NULL) {
                // If the node to remove is the only node
                StrList -> tail = NULL;
            }
        }

        free(current->line);
        free(current);
        StrList->size--;
    }
}

/**
 * This function compares two StrLists. 
 * It first checks for NULL lists and unequal sizes, returning 0 if either condition is met. 
 * It treats two NULL lists as equal and returns 1.
 * Then, it iterates through both lists simultaneously, comparing each pair of strings with strcmp. 
 * If any pair is unequal, it returns 0 immediately.
 * If it completes the iteration without finding unequal pairs, it returns 1.
 * @param StrList1 A pointer to the first StrList.
 * @param StrList2 A pointer to the second StrList.
 * @return Returns 1 if the two StrLists are equal, and 0 otherwise.
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2) {

    if ((StrList1 == NULL && StrList2 != NULL) || (StrList1 != NULL && StrList2 == NULL) || (StrList1->size != StrList2->size)) {
        return 0;
    }

    if (StrList1 == NULL && StrList2 == NULL) {
        return 1;
    }

    Node *current1 = StrList1->head;
    Node *current2 = StrList2->head;

    while (current1 != NULL && current2 != NULL) {
        int cmp = strcmp(current1->line, current2->line);
        if (cmp != 0) { // If any pair of elements is unequal, the lists are not equal
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return 1;
}


/**
 * This function clones a given StrList. 
 * It allocates memory for a new StrList and iterates through the given StrList, 
 * inserting each string into the new StrList. 
 * It returns a pointer to the new StrList.
 * @param StrList A pointer to the StrList to clone.
 * @return A pointer to the newly allocated StrList, or NULL if the allocation failed.
 */
StrList* StrList_clone(const StrList* StrList) {
    if(StrList == NULL){
        return NULL;
    }
    struct _StrList* clone;
    clone = StrList_alloc(); // Allocate memory for the new StrList
    if (clone == NULL) {
        return NULL; // Return NULL if memory allocation failed
    }
    Node* current = StrList->head;
    while(current != NULL){
        StrList_insertLast(clone, current->line);
        current = current->next;
    }
    return clone;
}

/**
 * This function reverses the order of nodes in a given StrList.
 * It first checks if the StrList is NULL or has less than two nodes.
 * If so, it returns immediately as there's nothing to reverse.
 * Then, it iterates through the list, reversing the next and prev pointers of each node.
 * Finally, it updates the head and tail pointers of the StrList to point to the new head and tail.
 * @param StrList A pointer to the StrList to be reversed.
 */
void StrList_reverse(StrList* StrList) {

    if (StrList == NULL || StrList->head == NULL || StrList->head->next == NULL) {
        return; // Nothing to reverse
    }

    Node *current = StrList->head;
    Node *prev = NULL;
    Node *next = NULL;

    while(current != NULL){
        next = current->next;
        current->prev = next;
        current->next = prev;
        prev = current;
        current = next;
    }
    StrList->tail = StrList->head;
    StrList->head = prev;
}
/**
 * Sorts a StrList in ascending order using a variant of Bubble Sort.
 * @param StrList: The list to be sorted. If StrList is NULL or has less than two nodes,
 * the function returns immediately.
 * The function iterates over the list, comparing and swapping adjacent nodes if necessary.
 * This process repeats until a pass occurs with no swaps, indicating the list is sorted.
 */
void StrList_sort(StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL || StrList->head->next == NULL) {
        return; // Nothing to sort
    }
    Node* end = NULL;
    int swapped;

    do {
        swapped = 0;
        Node* current = StrList->head;

        while (current->next != end) {
            if (strcmp(current->line, current->next->line) > 0) {
                char* temp = current->line;
                current->line = current->next->line;
                current->next->line = temp;
                swapped = 1;
            }
            current = current->next;
        }
        end = current;
    } while (swapped);
}

int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL || StrList->head->next == NULL) {
        return 1; // Empty or single-element list is considered sorted
    }
    Node *current = StrList->head;
    while(current->next != NULL) {
        if (strcmp(current->line, current->next->line) > 0) {
            return 0; // If a pair of elements is out of order, the list is not sorted
        }
        current = current->next;
    }
    return 1; // If we've gone through the whole list without finding out-of-order elements, the list is sorted
}