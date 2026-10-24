#ifndef SPHERE_H
#define SPHERE_H

//multiple spheres inside hittable list 

#include "hittable.h"
#include "utility_pch.h"

class sphere : public hittable
{
 public:
    sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}

    //hit rays for our sphere
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
//ie,he tracer aims to find the closest valid intersection point that falls inside the allowed distance window (ray_tmin to ray_tmax)
        auto root = (h - sqrtd) / a;
        //if (root <= ray_t.min || ray_t.max <= root) {         instead use interval
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            // if (root <= ray_t.min || ray_t.max <= root)
            if (!ray_t.surrounds(root)){
                return false;
        }
    }
//recording hit data
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
        //determination of surface side
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r,outward_normal);

        return true;
    }

  private:
    point3 center;
    double radius;
};

#endif