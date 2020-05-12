// Implements a dictionary's functionality
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "dictionary.h"
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

//Global variable for dictionary word count
int dic_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int idx = hash(word);
    //printf("index location we're checking: %i\n", idx);
    bool flag = false;
    for (node *tmp = table[idx]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
        {
            printf("file is not readable\n");
            return false;
        }
    
    char *line = malloc(LENGTH);
    //Check for available memory
    if (line == NULL)
    {
        printf("No Memory\n");
        return false;
    }
    
    //Read through dictionary File
    while (fscanf(dict, "%s", line) != EOF)
    {
        //Check for available memory
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("No Memory\n");
            return false;
        }
        
        //Copy the string from dictionary file into node
        strcpy(n->word, line);
        
        //Make Next section of current node be NULL
        n->next = NULL;
        
        //Get index location for given word
        int idx = hash(n->word);
        //node *link_list = table[hash(n->word)];
        //printf("index location we're putting it in: %i\n", hash(n->word));
        
        //Update size of dictionary
        dic_size += 1;
        
        //Insert node into correct linked list
        if (table[idx] == NULL)
        {
            table[idx] = n;
        }
        
        else
        {
            n->next = table[idx];
            table[idx] = n;
        }
    }
    //free(n);
    free(line);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dic_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    
    //Loop through all of the buckets clearing memory
    for (int i = 0; i < N; i++)
    {
        node* cursor = table[i];
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
