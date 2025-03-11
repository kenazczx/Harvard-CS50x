#include <stdio.h>
#include <cs50.h>

int const size = 5;
int main(void)
{
    // Declare an array
    int numbers[size];
    numbers[0] = 1;
    for (int j = 1; j < size; j++)
    {
        numbers[j] = numbers[j - 1] * 2;
    }
    // Print out value one by one
    for (int i = 0; i < size; i++)
    {
        printf("%i\n", numbers[i]);
    }
}
