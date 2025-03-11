#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (int) round(
                (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = (int) round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                       0.189 * image[i][j].rgbtBlue);
            int sepiaGreen =
                (int) round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                            0.168 * image[i][j].rgbtBlue);
            int sepiaBlue =
                (int) round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                            0.131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;

            image[i][width - j - 1].rgbtRed = temp[i][j].rgbtRed;
            image[i][width - j - 1].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][width - j - 1].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
            float totalRed = 0, totalGreen = 0, totalBlue = 0, counter = 0;
            for (int updatedI = i - 1; updatedI < i + 2; updatedI++)
            {
                for (int updatedJ = j - 1; updatedJ < j + 2; updatedJ++)
                {
                    if (updatedI >= 0 && updatedJ >= 0 && updatedI < height && updatedJ < width)
                    {
                        totalRed += image[updatedI][updatedJ].rgbtRed;
                        totalGreen += image[updatedI][updatedJ].rgbtGreen;
                        totalBlue += image[updatedI][updatedJ].rgbtBlue;
                        counter++;
                    }
                }
            }
            copy[i][j].rgbtRed = (round) (totalRed / counter);
            copy[i][j].rgbtGreen = (round) (totalGreen / counter);
            copy[i][j].rgbtBlue = (round) (totalBlue / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
