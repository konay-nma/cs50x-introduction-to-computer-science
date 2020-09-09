// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define N 65536

// define struct node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// declare words to count the words in the dictionary
int dic_size = 0;
// declare hashtable
node *table[N];

// hash funtion
unsigned int hash(const char *word)
{
    unsigned int hash = 401;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 4) ^ word[i];
    }
    return hash % N;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int len = strlen(word);
    char lword[len + 1];
    for (int i = 0; i < len; i++)
    {
        lword[i] = tolower(word[i]);
    }
    lword[len] = '\0';

    int bucket = hash(lword);
    node *cursor = table[bucket];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, lword) != 0)
        {
            cursor = cursor->next;
        }
        else
        {
            return true;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];


    while (fscanf(dic, "%s", buffer) != EOF)
    {
        // create a temporary node
        node *temp = malloc(sizeof(node));
        strncpy(temp->word, buffer, sizeof(buffer));

        // implement hash function to get the index
        int index = hash(buffer);

        // if the corresponding index in hashtable is empty, assign it to the temp node
        if (table[index] == NULL)
        {
            table[index] = temp;
        }

        // else append temp to the start of the linked list
        else
        {
            temp->next = table[index];
            table[index] = temp;
        }
        dic_size ++;
    }

    fclose(dic);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dic_size;
}


/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0 ; i < N ; i++)
    {
        node *cursor = table[i];
        if (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

    }

    return true;
}