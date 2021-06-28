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

            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    if (i - 1 + a < 0 || i - 1 + a > height - 1 || j - 1 + b < 0 || j - 1 + b > width - 1)
                    {
                        continue;
                    }

                    sum_r += image[i - 1 + a][j - 1 + b].rgbtRed;
                    sum_g += image[i - 1 + a][j - 1 + b].rgbtGreen;
                    sum_b += image[i - 1 + a][j - 1 + b].rgbtBlue;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int Redx, Greenx, Bluex, Redy, Greeny, Bluey;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Redx = Greenx = Bluex = Redy = Greeny = Bluey = 0;

            // loop through the pixels 1 row and 1 column from the pixel
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    if (i - 1 + a < 0 || i - 1 + a > height - 1 || j - 1 + b < 0 || j - 1 + b > width - 1)
                    {
                        continue;
                    }

                    // calculate Gx
                    Redx += image[i - 1 + a][j - 1 + b].rgbtRed * Gx[a][b];
                    Greenx += image[i - 1 + a][j - 1 + b].rgbtGreen * Gx[a][b];
                    Bluex += image[i - 1 + a][j - 1 + b].rgbtBlue * Gx[a][b];

                    // calculate Gy
                    Redy += image[i - 1 + a][j - 1 + b].rgbtRed * Gy[a][b];
                    Greeny += image[i - 1 + a][j - 1 + b].rgbtGreen * Gy[a][b];
                    Bluey += image[i - 1 + a][j - 1 + b].rgbtBlue * Gy[a][b];
                }
            }

            // calculate and set values
            int red = round(sqrt((Redx * Redx) + (Redy * Redy)));
            int blue = round(sqrt((Bluex * Bluex) + (Bluey * Bluey)));
            int green = round(sqrt((Greenx * Greenx) + (Greeny * Greeny)));


            new_image[i][j].rgbtRed = (red <= 255) ? red : 255;
            new_image[i][j].rgbtBlue = (blue <= 255) ? blue : 255;
            new_image[i][j].rgbtGreen = (green <= 255) ? green : 255;

        }
    }

    // overwrite on image from new_image
    for (int n = 0; n < height; n++)
    {
        for (int l = 0; l < width; l++)
        {
            image[n][l] = new_image[n][l];
        }
    }
    return;
}