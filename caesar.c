#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //command-line arguments

    if (argc != 2)                                                      //if none or more than 1 command argument
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int n = strlen(argv[1]);
    for (int i = 0; i < n; i++)
    {
        if (argv[1][i] < 48 || argv[1][i] > 57)                          //if all digits of command argument are not decimal numbers
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //assuming command-line arguments correct

    int k = atoi(argv[1]);                                              //convert command argument string key to integer
    string t = get_string("plaintext: ");                               //prompt plaintext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(t); i++)
    {
        if ((int)t[i] > 64 && (int)t[i] < 91)                           //if string array char is capital letter
        {
            printf("%c", ((int)t[i] - 64 + k) % 26 + 64);
        }
        else if ((int)t[i] > 96 && (int)t[i] < 123)                     //if string array char is lower case letter
        {
            printf("%c", ((int)t[i] - 96 + k) % 26 + 96);
        }
        else                                                            //otherwise, text remains same
        {
            printf("%c", t[i]);
        }
    }
    printf("\n");

}