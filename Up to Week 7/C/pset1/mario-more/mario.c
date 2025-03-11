#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);

int main(void)
{
    int height;
    // Prompt user for input
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int i = 0; i < height; i++)
    {
        // Print spaces
        int diff = height - i - 1;
        for (int j = 0; j < diff; j++)
        {
            printf(" ");
        }
        // Print left hashes
        print_row(i + 1);

        // Print gap
        printf("  ");

        // Print right hashes
        print_row(i + 1);
        printf("\n");
    }
}

void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}
