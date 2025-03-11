#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
} candidate;

int main(void)
{
    const int num = 3;
    candidate candidates[num];

    // Populate array with user's input
    for (int i = 0; i < num; i++)
    {
        candidates[i].name = get_string("Name: ");
        candidates[i].votes = get_int("Votes: ");
    }

    int highest_votes = 0;
    for (int i = 0; i < num; i++)
    {
        if (candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
        }
    }
    for (int i = 0; i < num; i++)
    {
        if (candidates[i].votes == highest_votes)
        {
            printf("%s has the highest votes of %i\n", candidates[i].name, highest_votes);
        }
    }
}
