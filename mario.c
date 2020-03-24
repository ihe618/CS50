#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //set restrictions
    int n;
    do
    {
        n = get_int("Size: /n");
    }
    while (n < 1 || n > 8);
    //Row iternation
    for (int i = 1; i <= n; i++)
    {
        //Left side
        for (int j = 1; j <= n - i; j++)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf(" ");
        //Right side
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
