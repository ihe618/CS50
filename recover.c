#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Define 1 byte of data
    typedef uint8_t BYTE;

    // Make sure user entered exactly 2 prompts
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    // Check pointer isn't null
    if (file == NULL)
    {
        return 1;
    }

    int i = -1;                                                         // create counter for jpegs
    FILE *img[50];                                                      // create array of pointers to 50 files named img
    // Repeat until end of file
    BYTE block [512];
    while (fread(&block, 1, 512, file) == 512)                          // keep reading block while block is full 512 bytes
    {
        // Check if first bytes are 0xff 0xd8 0xff & 0xe- (jpeg)
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (i == -1)                                                // if there has been no previous jpeg
            {
                i++;                                                    // add to counter to indicate new jpeg
                char *filename = malloc(8);                             // set aside string of 8 bytes for file name (xxx.jpg followed by null)
                sprintf(filename, "%03i.jpg", i);                       // print file name in correct format
                img[i] = fopen(filename, "w");
                fwrite(&block, 1, 512, img[i]);                         // write block to new image file of name
                free(filename);                                         // free the 8 bytes
            }
            else
            {
                // Else close old file and create next file
                i++;                                                    // add to counter
                fclose(img[i - 1]);                                     // close previous file
                char *filename = malloc(8);                             // set aside 8 bytes for file name
                sprintf(filename, "%03i.jpg", i);                       // print file name in correct format
                img[i] = fopen(filename, "w");
                fwrite(&block, 1, 512, img[i]);                         // write block to new image file of name
                free(filename);                                         // free the 8 bytes
            }
        }
        else
        {
            // Else if a jpeg already exists then continue writing
            if (i >= 0)
            {
                fwrite(&block, 1, 512, img[i]);
            }
        }
    }
    fclose(img[i]);                                                     // close last image file
    fclose(file);                                                       // close source file
}
