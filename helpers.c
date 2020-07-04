#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)                        // Rows
    {
        for (int j = 0; j < width; j++)                     // Columns
        {
            // So long RGB values equal- shades of gray
            // Calculate averages of each pixel, and set the RGB to average
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.000);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)                        // Rows
    {
        for (int j = 0; j < width; j++)                     // Columns
        {

            // Carry out sepia calculations (round to integers)
            int SR = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int SG = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int SB = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Red
            if (SR > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = SR;
            }

            // Green
            if (SG > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = SG;
            }

            //Blue
            if (SB > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = SB;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)                        // Rows
    {
        for (int j = 0; j < width / 2; j++)                 // Columns - swap addresses from left half with right half
        {
            int *tempRed = malloc(sizeof(BYTE));
            *tempRed = image[i][j].rgbtRed;
            * &image[i][j].rgbtRed = * &image[i][width - 1 - j].rgbtRed;
            * &image[i][width - 1 - j].rgbtRed = *tempRed;

            int *tempGreen = malloc(sizeof(BYTE));
            *tempGreen = image[i][j].rgbtGreen;
            * &image[i][j].rgbtGreen = * &image[i][width - 1 - j].rgbtGreen;
            * &image[i][width - 1 - j].rgbtGreen = *tempGreen;

            int *tempBlue = malloc(sizeof(BYTE));
            *tempBlue = image[i][j].rgbtBlue;
            * &image[i][j].rgbtBlue = * &image[i][width - 1 - j].rgbtBlue;
            * &image[i][width - 1 - j].rgbtBlue = *tempBlue;

            free(tempRed);
            free(tempGreen);
            free(tempBlue);
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create addresses temporarily to store old values
    int *tempRed[height][width];
    int *tempGreen[height][width];
    int *tempBlue[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempRed[i][j] = malloc(sizeof(BYTE));
            tempGreen[i][j] = malloc(sizeof(BYTE));
            tempBlue[i][j] = malloc(sizeof(BYTE));
            *tempRed[i][j] = image[i][j].rgbtRed;
            *tempGreen[i][j] = image[i][j].rgbtGreen;
            *tempBlue[i][j] = image[i][j].rgbtBlue;
        }
    }

    // NON-EDGE CASES
    for (int i = 1; i < height - 1; i++)                    // Rows
    {
        for (int j = 1; j < width - 1; j++)                 // Columns
        {
            int Red = 0;
            int Green = 0;
            int Blue = 0;
            for (int a = i - 1; a <= i + 1; a++)
            {
                for (int b = j - 1; b <= j + 1; b++)
                {
                    Red = Red + *tempRed[a][b];
                    Green = Green + *tempGreen[a][b];
                    Blue = Blue + *tempBlue[a][b];
                }
            }
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtBlue = Blue;
        }
    }

    // EDGE, NON-CORNER
    // Row 0
    for (int i = 1; i < width - 1; i++)                     // For columns 1 to width - 1
    {
        int Red = 0;
        int Green = 0;
        int Blue = 0;
        for (int a = 0; a < 2; a++)                         // Row 0 and 1
        {
            for (int b = i - 1; b <= i + 1; b++)            // Adjacent columns
            {
                Red = Red + *tempRed[a][b];            // Sum of adjacent column values in adjacent rows
                Green = Green + *tempGreen[a][b];
                Blue = Blue + *tempBlue[a][b];
            }
        }
        image[0][i].rgbtRed = round(Red / 6.000);              // Average of adjacent values for each color
        image[0][i].rgbtGreen = round(Green / 6.000);
        image[0][i].rgbtBlue = round(Blue / 6.000);
    }
    // Row height - 1 (bottom row)
    for (int i = 1; i < width - 1; i++)                     // For columns 1 to width - 1
    {
        int Red = 0;
        int Green = 0;
        int Blue = 0;
        for (int a = height - 2; a < height; a++)           // Bottom 2 rows
        {
            for (int b = i - 1; b <= i + 1; b++)            // Adjacent columns
            {
                Red = Red + *tempRed[a][b];            // Sum of adjacent column values in adjacent rows
                Green = Green + *tempGreen[a][b];
                Blue = Blue + *tempBlue[a][b];
            }
        }
        image[height - 1][i].rgbtRed = round(Red / 6.000);      // Average of adjacent values for each color
        image[height - 1][i].rgbtGreen = round(Green / 6.000);
        image[height - 1][i].rgbtBlue = round(Blue / 6.000);
    }
    // Column 0
    for (int i = 1; i < height - 1; i++)                    // For rows 1 to height - 1
    {
        int Red = 0;
        int Green = 0;
        int Blue = 0;
        for (int a = 0; a < 2; a++)                         // Column 0 and 1
        {
            for (int b = i - 1; b <= i + 1; b++)            // Adjacent rows
            {
                Red = Red + *tempRed[b][a];            // Sum of adjacent column values in adjacent rows
                Green = Green + *tempGreen[b][a];
                Blue = Blue + *tempBlue[b][a];
            }
        }
        image[i][0].rgbtRed = round(Red / 6.000);               // Average of adjacent values for each color
        image[i][0].rgbtGreen = round(Green / 6.000);
        image[i][0].rgbtBlue = round(Blue / 6.000);
    }
    // Column width - 1 (right most column)
    for (int i = 1; i < height - 1; i++)                    // For rows 1 to height - 1
    {
        int Red = 0;
        int Green = 0;
        int Blue = 0;
        for (int a = width - 2; a < width; a++)             // Right most 2 columns
        {
            for (int b = i - 1; b <= i + 1; b++)            // Adjacent rows
            {
                Red = Red + *tempRed[b][a];            // Sum of adjacent column values in adjacent rows
                Green = Green + *tempGreen[b][a];
                Blue = Blue + *tempBlue[b][a];
            }
        }
        image[i][width - 1].rgbtRed = round(Red / 6.000);       // Average of adjacent values for each color
        image[i][width - 1].rgbtGreen = round(Green / 6.000);
        image[i][width - 1].rgbtBlue = round(Blue / 6.000);
    }

    // CORNER PIECES
    // Image [0][0] - top left corner
    int Red = 0;
    int Green = 0;
    int Blue = 0;
    for (int a = 0; a < 2; a++)
    {
        for (int b = 0; b < 2; b++)
        {
            Red = Red + *tempRed[a][b];
            Green = Green + *tempGreen[a][b];
            Blue = Blue + *tempBlue[a][b];
        }
    }
    image[0][0].rgbtRed = round(Red / 4.000);                   // Average of adjacent values for each color
    image[0][0].rgbtGreen = round(Green / 4.000);
    image[0][0].rgbtBlue = round(Blue / 4.000);


    // Image[height-1][0]- bottom left corner
    Red = 0;
    Green = 0;
    Blue = 0;
    for (int a = height - 2; a < height; a++)               // Bottom 2 row
    {
        for (int b = 0; b < 2; b++)                         // First 2 columns
        {
            Red = Red + *tempRed[a][b];
            Green = Green + *tempGreen[a][b];
            Blue = Blue + *tempBlue[a][b];
        }
    }
    image[height - 1][0].rgbtRed = round(Red / 4.000);          // Average of adjacent values for each color
    image[height - 1][0].rgbtGreen = round(Green / 4.000);
    image[height - 1][0].rgbtBlue = round(Blue / 4.000);

    // Image[0][width-1] - top right corner corner
    Red = 0;
    Green = 0;
    Blue = 0;
    for (int a = 0; a < 2; a++)                             // Top 2 rows
    {
        for (int b = width - 2; b < width; b++)             // Right most 2 columns
        {
            Red = Red + *tempRed[a][b];
            Green = Green + *tempGreen[a][b];
            Blue = Blue + *tempBlue[a][b];
        }
    }
    image[0][width - 1].rgbtRed = round(Red / 4.000);           // Average of adjacent values for each color
    image[0][width - 1].rgbtGreen = round(Green / 4.000);
    image[0][width - 1].rgbtBlue = round(Blue / 4.000);

    // Image[height-1][width-1] - bottom right
    Red = 0;
    Green = 0;
    Blue = 0;
    for (int a = height - 2; a < height; a++)               // Bottom 2 rows
    {
        for (int b = width - 2; b < width; b++)             // Right most 2 columns
        {
            Red = Red + *tempRed[a][b];
            Green = Green + *tempGreen[a][b];
            Blue = Blue + *tempBlue[a][b];
        }
    }
    image[height - 1][width - 1].rgbtRed = round(Red / 4.000);  // Average of adjacent values for each color
    image[height - 1][width - 1].rgbtGreen = round(Green / 4.000);
    image[height - 1][width - 1].rgbtBlue = round(Blue / 4.000);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            free(tempRed[i][j]);
            free(tempGreen[i][j]);
            free(tempBlue[i][j]);
        }
    }

    return;
}

