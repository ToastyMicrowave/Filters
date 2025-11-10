#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{


    RGBTRIPLE *temp = malloc(sizeof(RGBTRIPLE));

    if (temp == NULL)
        return;
    for (int i = 0; i < height; i++)
    {


        for (int j = 0; j < width / 2; j++)
        {
            *temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = *temp;
        }
    }
    free(temp);

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    const int KERNEL_SIZE = 3;
    int avg_red, avg_green, avg_blue, pixel_count;
    // Copy image
    RGBTRIPLE (*cpimg)[width] = malloc(height * width * sizeof(RGBTRIPLE));
    if (cpimg == NULL) {return;};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cpimg[i][j] = image[i][j];
        }
    }

    // Blur image
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            // cvbtuy790===
            pixel_count = avg_red = avg_green = avg_blue = 0;
            for (int k = i - KERNEL_SIZE; k <= i + KERNEL_SIZE; k++)
            {
                for (int l = j - KERNEL_SIZE; l <= j + KERNEL_SIZE; l++)
                {
                    if (!(k < 0 || k >= height || l < 0 || l >= width))
                        {
                            avg_red += cpimg[k][l].rgbtRed;
                            avg_green += cpimg[k][l].rgbtGreen;
                            avg_blue += cpimg[k][l].rgbtBlue;
                            pixel_count++;
                        }
                }
            }
            image[i][j].rgbtRed = round((float)avg_red / pixel_count);
            image[i][j].rgbtGreen = round((float)avg_green / pixel_count);
            image[i][j].rgbtBlue = round((float)avg_blue / pixel_count);
        }
    }
    free(cpimg);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy image
    RGBTRIPLE (*cpimg)[width] = malloc(height * width * sizeof(RGBTRIPLE));
    if (cpimg == NULL) {return;};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cpimg[i][j] = image[i][j];
        }
    }

    int GxR, GxG, GxB, GyR, GyG, GyB, Gx_val, Gy_val;
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            GxR = GxG = GxB = GyR = GyG = GyB = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (!(k < 0 || k >= height || l < 0 || l >= width))
                    {
                        Gx_val = Gx[k - i + 1][l - j + 1];
                        Gy_val = Gy[k - i + 1][l - j + 1];

                        GxR += Gx_val * cpimg[k][l].rgbtRed;
                        GxG += Gx_val * cpimg[k][l].rgbtGreen;
                        GxB += Gx_val * cpimg[k][l].rgbtBlue;
                        GyR += Gy_val * cpimg[k][l].rgbtRed;
                        GyG += Gy_val * cpimg[k][l].rgbtGreen;
                        GyB += Gy_val * cpimg[k][l].rgbtBlue;
                    }
                }
            }

            int RED = round(sqrt(pow(GxR, 2) + pow(GyR, 2)));
            int GREEN = round(sqrt(pow(GxG, 2) + pow(GyG, 2)));
            int BLUE = round(sqrt(pow(GxB, 2) + pow(GyB, 2)));

            if (RED > 255)
            {
                RED = 255;
            }
            if (GREEN > 255)
            {
                GREEN = 255;
            }
            if (BLUE > 255)
            {
                BLUE = 255;
            }

            image[i][j].rgbtRed = RED;
            image[i][j].rgbtGreen = GREEN;
            image[i][j].rgbtBlue = BLUE;
        }
    }
    free(cpimg);
    return;
}
