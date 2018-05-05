#include "image.h"

void image_fill(struct image_data *this, struct pixel *color)
{
    for(int i = 0; i < this->width * this->height; i++)
        memcpy(&this->pixel_array[i], color, sizeof(struct pixel));
}

void image_draw_square(struct image_data *this, int x, int y, int w, int h, struct pixel *color)
{
    if(x < 0 || y < 0 || x + w >= this->width || y + h >= this->height)
        return;

    for(int i = 0; i < w; i++)
        for(int n = 0; n < h; n++)
            memcpy(&this->pixel_array[this->width * (y + n) + (i + x)], color, sizeof(struct pixel));
}


