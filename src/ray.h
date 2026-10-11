/*
The one thing that all ray tracers have is a ray class and a computation of what color is seen along a ray.
A ray is like this function -> P(t) = A + t.b where A is origin and b is direction and parameter t for cnaging leght.
*/

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray 
{
  public:
    ray() {}     //default and paramateric constructors
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }

    point3 at(double t) const 
    {
        return orig + t*dir;   // our ray function
    }  

  private:
    point3 orig;
    vec3 dir;
};

#endif