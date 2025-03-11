#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    string phrase;
    struct node *next;
}   node;

#define LIST_SIZE = 2

bool unload(node *list);
void visualiser(node*list);

int main(void)
{
    node *list = NULL;

    // Add items to List

    for (int i = 0; i < LIST_SIZE; i++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // Add new node to list
        node *n = malloc(sizeof(node));
        if (n = NULL)
        {
            return 1;
        }

        n -> phrase = phrase;
        n -> next = list;
        list = n;

        // visualise list after adding a node
    }
}

bool unload(node *list)
{
    node *ptr = list;
    while (ptr != NULL)
    {
        ptr = list->next;
        free(list);
        list = ptr;
    }

}
