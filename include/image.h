#ifndef IMAGE_H
#define IMAGE_H

#include "bmp.h"
#include "string.h"

void image_fill(struct image_data *this, struct pixel *color);

void image_draw_square(struct image_data *this, int x, int y, int w, int h, struct pixel *color);

inline struct pixel *image_pixel_at(struct image_data *this, int x, int y)
{
    return &this->pixel_array[this->width * y + x];
}

inline void image_pixel_set(struct image_data *this, int x, int y, struct pixel *color)
{
    memcpy(&this->pixel_array[this->width * y + x], color, sizeof(struct pixel));
}

#endif
