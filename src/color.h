#ifndef COLOR_H
#define COLOR_H

#include<iostream>
#include "vec3.h"

//Type Alising
using color = vec3;

void write_color(std::ostream& out, const color& pixel_color)
{
    auto r = pixel_color.x(); //accessing the member function we defined in vec3
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //translate [0,1] to our [0,255] range value
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    //Write out the pixel colors
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n'; 
}

#endif