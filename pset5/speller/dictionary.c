// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <math.h>
#include "dictionary.h"
int totalwords=0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//const unsigned int N = 26;
#define N 17577
// Hash table
node *table[N]; //using 3 letter for each bucket


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int address = hash(word);
    node *cursor = table[address];
    while(cursor != NULL)
    {
        if(strcasecmp(cursor->word,word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    int out = 0;
    bool apostrophe = false;
    int letter[3];
    char tmp[LENGTH + 1];
    strcpy(tmp,word);
    for(int i = 0; i < 3; i++)
        {
            if(isalpha(tmp[i]) != 0)
            {
            tmp[i] = toupper(tmp[i]);
            letter[i] = tmp[i] - 65;
            if(letter[i]>=0)
            {
                out += letter[i] * pow(26,(2-i));
            }
            }
            else if(tmp[i]==38)
            {
                apostrophe = true;
            }
        }
    if(apostrophe)
    {
        totalwords++;
        return 17576;
    }
    return out;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *txt = fopen(dictionary,"r");
    if(txt == NULL)
    {
        printf("Text error\n");
        return false;
    }
    char word[LENGTH + 1];
    while(fscanf(txt, "%s", word)!= EOF)
    {
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            printf("Memory Allocation Error\n");
            return false;
        }
        n->next = NULL;
        strcpy(n->word,word);
        int i = hash(n->word);
        totalwords++;
        n->next = table[i];
        table[i] = n;
    }
    fclose(txt);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return totalwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while(cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}