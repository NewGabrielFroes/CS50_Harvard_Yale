// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned long N = 100000;
int count_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index_hash = hash(word);

    for (node *tmp = table[index_hash]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int g = 31;
    int hash = 0;

    for (int i = 0; i < word[i] != '\0'; ++i)
    {
        hash = g * hash + (int)tolower(word[i]);
    }

    if (hash < 0)
    {
        hash *= -1;
    }

    if (hash > N)
    {
        hash = hash % N;
    }

    return hash;

    //Credits: RobEdwards https://www.youtube.com/watch?v=jtMwp0FqEcg&ab_channel=StableSortStableSort
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1]; //1

    if (file == NULL)
    {
        return false;
    }

    int index_hash = 0;

    while (fscanf(file, "%s", word) != EOF)  
    {

        index_hash = hash(word);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = table[index_hash];
        table[index_hash] = n;

        count_words++;
    }
    
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];

        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }

        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }


    return false;
}