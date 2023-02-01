#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef char string;

int main(int argc, char *argv[])
{
    printf("\n\n%s\n\n", argv[1]);

    string *digitos = "0123456789";

    FILE *arq = fopen(argv[1], "r");

    if
    (arq == NULL)
    {
        printf("\n\nFaiou!\n\n");
        return 1;
    }

    FILE *pa = NULL;
    BYTE bytes[512];
    int contaJPEG = 0;
    while
    (fread(bytes, sizeof(BYTE), 512, arq))
    {
        if
        (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
        {
            if
            (bytes[3] >= 0xe0 && bytes[3] < 0xef)
            {
                //string nomarq = "";
                char nomarq[] = "000.JPEG";

                int unidade = contaJPEG % 10;
                int dezena = (contaJPEG - unidade) / 10;
                nomarq[1] = digitos[dezena];
                nomarq[2] = digitos[unidade];

                printf("%i° arquivo %s\n", contaJPEG, nomarq);

                if(pa)
                {
                    fclose(pa);
                }

                pa = fopen(nomarq, "w+");
                fwrite(&bytes, sizeof(BYTE), 512, pa);
                contaJPEG++;

            }
        }
    }

    fclose(pa);
}