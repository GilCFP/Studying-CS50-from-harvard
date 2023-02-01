// Modifies the volume of an audio file
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef uint8_t BYTE;
typedef int16_t BYTES;


// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    float factor = atof(argv[3]);
    BYTE header[HEADER_SIZE];
    BYTES buffer[1000];
    fread(&header,1,HEADER_SIZE,input);
    fwrite(&header, 1, HEADER_SIZE, output);
    while(fread(&buffer, 2, 1, input)!=0)
    {
        buffer[0] = (buffer[0] * factor);
        fwrite(buffer, 2, 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
