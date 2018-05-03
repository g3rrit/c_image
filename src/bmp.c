#include "bmp.h"

#include <stdio.h>

struct image_data *load_bmp(char *url)
{
}

int save_bmp(char *url, struct image_data *data)
{
    FILE *file = fopen(url, "wb");

    if(!file)
    {
        printf("error opening file\n");
        return 0;
    }

    int image_size = data->height * data->width;

    int file_size = 54 + 4 * image_size;

    int ppm = dpi * 39.375;



}
