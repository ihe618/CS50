#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //size restriction
    int n;
    do 
    {
     n = get_int ("Size:");
    }
    while (n<1 || n>8);
    //prints pyramid
    for(int i=1; i<=n; i++)
    {
     for(int j=1; j <= n-i; j++)
        {
            printf(" ");
        }
            for(int j=1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
