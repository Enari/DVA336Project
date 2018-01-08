//
//  main.cpp
//  DVA336Project
//

#include <stdlib.h>
#include <stdio.h>
#include "bitmap_image.hpp"
#include <omp.h>

int main(int argc, const char * argv[]) {

    time_t time;
    bitmap_image out image = bitmap_image("images/zerio.bmp");
    if (!image){
        printf("Error - Failed to open image\n");
        return 1;
    }

    int height = image.height();
    int width = image.width();

    bitmap_image out = bitmap_image(image.height(), image.height());
    
    time = clock();
    
    #pragma opm parallel for static(image)
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            int red = 0;
            int green = 0;
            int blue = 0;
            int neighbors = 0;
            rgb_t colour;
            
            for(int i = x-1; i <= x+1; i++){
                for(int j = y-1; j <= y+1; j++){
                    if(i >= 0 && j >= 0 && i < height && j < width){
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

    time = clock() - time;
    printf("time:%f\n", ((float)time/CLOCKS_PER_SEC));
    
    out.save_image("images/out.bmp");
    
    return 0;
}
