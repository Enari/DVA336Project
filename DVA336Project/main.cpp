//
//  main.cpp
//  DVA336Project
//

#include <stdlib.h>
#include <stdio.h>
#include "bitmap_image.hpp"
#include <time.h>
#include <pthread.h>

// Number of threads
#define P 4

bitmap_image image;
bitmap_image out;

struct args
{
    int hStart;
    int hEnd;
    int wStart;
    int wEnd;
    int height;
    int width;
};

void* mean(void * args){
    struct args params = *((struct args*)args);
    
    for (int y = params.hStart; y < params.hEnd; y++){
        for (int x = params.wStart; x < params.wEnd; x++){
            int red = 0;
            int green = 0;
            int blue = 0;
            int neighbors = 0;
            rgb_t colour;
            
            for(int i = x-1; i <= x+1; i++){
                for(int j = y-1; j <= y+1; j++){
                    if(i >= 0 && j >= 0 && i < params.height && j < params.width){
                        neighbors++;
                        image.get_pixel(i, j, colour);
                        
                        red   += colour.red;
                        green += colour.green;
                        blue  += colour.blue;
                    }
                }
            }
            red   /= neighbors;
            green /= neighbors;
            blue  /= neighbors;
            colour = make_colour(red, green, blue);
            out.set_pixel(x, y, colour);
            
        }
    }
    return NULL;
}

int main(int argc, const char * argv[]) {
    pthread_t thread[P];
    pthread_attr_t attr;
    time_t time;
    image = bitmap_image("../../../../../DVA336Project/images/zerio.bmp");
    
    if (!image){
        printf("test01() - Error - Failed to open image\n");
        return 1;
    }
    
    int height = image.height();
    int width = image.width();
    
    out = bitmap_image(width, height);
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    time = clock();
    
    for (int i = 0; i < 1; i++)
    {
        struct args* params = (struct args*)malloc(sizeof(struct args));
        params->hStart = 0;
        params->hEnd = height;
        params->wStart = 0;
        params->wEnd = width;
        params->height = height;
        params->width = width;
        
        pthread_create(&thread[i], &attr, &mean, (void*)params);
    }
    
    //Join the fucking threads
    for (int i = 0; i < P; i++) {
        pthread_join(thread[i], NULL);
    }
    
    out.save_image("../../../../../DVA336Project/images/out.bmp");
    
    time = clock() - time;
    printf("time:%f\n", ((float)time/CLOCKS_PER_SEC));
    
    return 0;
}
