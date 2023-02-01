#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            double grey = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            grey = round(grey/3);
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {   int sepiablue= 0;
            int sepiared= 0;
            int sepiagreen = 0;
            //checking RED
            if(round((float)0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue) > 255)
            {
                sepiared = 255;
            }
            else
            {
                sepiared = round((float)0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            }
            //cheking GREEN
            if(round((float)0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue) > 255)
            {
                sepiagreen = 255;
            }
            else
            {
                sepiagreen = round((float)0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            }
            //cheking BLUE
            if(round((float)0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue) > 255)
            {
                sepiablue = 255;
            }
            else
            {
                sepiablue = round((float)0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            }
            image[i][j].rgbtRed = sepiared;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtBlue = sepiablue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < ceil(width/2); j++)
        {
        int opposite = width - 1 - j;
        RGBTRIPLE temp;
        temp = image[i][opposite];
        image[i][opposite] = image[i][j];
        image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];      //creating copy
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width;j++)
        {
            int blue = 0;
            int red = 0;
            int green = 0;
            int count = 0;
            for(int k = - 1; k < 2; k ++)
            {
                for(int l = - 1; l < 2; l++)
                {
                    if(((i + k < height) && (i + k >= 0)) && ((j + l < width)&&(j + l >= 0)))
                    {
                        blue += copy[i + k][j + l].rgbtBlue;
                        red += copy[i + k][j + l].rgbtRed;
                        green += copy[i + k][j + l].rgbtGreen;
                        count++;
                    }
                }
            }
        image[i][j].rgbtBlue = round((float)blue/count);
        image[i][j].rgbtRed = round((float)red/count);
        image[i][j].rgbtGreen = round((float)green/count);
        }
    }
    return;
}
