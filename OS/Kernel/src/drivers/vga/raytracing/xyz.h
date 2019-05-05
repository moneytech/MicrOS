#ifndef xyz_h
#define xyz_h

#include <math.h>

double dmin(double a, double b);

typedef struct _XYZ
{
    double d[3];
} XYZ;

void XYZ_set_values(XYZ* d, double a, double b, double c);

void XYZ_set_struct(XYZ* d, XYZ* n);

//===

void XYZ_add_struct_to(XYZ* to, XYZ* b);

void XYZ_add_value_to(XYZ* to, double b);

void XYZ_add_struct(XYZ* result, XYZ* a, XYZ* b);

void XYZ_add_value(XYZ* result, XYZ* a, double b);

//===

void XYZ_sub_struct_to(XYZ* to, XYZ* b);

void XYZ_sub_value_to(XYZ* to, double b);

void XYZ_sub_struct(XYZ* result, XYZ* a, XYZ* b);

void XYZ_sub_value(XYZ* result, XYZ* a, double b);

//===

void XYZ_mul_struct_to(XYZ* to, XYZ* b);

void XYZ_mul_value_to(XYZ* to, double b);

void XYZ_mul_struct(XYZ* result, XYZ* a, XYZ* b);

void XYZ_mul_value(XYZ* result, XYZ* a, double b);

//===

void XYZ_neg(XYZ* result, XYZ* a);

void XYZ_pow(XYZ* result, XYZ* a, double b);

double XYZ_dot(XYZ* a, XYZ* b);

double XYZ_squared(XYZ* a);

double XYZ_len(XYZ* a);

void XYZ_normalize(XYZ* a);

void XYZ_mirror_arround(XYZ* a, XYZ* axis);

double XYZ_luma(XYZ* a);

void XYZ_clamp(XYZ* a);

void XYZ_clamp_with_desauration(XYZ* a);


#endif