#include <stdio.h>
#include <stdlib.h>

struct PpmImage {
    int height; // nombre de ligne de l'image
    int width;  // nombre de colonne de l'image
    int maxColorValue; // nombre niveau par pixel
    struct Pixel  *img; // un pointeur sur un tableau de pixels
};

struct Pixel{
    unsigned char r,g,b, padding;
    // padding is used to make the structure 4 bytes, which is a power of 2
    // and speeds up the code at runtime
};



struct PpmImage readPPM(char nom[]){

    FILE *f;
    struct PpmImage image;

    if( (f=fopen(nom,"r")) == NULL ) {
        printf("file opening error\n");
        exit(1);
    }

    char ligne[128];
    // checks if image is valid
    if ( (fgets(ligne, 70, f)==NULL)  || ( ligne[0] != 'P' && ligne[1] != '3' && ligne[2] != '\n')) {
        printf("Image not valid\n");
        exit(1);
    }

    // on ne considere que les fichiers avec 1 seule ligne de commentaires
    if (fgets(ligne, 128, f)==NULL) {
        printf("error reading comment.");
        exit(1);
    }

    fscanf(f,"%d", &(image.width));
    fscanf(f,"%d", &(image.height));
    fscanf(f,"%d", &(image.maxColorValue));

    if ((image.img=malloc(image.width*image.height*sizeof(struct Pixel )))==NULL) {
        printf("malloc error.\n");
        exit(1);
    }

    for(int i=0; i< image.width*image.height;i++){
        unsigned int r,v,b;

        fscanf(f,"%d %d %d ",&r,&v,&b);
        image.img[i].r=r;
        image.img[i].g=v;
        image.img[i].b=b;
    }
    return image;
}


void savePPM(struct PpmImage image, char nom[]){

    FILE *f;
    if ((f=fopen(nom,"w"))==NULL){
        printf("File opening error\n");
        exit(1);
    }

    fprintf(f,"P3\n");
    fprintf(f,"#\n");

    fprintf(f,"%d ", image.width);
    fprintf(f,"%d\n", image.height);
    fprintf(f,"%d\n", image.maxColorValue);

    for(int i=0; i< image.width*image.height;i++){
        fprintf(f,"%d %d %d\n", image.img[i].r, image.img[i].g, image.img[i].b);
    }
}


struct PpmImage createEmptyPPM(int height, int width, int maxColorValue){

    if (maxColorValue>65536) {
        printf ("Too many colors");
        exit(1);
    }

    struct PpmImage image;
    image.height=height;
    image.width=width;
    image.maxColorValue=maxColorValue;

    if ((image.img=malloc(image.width*image.height*sizeof(struct Pixel )))==NULL){
        printf("Malloc error\n");
        exit(1);
    }

    return image;
}
