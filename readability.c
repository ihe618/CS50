#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");                     //Prompt for text

    //Define word count
    int wc = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' && text[i + 1] != ' ')
        {
            wc = wc + 1;
        }
    }

    //Define number of letters
    float l = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((65 <= (int)text[i] && (int)text[i] <= 90) || (97 <= (int)text[i] && (int)text[i] <= 122))
        {
            l = l + 1;
        }
    }
    float L = l * 100 / wc;                                 //Calculate number of letters per 100 wc

    //Define number of sentences
    float s = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((int)text[i] == 33 || (int)text[i] == 46 || (int)text[i] == 63)
        {
            s = s + 1;
        }
    }
    float S = s * 100 / wc;                                 //Calculate number of sentences per 100 wc

    float index = 0.0588 * L - 0.296 * S - 15.8;            //Calculate Coleman-Liau index

    if (index < 1)                                          //Print results
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}