#ifndef matrix_h
#define matrix_h

#include "xyz.h"

typedef struct _matrix
{
    XYZ m[3];
} Matrix;

void Matrix_init_rotate(Matrix* m, XYZ* angle);
void Matrix_transform(Matrix* m, XYZ* vec);

#endif