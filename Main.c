#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_WORD_LEN 512

int main() {

    StrList* myList = StrList_alloc();
    int choice; // Initialize choice
    int index;
    char word[MAX_WORD_LEN];

    
    
    while (1) {
        scanf("%d", &choice); // Read the choice character

        switch (choice) {
            case 1: {
                int numWords;
                scanf("%d", &numWords); // Read the number of words to insert
                char word[MAX_WORD_LEN];
                for (int i = 0; i < numWords; i++) {
                    scanf("%s", word); // Read each word
                    StrList_insertLast(myList, word); // Insert the word into the list
                }
                break;
            }
            case 2: {
                scanf("%d %s", &index, word);
                StrList_insertAt(myList, word, index);
                break;
            }
            case 3: {
                StrList_print(myList);
                break;
            }
            case 4: {
                printf("%zu\n", StrList_size(myList));
                break;
            }
            case 5: {
                scanf("%d", &index);
                StrList_printAt(myList, index);
                break;
            }
            case 6: {
                printf("%d\n", StrList_printLen(myList));
                break;
            }
            case 7: {
                scanf("%s", word);
                printf("%d\n", StrList_count(myList, word));
                break;
            }
            case 8: {
                scanf("%s", word);
                StrList_remove(myList, word);
                break;
            }
            case 9: {
                scanf("%d", &index);
                StrList_removeAt(myList, index);
                break;
            }
            case 10: {
                StrList_reverse(myList);
                break;
            }
            case 11: {
                StrList_free(myList);
                myList = StrList_alloc();
                break;
            }
            case 12: {
                StrList_sort(myList);
                break;
            }
            case 13: {
                if(StrList_isSorted(myList)){
                    printf("true\n");
                }else{
                    printf("false\n");
                }
                break;
            }
            case 0: {
                StrList_free(myList);
                exit(0);
            }

            default: {
                printf("Invalid choice\n");
                break;
            }
        }
    }
}
