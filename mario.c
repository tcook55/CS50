#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1);
    int ctr = 1;
    for (int i = 0; i < h; i++)
    {
        int dots = h - ctr;
        for (int j = 0; j < dots; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < ctr; j++)
        {
            printf("#");
        }
        printf("\n");
        ctr++;
    }

}
