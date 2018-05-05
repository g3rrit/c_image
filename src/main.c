#include "bmp.h"
#include "util.h"
#include "image.h"

int main()
{
    struct image_data i_data;
    image_data_create(&i_data, 100, 100, 96);

    struct pixel p_r = { .r = 255, .g = 0, .b = 0 };
    struct pixel p_g = { .r = 0, .g = 255, .b = 0 };
    image_fill(&i_data, &p_r);

    save_bmp("img.bmp", &i_data);

    struct image_data i_data2;
    load_bmp("img.bmp", &i_data2);

    image_draw_square(&i_data2, 10, 10, 80, 80, &p_g);

    save_bmp("img2.bmp", &i_data2);

    image_data_delete(&i_data);
    image_data_delete(&i_data2);

    return 0;
}
