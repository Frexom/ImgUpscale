#include <stdio.h>
#include <stdlib.h>
#include "ppm.c"


struct PpmImage upscale(struct PpmImage* image){

    struct PpmImage upscaled = createEmptyPPM(image->height*2-1, image->width*2-1, image->maxColorValue);

    printf("Converting %d*%d to %d*%d...\n", image->width, image->height, upscaled.width, upscaled.height);

    for(int i=0; i< upscaled.height * upscaled.width;i++){
        int x = i % upscaled.width;
        int y = i / upscaled.width;

        //printf("X : %d, Y : %d\n", x, y);

        //Pixel already filled
        if(x%2 == 0 && y%2 == 0){
            upscaled.img[i].r = image->img[y/2*image->width + x/2].r;
            upscaled.img[i].g = image->img[y/2*image->width + x/2].g;
            upscaled.img[i].b = image->img[y/2*image->width + x/2].b;
        }

        //Pixel empty but top and bottom pixel filled
        if(x%2 == 0 && y%2 == 1){
            upscaled.img[i].r = (image->img[y/2*image->width + x/2].r + image->img[y/2*image->width+image->width + x/2].r)/2;
            upscaled.img[i].g = (image->img[y/2*image->width + x/2].g + image->img[y/2*image->width+image->width + x/2].g)/2;
            upscaled.img[i].b = (image->img[y/2*image->width + x/2].b + image->img[y/2*image->width+image->width + x/2].b)/2;
        }

        //Pixel empty but right and left pixel filled
        if(x%2 == 1 && y%2 == 0){
            upscaled.img[i].r = (image->img[y/2*image->width + x/2].r + image->img[y/2*image->width+ + x/2+1].r)/2;
            upscaled.img[i].g = (image->img[y/2*image->width + x/2].g + image->img[y/2*image->width+ + x/2+1].g)/2;
            upscaled.img[i].b = (image->img[y/2*image->width + x/2].b + image->img[y/2*image->width+ + x/2+1].b)/2;
        }

        //Pixel empty, must rely on diagonals

        if(x%2 == 1 && y%2 == 1){
            upscaled.img[i].r = (image->img[y/2*image->width + x/2].r + image->img[y/2*image->width+ + x/2+1].r + image->img[y/2*image->width+image->width + x/2].r + image->img[y/2*image->width+image->width + x/2+1].r)/4;
            upscaled.img[i].g = (image->img[y/2*image->width + x/2].g + image->img[y/2*image->width+ + x/2+1].g + image->img[y/2*image->width+image->width + x/2].g + image->img[y/2*image->width+image->width + x/2+1].g)/4;
            upscaled.img[i].b = (image->img[y/2*image->width + x/2].b + image->img[y/2*image->width+ + x/2+1].b + image->img[y/2*image->width+image->width + x/2].b + image->img[y/2*image->width+image->width + x/2+1].b)/4;
        }

    }
    return upscaled;
}




int main(int argc, char *argv[ ])
{
    if(argc < 2){
        printf("Please specify an image to upscale.");
    }
    struct PpmImage im;
    struct PpmImage imResultat;
    im=readPPM(argv[1]);

    // premiere méthode pour calculer le négatif d'une image
    // en créant une nouvelle image
    imResultat = upscale(&im);
    savePPM(imResultat, "upscaled.ppm");

    printf("Done!\n");

}
