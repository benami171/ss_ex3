#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_WORD_LEN 512
#define INIT_CAPACITY 10

/**
 * A HELPER FUNCTION TO READ A WORD FROM THE STANDARD INPUT
 * This function reads a word from the standard input (stdin)
 * and returns it as a dynamically allocated string.
 * If the input starts with a space or a newline, these characters are ignored.
 * The function dynamically resizes the string as needed to accommodate the word.
 * If the word is empty (consists only of spaces or newlines), the function returns an empty string.
 * If memory allocation fails at any point, the function frees any allocated memory and returns NULL.
 */
char *inWord()
{
    int maxCap = INIT_CAPACITY;
    char *word = (char *)malloc(maxCap * sizeof(char));
    if (word == NULL) {
        printf("Failed to allocate memory for the word\n");
        return NULL;
    }

    int indx = 0;
    char c = 0;
    while (1){
        c = getchar();
        if (c == ' ' || c == '\n')
        {
            if (indx == 0){
                continue;
            }
            word[indx] = '\0';
            break;
        }
        word[indx] = c;
        indx++;
        if (indx >= maxCap)
        {
            maxCap *= 2;
            // we use temp because otherwise in a case of allocation failur,
            // word will be lost. so that way we can safely check 
            // if the allocation was successful
            char* temp = (char *)realloc(word, maxCap * sizeof(char));
            if (temp == NULL) {
                printf("Failed to allocate memory for the word\n");
                free(word);
                return NULL;
            }
            word = temp;
        }
    }
    // in case the word is empty
    // we sets the first character to '\0'
    // because we want to return an empty null-terminated string
    if (indx == 0) {
        word[indx] = '\0';
    }
    return word;
}

int main()
{

    StrList *myList = StrList_alloc();
    int choice; // Initialize choice
    int index;
    int num_words;
    char word[MAX_WORD_LEN];
    char *data;

    while (1)
    {
        scanf("%d", &choice); // Read the choice character

        switch (choice)
        {
        case 1:
        {
            if (scanf("%d", &num_words) != 1)
            {
                printf("Invalid choice\n");
                break;
            }
            for (int i = 0; i < num_words; i++)
            {
                data = inWord();
                if (data == NULL)
                {
                    printf("Invalid choice\n");
                    break;
                }
                StrList_insertLast(myList, data);
                free(data);
            }
            break;
        }
        // case 1: {
        //     int numWords;
        //     scanf("%d", &numWords); // Read the number of words to insert
        //     char word[MAX_WORD_LEN];
        //     for (int i = 0; i < numWords; i++) {
        //         scanf("%s", word); // Read each word
        //         StrList_insertLast(myList, word); // Insert the word into the list
        //     }
        //     break;
        // }
        case 2:
        {
            scanf("%d %s", &index, word);
            StrList_insertAt(myList, word, index);
            break;
        }
        case 3:
        {
            StrList_print(myList);
            break;
        }
        case 4:
        {
            printf("%zu\n", StrList_size(myList));
            break;
        }
        case 5:
        {
            scanf("%d", &index);
            StrList_printAt(myList, index);
            break;
        }
        case 6:
        {
            printf("%d\n", StrList_printLen(myList));
            break;
        }
        case 7:
        {
            scanf("%s", word);
            printf("%d\n", StrList_count(myList, word));
            break;
        }
        case 8:
        {
            scanf("%s", word);
            StrList_remove(myList, word);
            break;
        }
        case 9:
        {
            scanf("%d", &index);
            StrList_removeAt(myList, index);
            break;
        }
        case 10:
        {
            StrList_reverse(myList);
            break;
        }
        case 11:
        {
            StrList_free(myList);
            myList = StrList_alloc();
            break;
        }
        case 12:
        {
            StrList_sort(myList);
            break;
        }
        case 13:
        {
            if (StrList_isSorted(myList))
            {
                printf("true\n");
            }
            else
            {
                printf("false\n");
            }
            break;
        }
        case 0:
        {
            StrList_free(myList);
            exit(0);
        }

        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
    }
}
