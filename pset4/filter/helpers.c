#include "helpers.h"
#include<stdio.h>
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // RGB Triple vlaues to one integer
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;

            float average_raw = (float)(b + g + r) / 3;
            int average = round(average_raw);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // int sepiaRed = round(.393 * image[0][0].rgbtRed + .769 * image[0][0].rgbtGreen + .189 * image[0][0].rgbtBlue);
    // int sepiaGreen = round(.349 * image[0][0].rgbtRed + .686 * image[0][0].rgbtGreen + .168 * image[0][0].rgbtBlue);
    // int sepiaBlue = round(.272 * image[0][0].rgbtRed + .534 * image[0][0].rgbtGreen + .131 * image[0][0].rgbtBlue);
    // printf("%i %i %i", sepiaRed, sepiaGreen, sepiaBlue);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE tmpImage = image[i][j];
            int k = width - (j + 1);
            image[i][j] = image[i][k];
            image[i][k] = tmpImage;
        }
    }
    return;
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
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total_red, total_green, total_blue;
            float counter;
            total_red = total_green = total_blue =  counter = 0;

            // top corner left
            if (i >= 0 && j >= 0)
            {
                total_red += copy[i][j].rgbtRed;
                total_green += copy[i][j].rgbtGreen;
                total_blue += copy[i][j].rgbtBlue;
                counter++;
            }

            // top corner right
            if (i >= 0 && j - 1 >= 0)
            {
                total_red += copy[i][j - 1].rgbtRed;
                total_green += copy[i][j - 1].rgbtGreen;
                total_blue += copy[i][j - 1].rgbtBlue;
                counter++;
            }

            // bottom corner left
            if (i - 1 >= 0 && j >= 0)
            {
                total_red += copy[i - 1][j].rgbtRed;
                total_green += copy[i - 1][j].rgbtGreen;
                total_blue += copy[i - 1][j].rgbtBlue;
                counter++;
            }

            //bottoom corner right
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                total_red += copy[i - 1][j - 1].rgbtRed;
                total_green += copy[i - 1][j - 1].rgbtGreen;
                total_blue += copy[i - 1][j - 1].rgbtBlue;
                counter++;
            }

            // top middle edge
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                total_red += copy[i][j + 1].rgbtRed;
                total_green += copy[i][j + 1].rgbtGreen;
                total_blue += copy[i][j + 1].rgbtBlue;
                counter++;
            }

            // bottom middle edge
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                total_red += copy[i - 1][j + 1].rgbtRed;
                total_green += copy[i - 1][j + 1].rgbtGreen;
                total_blue += copy[i - 1][j + 1].rgbtBlue;
                counter++;
            }

            // left middle edge
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                total_red += copy[i + 1][j].rgbtRed;
                total_green += copy[i + 1][j].rgbtGreen;
                total_blue += copy[i + 1][j].rgbtBlue;
                counter++;
            }

            //  right middle edges
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                total_red += copy[i + 1][j - 1].rgbtRed;
                total_green += copy[i + 1][j - 1].rgbtGreen;
                total_blue += copy[i + 1][j - 1].rgbtBlue;
                counter++;
            }

            // middles
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                total_red += copy[i + 1][j + 1].rgbtRed;
                total_green += copy[i + 1][j + 1].rgbtGreen;
                total_blue += copy[i + 1][j + 1].rgbtBlue;
                counter++;
            }

            //averaging all color values
            image[i][j].rgbtRed = round(total_red / counter);
            image[i][j].rgbtGreen = round(total_green / counter);
            image[i][j].rgbtBlue = round(total_blue / counter);

        }
    }

    return;
}

