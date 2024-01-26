#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image/stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

int main(void) {
int width, height, channels;
unsigned char *img = stbi_load("snow.jpg", &width, &height, &channels, 0);
if(img == NULL) {
printf("Error in loading the image\n");
exit(1);
}
printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

int new_width = width /3;
int new_height = height /3;
unsigned char *resized_img = malloc(new_width * new_height * channels);

stbir_resize_uint8(img, width, height, 0, resized_img, new_width, new_height, 0, channels);

stbi_write_png("karthi_resized.png", new_width, new_height, channels, resized_img, new_width * channels);
stbi_write_jpg("karthi_resized.jpg", new_width, new_height, channels, resized_img, 100);

stbi_image_free(img);
free(resized_img);
}