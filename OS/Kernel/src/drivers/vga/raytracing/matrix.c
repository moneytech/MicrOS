#include "matrix.h"
#include "math.h"

void Matrix_init_rotate(Matrix* m, XYZ* angle)
{
       double Cx = cos(angle->d[0]), Cy = cos(angle->d[1]), Cz = cos(angle->d[2]);
       double Sx = sin(angle->d[0]), Sy = sin(angle->d[1]), Sz = sin(angle->d[2]);
       double sxsz = Sx*Sz, cxsz = Cx*Sz;
       double cxcz = Cx*Cz, sxcz = Sx*Cz;
       XYZ_set_values(&(m->m[0]), Cy*Cz, Cy*Sz, -Sy);
       XYZ_set_values(&(m->m[1]), sxcz*Sy - cxsz, sxsz*Sy + cxcz, Sx*Cy);
       XYZ_set_values(&(m->m[2]), cxcz*Sy + sxsz, cxsz*Sy - sxcz, Cx*Cy);
       //{ {{ Cy*Cz, Cy*Sz, -Sy }},
       //                    {{ sxcz*Sy - cxsz, sxsz*Sy + cxcz, Sx*Cy }},
       //                    {{ cxcz*Sy + sxsz, cxsz*Sy - sxcz, Cx*Cy }}};
}

void Matrix_transform(Matrix* m, XYZ* vec)
{
    XYZ_set_values(vec, XYZ_dot(&(m->m[0]), vec), XYZ_dot(&(m->m[1]), vec), XYZ_dot(&(m->m[2]), vec));
}