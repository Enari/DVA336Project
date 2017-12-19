//
//  main.cpp
//  DVA336Project
//
//  Created by Anton Roslund on 2017-12-05.
//  Copyright © 2017 Anton Roslund. All rights reserved.
//

#include <iostream>
#include "bitmap_image.hpp"

void test01()
{
    std::string file_name("../../../../../DVA336Project/images/zerio.bmp");
    
    bitmap_image image(file_name);
    
    if (!image){
        printf("test01() - Error - Failed to open '%s'\n",file_name.c_str());
        return;
    }
    
    image.save_image("../../../../../DVA336Project/images/test01_saved.bmp");
}

void mean(){
    std::string file_name("../../../../../DVA336Project/images/zerio.bmp");
    
    bitmap_image image(file_name);
    
    if (!image){
        printf("test01() - Error - Failed to open '%s'\n",file_name.c_str());
        return;
    }
    
    const unsigned int height = image.height();
    const unsigned int width  = image.width();
    
    bitmap_image out(height, width);
    
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
    
    out.save_image("../../../../../DVA336Project/images/out.bmp");
}

int main(int argc, const char * argv[]) {
    mean();
    
    return 0;
}
