#include "xyz.h"

double dmin(double a, double b)
{
    return a<b ? a : b;
}

void XYZ_set_values(XYZ* d, double a, double b, double c)
{
    d->d[0] = a; d->d[1] = b; d->d[2] = c; 
}

void XYZ_set_struct(XYZ* d, XYZ* n)
{
    d->d[0] = n->d[0]; d->d[1] = n->d[1]; d->d[2] = n->d[2]; 
}

//===

void XYZ_add_struct_to(XYZ* to, XYZ* b)
{
    for(unsigned n=0; n<3; ++n) to->d[n] += b->d[n];
}

void XYZ_add_value_to(XYZ* to, double b)
{
    for(unsigned n=0; n<3; ++n) to->d[n] += b;
}

void XYZ_add_struct(XYZ* result, XYZ* a, XYZ* b)
{
    XYZ_set_struct(result, a);
    XYZ_add_struct_to(result, b);
}

void XYZ_add_value(XYZ* result, XYZ* a, double b)
{
    XYZ_set_struct(result, a);
    XYZ_add_value_to(result, b);
}

//===

void XYZ_sub_struct_to(XYZ* to, XYZ* b)
{
    for(unsigned n=0; n<3; ++n) to->d[n] -= b->d[n];
}

void XYZ_sub_value_to(XYZ* to, double b)
{
    for(unsigned n=0; n<3; ++n) to->d[n] -= b;
}

void XYZ_sub_struct(XYZ* result, XYZ* a, XYZ* b)
{
    XYZ_set_struct(result, a);
    XYZ_sub_struct_to(result, b);
}

void XYZ_sub_value(XYZ* result, XYZ* a, double b)
{
    XYZ_set_struct(result, a);
    XYZ_sub_value_to(result, b);
}

//===

void XYZ_mul_struct_to(XYZ* to, XYZ* b)
{
    for(unsigned n=0; n<3; ++n) to->d[n] *= b->d[n];
}

void XYZ_mul_value_to(XYZ* to, double b)
{
    for(unsigned n=0; n<3; ++n) to->d[n] *= b;
}

void XYZ_mul_struct(XYZ* result, XYZ* a, XYZ* b)
{
    XYZ_set_struct(result, a);
    XYZ_mul_struct_to(result, b);
}

void XYZ_mul_value(XYZ* result, XYZ* a, double b)
{
    XYZ_set_struct(result, a);
    XYZ_mul_value_to(result, b);
}

//===

void XYZ_neg(XYZ* result, XYZ* a)
{
    for(unsigned n=0; n<3; ++n) result->d[n] = -(a->d[n]);
}

void XYZ_pow(XYZ* result, XYZ* a, double b)
{
    for(unsigned n=0; n<3; ++n) result->d[n] = pow(a->d[n], b);
}

double XYZ_squared(XYZ* a)
{
    return XYZ_dot(a, a);
}

double XYZ_len(XYZ* a)
{
    return sqrt(XYZ_squared(a));
}

double XYZ_dot(XYZ* a, XYZ* b)
{
    return a->d[0] * b->d[0] + a->d[1] * b->d[1] + a->d[2] * b->d[2];
}

void XYZ_normalize(XYZ* a)
{
    XYZ_mul_value_to(a, 1.0 / XYZ_len(a));
}

XYZ N;

void XYZ_mirror_arround(XYZ* a, XYZ* axis)
{
    N = *axis; 
    XYZ_normalize(&N);
    double v = XYZ_dot(a, &N);
    XYZ_mul_value_to(&N, v+v);
    XYZ_sub_struct_to(&N, a);
    XYZ_set_struct(a, &N);
}

double XYZ_luma(XYZ* a) 
{ 
    return a->d[0]*0.299 + a->d[1]*0.587 + a->d[2]*0.114; 
}

void XYZ_clamp(XYZ* a)
{
    for(unsigned n=0; n<3; ++n)
        {
            if(a->d[n] < 0.0) a->d[n] = 0.0;
            else if(a->d[n] > 1.0) a->d[n] = 1.0;
        }
}

XYZ t;

void XYZ_clamp_with_desauration(XYZ* a)
{
    double l = XYZ_luma(a), sat = 1.0;
    if(l > 1.0) { a->d[0] = a->d[1] = a->d[2] = 1.0; return; }
    if(l < 0.0) { a->d[0] = a->d[1] = a->d[2] = 0.0; return; }
    for(int n=0; n<3; ++n)
        if(a->d[n] > 1.0) sat = dmin(sat, (l-1.0) / (l-a->d[n]));
        else if(a->d[n] < 0.0) sat = dmin(sat, l  / (l-a->d[n]));
    if(sat != 1.0)
    {
        XYZ_set_struct(&t, a);
        XYZ_sub_value_to(&t, l);
        XYZ_mul_value_to(&t, sat);
        XYZ_add_value_to(&t, l);
        XYZ_set_struct(a, &t);
        XYZ_clamp(a);
    }
    //{ *this = (*this - l) * sat + l; Clamp(); }
}