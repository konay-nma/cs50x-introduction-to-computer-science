#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r"); // file open input file
    if (inputFile == NULL)
    {
        printf("something worg\n");
        return 2;
    }

    BYTE buffer[BLOCK_SIZE];
    int imageCount = 0;
    FILE *outptr = NULL;
    char outfile[8];
    while (true)
    {
        size_t  retRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inputFile);

        if (retRead < 512) //checking the end of file
        {
            printf("%zu\n", retRead);
            break;
        }
        bool isImage = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
        if (isImage && outptr != NULL)
        {
            fclose(outptr);
            imageCount++;

        }

        if (isImage)
        {
            sprintf(outfile, "%03i.jpg", imageCount); // write out file with file name
            outptr = fopen(outfile, "w");
        }

        // wirte out file if file is alrady open
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), retRead, outptr);
        }

    }

    printf("%i\n", imageCount);
    // cloe the outfile
    fclose(outptr);
    //close the input file
    fclose(inputFile);
}
