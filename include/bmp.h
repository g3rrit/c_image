#ifndef BMP_H
#define BMP_H

struct pixel
{
    float r;
    float g;
    float b;
};

struct image_data
{
    int dpi;
    int width;
    int height;
    struct pixel *pixel_array; 
};

struct image_data *load_bmp(char *url);

int save_bmp(char *url, struct image_data *data);

#endif
