#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    // Compute the Coleman-Liau index
    int coleman = round(0.0588 * (((float) letters / words) * 100) -
                        0.296 * ((float) sentences / words) * 100 - 15.8);
    // Print grade level
    if (coleman < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", coleman);
    }
}

int count_letters(string text)
{
    int scorel = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isupper(text[i]))
        {
            scorel++;
        }
        else if (islower(text[i]))
        {
            scorel++;
        }
    }
    return scorel;
}

int count_words(string text)
{
    int scorew = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            scorew++;
        }
    }
    return (scorew + 1);
}

int count_sentences(string text)
{
    int scores = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.')
        {
            scores++;
        }
        else if (text[i] == '!')
        {
            scores++;
        }
        else if (text[i] == '?')
        {
            scores++;
        }
    }
    return scores;
}
