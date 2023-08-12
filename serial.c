#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int countSurrounding(bool **grid, int x, int y, int w, int h)
{
    int count = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            // if (i >= 0 && i < w && j >= 0 && j < h)
            // {
            //     if (grid[i][j])
            //     {
            //         count++;
            //     }
            // }
            // else if (i < 0 || i >= w || j < 0 || j >= h)
            // {
            if (grid[(i + w) % w][(j + h) % h])
            {
                count++;
            }
            // }
            if (i == x && j == y)
            {
                if (grid[i][j])
                {
                    count--;
                }
            }
        }
    }
    return count;
}

void printGrid(bool **grid, int w, int h)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (grid[i][j])
            {
                printf("#");
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main()
{
    int w, h, n, m, a, b, c;
    char buffer[128000];
    bool **grid, **grid2;

    // FILE *finput = fopen("1.in", "r");

    // if (finput == NULL)
    // {
    //     printf("Could not open input\n");
    //     return 1;
    // }

    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d %d %d %d %d %d %d", &w, &h, &n, &m, &a, &b, &c);

    grid = (bool **)malloc(h * sizeof(bool *));
    grid2 = (bool **)malloc(h * sizeof(bool *));
    for (int i = 0; i < h; i++)
    {
        grid[i] = (bool *)malloc(w * sizeof(bool));
        grid2[i] = (bool *)malloc(w * sizeof(bool));
    }

    for (int i = 0; i < h; i++)
    {
        fgets(buffer, sizeof(buffer), stdin);
        for (int j = 0; j < w; j++)
        {
            grid[i][j] = (buffer[j] == '#');
        }
    }

    for (int i = 0; i < n; i++)
    {

        if (i % m == 0 && i != 0 || i == 1)
        {
            printGrid(grid, w, h);
        }

        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < w; k++)
            {
                int count = countSurrounding(grid, j, k, w, h);
                if (grid[j][k])
                {
                    if (count < a || count > b)
                    {
                        grid2[j][k] = false;
                    }
                    else
                    {
                        grid2[j][k] = true;
                    }
                }
                else
                {
                    if (count == c)
                    {
                        grid2[j][k] = true;
                    }
                    else
                    {
                        grid2[j][k] = false;
                    }
                }
            }
        }

        bool **temp = grid;
        grid = grid2;
        grid2 = temp;
    }
    printGrid(grid, w, h);

    // fclose(finput);

    for (int i = 0; i < h; i++)
    {
        free(grid[i]);
        free(grid2[i]);
    }
    free(grid);
    free(grid2);

    return 0;
}