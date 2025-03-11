#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string text);
int main(int argc, string argv[])
{
    // Make sure program is run with one command-line argument
    if (!(argc == 2))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int length = strlen(argv[1]);
    // Make sure every character in argv[1] is a digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Convert argv[1] from a string to a int
    int convert = atoi(argv[1]);

    if (convert > 26)
    {
        convert = convert % 26;
    }
    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    // For each character in the plaintext
    printf("ciphertext: ");
    for (int i = 0, plength = strlen(plaintext); i < plength; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                printf("%c", ((plaintext[i] - 'A' + convert) % 26) + 'A');
            }
            if (islower(plaintext[i]))
            {
                printf("%c", ((plaintext[i] - 'a' + convert) % 26) + 'a');
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    // Rotate the character if its a letter
}

bool only_digits(string text)
{
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (!isdigit(text[i]))
        {
            return false;
        }
    }
    return true;
}
