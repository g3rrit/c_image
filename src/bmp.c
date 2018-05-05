#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void image_data_create(struct image_data *this, int width, int height, int dpi)
{
    this->width = width;
    this->height = height;
    this->dpi = dpi;

    this->pixel_array = malloc(sizeof(struct pixel) * width * height);
}

void image_data_delete(struct image_data *this)
{
    if(this->pixel_array)
        free(this->pixel_array);
}

struct bmp_file_header
{
    unsigned char bitmap_type[2];
    int file_size;
    short r_1;
    short r_2;
    unsigned int offset_bits;
};

struct bmp_image_header
{
    unsigned int size_header;
    unsigned int width;
    unsigned int height;
    short int planes;
    short int bit_count;
    unsigned int compression;
    unsigned int image_size;
    unsigned int ppm_x;
    unsigned int ppm_y;
    unsigned int clr_used;
    unsigned int clr_important;
};


int load_bmp(char *url, struct image_data *data)
{
    FILE *file = fopen(url, "rb");

    if(!file)
    {
        printf("error opening file: %s\n", url);
        return 0;
    }

    struct bmp_file_header bfh;
    struct bmp_image_header bih;

    fread(&bfh, 1, 14, file);
    fread(&bih, 1, sizeof(bih), file);

    data->dpi = bih.ppm_x / 39.375;
    data->width = bih.width;
    data->height = bih.height;

    int image_size = data->width * data->height;

    data->pixel_array = malloc(sizeof(struct pixel) * data->width * data->height);

    for(int i = 0; i < image_size; i++)
    {
        unsigned char color[3] = { data->pixel_array[i].b, data->pixel_array[i].g, data->pixel_array[i].r };

        fread(color, 1, sizeof(color), file);

        data->pixel_array[i].b = color[0];
        data->pixel_array[i].g = color[1];
        data->pixel_array[i].r = color[2];
    }

    return image_size;
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

    int ppm = data->dpi * 39.375;

    struct bmp_file_header bfh;

    struct bmp_image_header bih;
    
    memcpy(&bfh.bitmap_type, "BM", 2);
    bfh.file_size = file_size;
    bfh.r_1 = 0;
    bfh.r_2 = 0;
    bfh.offset_bits = 0;

    bih.size_header = sizeof(bih);
    bih.width = data->width;
    bih.height = data->height;
    bih.planes = 1;
    bih.bit_count = 24;
    bih.compression = 0;
    bih.image_size = file_size;
    bih.ppm_x = ppm;
    bih.ppm_y = ppm;
    bih.clr_used = 0;
    bih.clr_important = 0;

    fwrite(&bfh, 1, 14, file);
    fwrite(&bih, 1, sizeof(bih), file);

    for(int i = 0; i < image_size; i++)
    {
        unsigned char color[3] = { data->pixel_array[i].b, data->pixel_array[i].g, data->pixel_array[i].r };

        fwrite(color, 1, sizeof(color), file);
    }

    fclose(file);

    return 1;
}
