#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

int main()
{
    int n; //number of known data points
    float w; //point in which we want to estimate the function
    float pw; //polynomial at w
    float *x = NULL, *y = NULL; //arrays of known data points coordinates
    float **f = NULL; //array of divided differences
    float product = 1;
    int i, j, go = 1; //counters
    FILE *p = NULL;
    //open input file
    p = fopen("input.txt", "r");
    if (!p)
    {
        printf("input file couldn't be open\n");
        exit(1);
    }
    //read the number of known data points
    fscanf(p, "%d", &n);
    if (n <= 0)
    {
        printf("invalid data\n");
        exit(2);
    }
    //allocate memory for the arrays
    x = (float*)malloc(n * sizeof(float));
    y = (float*)malloc(n * sizeof(float));
    f = (float**)malloc((n - 1) * sizeof(float*));
    if (!x || !y || !f)
    {
        printf("memory allocation error\n");
        exit(3);
    }
    for (i = 0; i < n - 1; i++)
    {
        f[i] = (float*)malloc((n - 1) * sizeof(float));
        if (!f[i])
        {
            printf("memory allocation error\n");
            exit(3);
        }
    }
    //read х coordinates of known data points
    for (i = 0; i < n; i++)
    {
        fscanf(p, "%f", &x[i]);
    }
    //read y coordinates of known data points
    for (i = 0; i < n; i++)
    {
        fscanf(p, "%f", &y[i]);
    }
    printf("POLYNOMIAL INTERPOLATION\n");
    while (go == 1)
    {
        //enter w
        printf("enter x*: ");
        scanf("%f", &w);
        //calculate the divided differences
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - 1 - i; j++)
            {
                if (i == 0)
                {
                    f[i][j] = (y[j + 1] - y[j]) / (x[j + 1] - x[j]);
                }
                else
                {
                    f[i][j] = (f[i - 1][j + 1] - f[i - 1][j]) / (x[j + i + 1] - x[j]);
                }
            }
        }
        //calculate the polynomial at w
        if (fabs(x[0] - w) < fabs(x[n - 1] - w))
        {
            //Newton forward divided difference formula
            pw = y[0];
            for (i = 0; i < n - 1; i++)
            {
                product *= w - x[i];
                pw += f[i][0] * product;
            }
        }
        else
        {
            //Newton backward divided difference formula
            pw = y[n - 1];
            for (i = 0; i < n - 1; i++)
            {
                product *= w - x[n - 1 - i];
                pw += f[i][n - 2 - i] * product;
            }
        }
        //print results
        printf("P(%.4f) = %.4f\n", w, pw);
        printf("continue? (1 - yes, 0 - no)\n");
        scanf("%d", &go);
    }
    //free the memory
    free(x);
    free(y);
    for (i = 0; i < n - 1; i++)
    {
        free(f[i]);
    }
    free(f);
    return 0;
}
