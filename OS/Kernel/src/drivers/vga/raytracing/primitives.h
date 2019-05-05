#ifndef primitives_h
#define primitives_h

#include "xyz.h"

typedef struct _Plane
{ XYZ normal; double offset; } Plane;

typedef struct _Sphere
{ XYZ center; double radius; } Sphere;

typedef struct _LightSource
{ XYZ where, colour; } LightSource;

#endif