#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Get users input
    string text = argv[1];
    length = strlen(text)
    if (argc != 2)
    {
        printf("Please provide a word.\n");
        return 1;
    }
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(text[i]))
        {
            printf("This is not a letter.\n");
            return 2;
        }
    }
    // Iterate through each element in the string
    for (int i = 1; i < length; i++)
    {
        if (text[i -1] > text[i])
        {
            printf("No\n");
            return 0;
        }
    }
        // check if its alphabetical

    // Print yes or no
    printf("Yes\n");
}
