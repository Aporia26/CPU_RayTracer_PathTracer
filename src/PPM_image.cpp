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

1.Calculate the ray from the “eye” through the pixel,
2.Determine which objects the ray intersects, and
3.Compute a color for the closest intersection point.
*/

#include "utility_pch.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

//First RayTrace! checking ray-sphere intersection Discrimant method
// the 3d shere equn in vector forn written as (c-p).(c-p) = r^2 so get quadratic...
/*
double hit_sphere(const point3& center, double radius, const ray& r) {
    //can also simplify
    vec3 oc = center - r.origin(); //vector pointing from the ray's starting origin to the center of the sphere
    //auto a = dot(r.direction(), r.direction());
    auto a = r.direction().length_squared();
    auto b = -2.0 * dot(r.direction(), oc);
    //auto c = dot(oc, oc) - radius*radius;
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant) ) / (2.0*a);
    }
}
*/
//sending and creating rays to scene and viewport
//color ray_color(const ray& r) 
//{
   //if (hit_sphere(point3(0,0,-1), 0.5, r))
   //     return color(1, 0, 0);

   /*auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));   //Adding SURFACE NORMALs for shading
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }*/

    color ray_color(const ray& r, const hittable& world) //Updated 
    {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

   //To get a sky gradient color with varyin g height y using lerp ie, 
   //0(blue)<a<1(white) so blendedvalue = (1-a).startvalue + a.endvalue
   vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main()
{
  //IMAGE----------------------------------------------------------------------------------------------------

   //int image_height = 256;  we now replace these fixed size to our apect ratio and pixel size we want!
   //int image_width = 256;

   auto aspect_ratio = 16.0/9.0;
   int image_width = 400;
// Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // WORLD-------------------------------------------------------------------------------------------------

    hittable_list world;
   //our scene
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    //CAMERA--------------------------------------------------------------------------------------------------

    auto focal_length = 1.0;
//the viewport helps to brigde the gap between our 3D scene and the 2D coordinates pixel grid.
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0,0,0); //Eye from where all rays originate

//To translate our 3D camera center with the image rendered origin ie, from top left------>
    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


  //RENDERER-------------------------------------------------------------------------------------------------

  /* std::cout << "P3\n" << image_height << ' ' << image_width << "\n255\n";

   for(int i=0; i<image_height; i++)
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
        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r,world);
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
