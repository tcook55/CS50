#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int m = 0; m < width; m++)
        {
            //Take average of RGB values per cell and apply them to each value to make gray levels
            int avg = round(((float)(image[i][m].rgbtBlue + image[i][m].rgbtGreen + image[i][m].rgbtRed) / 3));
            //avg = round(avg);
            image[i][m].rgbtBlue = avg;
            image[i][m].rgbtGreen = avg;
            image[i][m].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int m = 0; m < width; m++)
        {
            //Make Sepia calculation for R, G, and B
            float sepiaRed = .393 * image[i][m].rgbtRed + .769 * image[i][m].rgbtGreen + .189 * image[i][m].rgbtBlue;
            float sepiaGreen = .349 * image[i][m].rgbtRed + .686 * image[i][m].rgbtGreen + .168 * image[i][m].rgbtBlue;
            float sepiaBlue = .272 * image[i][m].rgbtRed + .534 * image[i][m].rgbtGreen + .131 * image[i][m].rgbtBlue;
            
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
            //Round because colors have to be integers
            image[i][m].rgbtRed = round(sepiaRed);
            image[i][m].rgbtGreen = round(sepiaGreen);
            image[i][m].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int center = round((float)width / 2);
    for (int i = 0; i < height; i++)
    {
        for (int m = 0; m < center; m++)
        {
            //Iterate across half the image and swap cells from both sides of image.
            RGBTRIPLE tmp = image[i][width - m - 1];
            image[i][width - m - 1] = image[i][m];
            image[i][m] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create new image array to store new values
    RGBTRIPLE new_im[height][width];
    //Iterate through original image
    for (int i = 0; i < height; i++)
    {
        for (int m = 0; m < width; m++)
        {
            int count = 0;
            int avgR = 0;
            int avgG = 0;
            int avgB = 0;
            
            //Iterate around pixel we want to blur and collect averages
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int j = m - 1; j <= m + 1; j++)
                {
                    if (j < width && j >= 0 && k < height && k >= 0)
                    {
                        avgR += image[k][j].rgbtRed;
                        avgG += image[k][j].rgbtGreen;
                        avgB += image[k][j].rgbtBlue;
                        count += 1;
                    }
                }
            }
            //calculate averages for new pixel value
            avgR = round((float)avgR / count);
            avgG = round((float)avgG / count);
            avgB = round((float)avgB / count);
            //Store new pixel values in temporary image array
            new_im[i][m].rgbtRed = avgR;
            new_im[i][m].rgbtGreen = avgG;
            new_im[i][m].rgbtBlue = avgB;
        }
    }
    //Apply new pixel values from temporary image to original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = new_im[i][j].rgbtRed;
            image[i][j].rgbtGreen = new_im[i][j].rgbtGreen;
            image[i][j].rgbtBlue = new_im[i][j].rgbtBlue;
        }
    }
    return;
}
