#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "raytracing/xyz.h"

int RayFindObstacle
    (XYZ* eye, XYZ* dir,
     double* HitDist, int* HitIndex,
     XYZ* HitLoc, XYZ* HitNormal);

int ray_demo_main();

#endif