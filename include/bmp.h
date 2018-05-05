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

void image_data_create(struct image_data *this, int width, int height, int dpi);

void image_data_delete(struct image_data *this);

int load_bmp(char *url, struct image_data *data);

int save_bmp(char *url, struct image_data *data);

#endif
