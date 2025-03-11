#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command line argument
    if (argc != 2)
    {
        printf("Correct usage: ./recover FILE\n");
        return 1;
    }
    // Open memory card
    FILE *src = fopen(argv[1], "r");
    if (src == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    uint8_t buffer[512];
    // While stil have data to read
    int counter = 0;
    FILE *img = NULL;
    while (fread(buffer, 512, 1, src) != 0)
    {
        // If it is a JPG File
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0))
        // Create JPEG
        {
            if (img != NULL)
            {
                fclose(img);
            }
            char *filename = malloc(8);
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            free(filename);
            if (img == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }
            fwrite(buffer, 512, 1, img);
            counter++;
        }
        else if (img != NULL)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(src);
}
