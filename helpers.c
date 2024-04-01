#include "helpers.h"
#include <math.h>
int roundoff(float num)
{
    if (num < 255)
    {
        float decimal = num - (int)num;
        if (decimal != 0.0 && decimal > 0.5)
        {
            return (int)num + 1;
        }
        else
        {
            return (int)num;
        }
    }
    else
    {
        return 255;
    }
}

int gx[3][3] = {{-1, 0, 1},
              {-2, 0, 2},
              {-1, 0, 1}};

int gy[3][3] = {{-1, -2, -1},
               {0, 0, 0},
               {1, 2, 1}};


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
     for (int i=0; i<height; i++)
     {
        for (int j=0; j<width; j++)
        {
            float avg = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen +image[i][j].rgbtRed)/3;
            image[i][j].rgbtBlue = roundoff(avg);
            image[i][j].rgbtGreen = roundoff(avg);
            image[i][j].rgbtRed = roundoff(avg);
        }
     }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
      for (int i=0; i<height; i++)
     {
        for (int j=0; j<width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = temp;
        }
     }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i=0; i<height; i++)
    {
        for (int j=0;j<width; j++)
        {
            int sumr = 0;
            int sumb = 0;
            int sumg = 0;
            int count = 0;
            for (int k=-1; k<2; k++)
            {
                if(i+k<0 || i+k >height-1)
                {
                    continue;
                }
                for (int l=-1; l<2; l++)
                {
                    if(j+l<0 || j+l>width-1)
                {
                    continue;
                }
                sumr += image[i+k][j+l].rgbtRed;
                sumb += image[i+k][j+l].rgbtBlue;
                sumg += image[i+k][j+l].rgbtGreen;
                count++;
                }
            }

            temp[i][j].rgbtRed = round(sumr/(float)count);
            temp[i][j].rgbtBlue = round(sumb/(float)count);
            temp[i][j].rgbtGreen = round(sumg/(float)count);
        }
    }
     for (int i=0; i<height; i++)
    {
        for (int j=0;j<width; j++)
        {
            image[i][j]= temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];
    for (int i=0; i<height; i++)
    {
        for (int j=0;j<width; j++)
        {
            int sum_rx = 0, sum_bx = 0, sum_gx = 0;
            int sum_ry = 0, sum_by = 0, sum_gy = 0;
             for (int k=0; k<3; k++)
            {
                for (int l=0; l<3; l++)
                {
                    if(i+k-1<0 || i+k-1 >height-1 || j+l-1<0 || j+l-1>width-1)
                {
                    continue;
                }
                 sum_rx += image[i+k-1][j+l-1].rgbtRed * gx[k][l];
                 sum_ry += image[i+k-1][j+l-1].rgbtRed * gy[k][l];
                 sum_bx += image[i+k-1][j+l-1].rgbtBlue * gx[k][l];
                 sum_by += image[i+k-1][j+l-1].rgbtBlue * gy[k][l];
                 sum_gx += image[i+k-1][j+l-1].rgbtGreen * gx[k][l];
                 sum_gy += image[i+k-1][j+l-1].rgbtGreen * gy[k][l];
                }
            }
            float avgr = sqrt(pow(sum_rx, 2) + pow(sum_ry, 2));
            temp[i][j].rgbtRed = roundoff(avgr);

            float avgb = sqrt(pow(sum_bx, 2) + pow(sum_by, 2));
            temp[i][j].rgbtBlue = roundoff(avgb);

            float avgg = sqrt(pow(sum_gx, 2) + pow(sum_gy, 2));
            temp[i][j].rgbtGreen = roundoff(avgg);

        }
    }
    for (int i=0; i<height; i++)
    {
        for (int j=0;j<width; j++)
        {
            image[i][j]= temp[i][j];
        }
    }
    return;

}
