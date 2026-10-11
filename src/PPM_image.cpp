/*
Whenever you start a renderer, you need a way to see an image. 
The most straightforward way is to write it to a file. The catch is, there are so many formats

Instead of usig complex ap opengl and vulkan, we will use PPM stands for Portable Pixmap. 
It is a very simple image format written in plain text.
its example -->
    P3  (means code is in ASCII)
    3 2 (Means 3 columns and 2 rows)
    255 (Means max color value)
    255 0 0     0 255 0     0 0 255 (RGB triplet)
    255 255 0   255 255 255 0 0 0   
*/
#include <iostream>
#include "vec3.h"
#include "color.h"

int main()
{
  //image

   int image_height = 256;
   int image_width = 256;

  //render

   std::cout << "P3\n" << image_height << ' ' << image_width << "\n255\n";

  /* for(int i=0; i<image_height; i++)
   { 
    std::clog << "\rScanlines Remaining: " << (image_height-i) << ' ' << std::flush;
     for(int j=0; j<image_width; j++)
     {
        auto r = double(j)/(image_width-1);
        auto g = double(i)/(image_height-1);
        auto b = 0.0f;                                //this is without vec3 and color classes

        int ir = int(255.999*r);
        int ig = int(255.999*g);
        int ib = int(255.999*b);
        std::cout << ir << ' '<< ig << ' '<< ib << '\n';
     }
   }
*/
//with vec3 and color classes we made...
 std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) 
    {
     std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
     for (int i = 0; i < image_width; i++) 
     {
        auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
        write_color(std::cout, pixel_color);
     }
    }
     std::clog << "\rDone.            \n";

  /*
  The pixels are written in rows in left to right and top to bottom.
  we have also added a loading.
  */

    return 0;
}
