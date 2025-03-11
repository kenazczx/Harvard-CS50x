// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * LENGTH * LENGTH;

// Hash table
node *table[N];
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hash_value = hash(word);
    node *cursor = table[hash_value];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
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
    // TODO: Improve this hash function
    int word_length = strlen(word);
    unsigned long hash_number = 0;
    for (int i = 0; i < word_length; i++)
    {
        hash_number += (toupper(word[i]) - 'A') * i;
    }
    return hash_number % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    // Read each word in dictionary
    while (fscanf(dict, "%s", word) != EOF)
    {
        // add each word to the hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        int hash_output = hash(word);
        n->next = table[hash_output];
        table[hash_output] = n;
        word_count += 1;
    }
    // close the dictionary file
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
