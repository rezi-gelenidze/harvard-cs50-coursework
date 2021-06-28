#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculating an average value and assigning each color
            // value to it to get shades of grayscale
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int ORed, OGreen, OBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calcuating sepia color value for each color.
            // if calculated number is more than 255, it is assigned to 255 (MAX value of RGB)
            // else it is assigned calculated value
            ORed = image[i][j].rgbtRed;
            OGreen = image[i][j].rgbtGreen;
            OBlue = image[i][j].rgbtBlue;

            int sepiared = round(0.393 * ORed + 0.769 * OGreen + 0.189 * OBlue);
            image[i][j].rgbtRed = (sepiared > 255) ? 255 : sepiared;

            int sepiagreen = round(0.349 * ORed + 0.686 * OGreen + 0.168 * OBlue);
            image[i][j].rgbtGreen = (sepiagreen > 255) ? 255 : sepiagreen;

            int sepiablue = round(0.272 * ORed + 0.534 * OGreen + 0.131 * OBlue);
            image[i][j].rgbtBlue = (sepiablue > 255) ? 255 : sepiablue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *first = &image[i][j];
            RGBTRIPLE *last = &image[i][width - (j + 1)];

            // swapping first and last RGBTRIPLES (pixels)
            RGBTRIPLE temp = *first;
            *first = *last;
            *last = temp;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float n, sum_r, sum_g, sum_b;

    RGBTRIPLE blur[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            n = 0;
            sum_r = 0;
            sum_g = 0;
            sum_b = 0;

            sum_r += image[i][j].rgbtRed;
            sum_g += image[i][j].rgbtGreen;
            sum_b += image[i][j].rgbtBlue;
            n++;

            // next pixel
            if (j != (width - 1))
            {
                sum_r += image[i][j + 1].rgbtRed;
                sum_g += image[i][j + 1].rgbtGreen;
                sum_b += image[i][j + 1].rgbtBlue;
                n++;
            }
            // previous pixel
            if (j != 0)
            {
                sum_r += image[i][j - 1].rgbtRed;
                sum_g += image[i][j - 1].rgbtGreen;
                sum_b += image[i][j - 1].rgbtBlue;
                n++;
            }
            // upper
            if (i != 0)
            {
                // upper middle
                sum_r += image[i - 1][j].rgbtRed;
                sum_g += image[i - 1][j].rgbtGreen;
                sum_b += image[i - 1][j].rgbtBlue;
                n++;

                // upper next
                if (j != width - 1)
                {
                    sum_r += image[i - 1][j + 1].rgbtRed;
                    sum_g += image[i - 1][j + 1].rgbtGreen;
                    sum_b += image[i - 1][j + 1].rgbtBlue;
                    n++;
                }
                // upper previous
                if (j != 0)
                {
                    sum_r += image[i - 1][j - 1].rgbtRed;
                    sum_g += image[i - 1][j - 1].rgbtGreen;
                    sum_b += image[i - 1][j - 1].rgbtBlue;
                    n++;
                }
            }

            // down
            if (i != (height - 1))
            {
                // down middle
                sum_r += image[i + 1][j].rgbtRed;
                sum_g += image[i + 1][j].rgbtGreen;
                sum_b += image[i + 1][j].rgbtBlue;
                n++;

                // down next
                if (j != width - 1)
                {
                    sum_r += image[i + 1][j + 1].rgbtRed;
                    sum_g += image[i + 1][j + 1].rgbtGreen;
                    sum_b += image[i + 1][j + 1].rgbtBlue;
                    n++;
                }

                // down previous
                if (j != 0)
                {
                    sum_r += image[i + 1][j - 1].rgbtRed;
                    sum_g += image[i + 1][j - 1].rgbtGreen;
                    sum_b += image[i + 1][j - 1].rgbtBlue;
                    n++;
                }
            }

            // calculating and setting an average value
            blur[i][j].rgbtRed = round(sum_r / n);
            blur[i][j].rgbtGreen = round(sum_g / n);
            blur[i][j].rgbtBlue = round(sum_b / n);

        }
    }

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b] = blur[a][b];

        }
    }

    return;
}
