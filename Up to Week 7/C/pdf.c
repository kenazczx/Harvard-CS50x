#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // check for usage, must be 2 CLA
    if (argc != 2)
    {
        printf("Print provide only one filename\n");
        return 1;
    }
    // Open File
    FILE *input = fopen(argv[1], "r");

    // Create buffer for file
    uint8_t buffer[4];

    // Create an array of signature bytes
    uint8_t signature[] = {0x25, 0x50, 0x44, 0x46};

    // Read first 4 bytes from the file
    fread(buffer, sizeof(uint8_t), 4, input);

    // Check the first 4 bytes again signature bytes
    for (int i = 0; i < 4; i++)
    {
        if (signature[i] != buffer[i])
        {
            printf("This is not a PDF!\n");
            return 0;
        }

    }

    // Success
    printf("It is a pdf!\n");
    // Close file
    fclose(input);

    return 0;
}
