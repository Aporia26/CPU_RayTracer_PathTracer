#ifndef HITTABLE_H
#define HITTABLE_H

/*
This is an Abstract class to list the hittable object with which rays interact and give color
this is to include more than one object rendering. ----> BluePrint

we will eventually want to determine which side of the surface that the ray is coming from. 
This is important for objects that are rendered differently on each side, like glass or text on paper...
so,
If we decide to have the normals always point out, then we will need to determine which side the ray is on when we color it.
We can figure this out by comparing the ray with the normal. If the ray and the normal face in the same direction, 
the ray is inside the object, if the ray and the normal face in the opposite direction, then the ray is outside the object. 
This can be determined by taking the dot product of the two vectors, where if their dot is positive, the ray is inside the sphere.

If we decide to have the normals always point against the ray, we won't be able to use the dot product to determine which side of the surface the ray is on. Instead, we would need to store that information:
bool front_face;
if (dot(ray_direction, outward_normal) > 0.0) {
    // ray is inside the sphere
    normal = -outward_normal;
    front_face = false;
} else {
    // ray is outside the sphere
    normal = outward_normal;
    front_face = true;
}

*/

#include "utility_pch.h"
class hit_record
{
 public:
    vec3 normal;
    point3 p;
    double t;
  // inside and outside ray is where? --> we will use dot product method!
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0; //-ve mean opp. dir
        normal = front_face ? outward_normal : -outward_normal; //ternary operator
                                   // If it's a front face hit, keep it pointing out. Otherwise, flip it inward
    }
};

class hittable
{
 public:
    virtual ~hittable() {}

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0; 
    //hit functions takes in rays and tmin<t<tmax
};

#endif