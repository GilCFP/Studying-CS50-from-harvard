#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX 512
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if  (argc != 2){
        printf("Usage: ./recover <filename.raw>\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL){
        printf("Empty file /Reading error\n");
        return 1;
    }
    int writing;
    int jpeg_count = 0;
    BYTE buffer[MAX];
    char *name = malloc(9);
    FILE *img;
    while(fread(buffer, 1, MAX, card) != 0)
        {
            if((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff)  && (buffer[3] & 0xf0) == 0xe0)
            {
                if (writing == 1)
                {
                    fclose(img);
                    writing = 0;
                }
                if(jpeg_count > 100)
                {
                    return 1;
                }

                sprintf(name, "%03i.jpg",jpeg_count);
                img = fopen(name,"w");
                writing = 1;
                fwrite(buffer, 1, MAX, img);
                jpeg_count++;
            }
            else
            {
                if(jpeg_count > 0)
                {
                fwrite(buffer, 1, MAX, img);
                }
            }
        }
        fclose(img);
        free(name);
        return 0;
}
