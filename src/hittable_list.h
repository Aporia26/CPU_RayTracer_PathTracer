#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "utility_pch.h"
#include <vector>

class hittable_list : public hittable //inheriting from abstarct class
{
 public:
    std::vector<shared_ptr<hittable>> objects;  //dynamic array containg smart pointers

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); } //to add object into empty world

    void clear() { objects.clear(); } //delete objects
    void add(shared_ptr<hittable> object)//new object pointer taken into our dynamic array
    {
        objects.push_back(object);
    }

    //To check through each and all objects if a ray hit something
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override 
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif