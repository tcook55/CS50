#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float n;
    do
    {
    n = get_float("Change owed: ");
    }
    while(n < 0);
    int cents = round(n * 100);
    int coins = 0;

    for (;cents >= 25;)
    {
    cents = cents - 25;
    coins++;
    }
    
    for (;cents >= 10;)
    {
    cents = cents - 10;
    coins++;
    }
    
    for (;cents >= 5;)
    {
    cents = cents - 5;
    coins++;
    }

    for (;cents >= 1;)
    {
    cents = cents - 1;
    coins++;
    }
    printf("Coins: ");
    printf("%d", coins);
    printf("\n");
}
