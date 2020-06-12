#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //command-line arguments

    //if none or more than 1 command argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //if key not 26 characters
    int n = strlen(argv[1]);
    if (n != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //if key contains non-alphabetic characters
    int l = 0;
    for (int i = 0; i < 26; i++)
    {
        if (((int)argv[1][i] < 65 || (int)argv[1][i] > 90) && ((int)argv[1][i] < 97 || (int)argv[1][i] > 122))
        {
            l++;
        }
    }
    if (l > 0)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //if key contains duplicate characters
    int r = 0;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < i; j++)                             //for each ith character, compare with all previous characters for dup
        {
            if (argv[1][i] == argv[1][j])
            {
                r++;
            }
        }
    }
    if (r > 0)
    {
        printf("Usage: ./substitution key", r);
        return 1;
    }

    //assuming command-line arguments correct
    string t = get_string("plaintext: ");                       //prompt for plaintext
    printf("ciphertext: ");
    int m = strlen(t);
    for (int i = 0; i < m; i++)
    {
        if ((int)t[i] > 96 && (int)t[i] < 123)                  //if plaintext digit i is lowercase letter
        {
            printf("%c", tolower(argv[1][(int)t[i] - 97]));
        }
        else if ((int)t[i] > 64 && (int)t[i] < 91)              //if plaintext digit i is uppercase letter
        {
            printf("%c", toupper(argv[1][(int)t[i] - 65]));
        }
        else                                                    //otherwise, if plaintext digit is not letter
        {
            printf("%c", t[i]);
        }
    }
    printf("\n");
    return 0;
}