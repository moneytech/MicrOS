#include "raytracing.h"

#include "raytracing/matrix.h"
#include "raytracing/primitives.h"
#include <stdlib.h>
#include "../dal/videocard/videocard.h"
#include "../assembly/io.h"

Plane Planes[] =
{
// Declare six planes, each looks 
// towards origo and is 30 units away.
    { {{0,0,-1}}, -30 },
    { {{0, 1,0}}, -30 },
    { {{0,-1,0}}, -30 },
    { {{ 1,0,0}}, -30 },
    { {{0,0, 1}}, -30 },
    { {{-1,0,0}}, -30 }
};

Sphere Spheres[] =
{
// Declare a few spheres.
    { {{0,0,0}}, 7 },
    { {{19.4, -19.4, 0}}, 2.1 },
    { {{-19.4, 19.4, 0}}, 2.1 },
    { {{13.1, 5.1, 0}}, 1.1 },
    { {{ -5.1, -13.1, 0}}, 1.1 },
    { {{-30,30,15}}, 11},
    { {{15,-30,30}}, 6},
    { {{30,15,-30}}, 6}
};

LightSource Lights[] =
{
    { {{-28,-14, 3}}, {{.4, .51, .9}} },
    { {{-29,-29,-29}}, {{.95, .1, .1}} },
    { {{ 14, 29,-14}}, {{.8, .8, .8}} },
    { {{ 29, 29, 29}}, {{1,1,1}} },
    { {{ 28,  0, 29}}, {{.5, .6,  .1}} }
};

#define NElems(x) sizeof(x)/sizeof(*x)
const unsigned
    NumPlanes = NElems(Planes),
    NumSpheres = NElems(Spheres),
    NumLights = NElems(Lights),
    MAXTRACE = 6;

int RayFindObstacle
    (const XYZ* eye, const XYZ* dir,
     double* HitDist, int* HitIndex,
     XYZ* HitLoc, XYZ* HitNormal)
{
    // Try intersecting the ray with
    // each object and see which one
    // produces the closest hit.
    int HitType = -1;
   {for(unsigned i=0; i<NumSpheres; ++i)
    {
        XYZ V; 
        XYZ_sub_struct(&V, eye, &(Spheres[i].center));
        double r = Spheres[i].radius,
            DV = XYZ_dot(dir, &V),
            D2 = XYZ_squared(dir),
            SQ = DV*DV
               - D2*(XYZ_squared(&V) - r*r);
        // Does the ray coincide
        // with the sphere?
        if(SQ < 1e-6) continue;
        // Determine where exactly
        double SQt = sqrt(SQ),
            Dist = dmin(-DV-SQt,
                        -DV+SQt) / D2;
        if(Dist<1e-6 || Dist >= *HitDist)
            continue;
        HitType = 1; HitIndex = i;
        *HitDist = Dist;
        XYZ t;
        XYZ_mul_struct(&t, dir, HitDist);
        XYZ_add_struct_to(&t, eye);
        XYZ_set_struct(HitLoc, &t);
        XYZ_sub_struct(&t, HitLoc, &(Spheres[i].center));
        XYZ_mul_value_to(&t, 1/r);
        XYZ_set_struct(HitNormal, &t);
    }}
   {for(unsigned i=0; i<NumPlanes; ++i)
    {
        double DV = -XYZ_dot(&(Planes[i].normal), dir);
        if(DV > -1e-6) continue;
        double D2 =
            XYZ_dot(&(Planes[i].normal), eye),
            Dist = (D2+Planes[i].offset) / DV;
        if(Dist<1e-6 || Dist>=*HitDist)
            continue;
        HitType = 0; HitIndex = i;
        *HitDist = Dist;
        XYZ t;
        XYZ_mul_value(&t, dir, *HitDist);
        XYZ_add_struct_to(&t, eye);
        XYZ_set_struct(HitLoc, &t);
        XYZ_neg(&t, &(Planes[i].normal));
        *HitNormal = t;
    }}
    return HitType;
}

#define NumArealightVectors 20
XYZ ArealightVectors[NumArealightVectors];

void InitArealightVectors()
{
    // To smooth out shadows cast by lightsources,
    // I plan to approximate the lightsources with
    // a _cloud_ of lightsources around the point
    for(unsigned i=0; i<NumArealightVectors; ++i)
        for(unsigned n=0; n<3; ++n)
            ArealightVectors[i].d[n] =
                2.0 * (rand() / (double)RAND_MAX - 0.5);
}

void RayTrace(XYZ* resultcolor, const XYZ* eye, const XYZ* dir, int k)
{
    double HitDist = 1e6;
    XYZ HitLoc, HitNormal;
    int HitIndex, HitType;
    HitType = RayFindObstacle(eye,dir, &HitDist, HitIndex, &HitLoc, &HitNormal);
    if(HitType != -1)
    {
        // Found an obstacle. Next, find out how it is illuminated.
        // Shoot a ray to each lightsource, and determine if there
        // is an obstacle behind it. This is called "diffuse light".
        // To smooth out the infinitely sharp shadows caused by
        // infinitely small point-lightsources, assume the lightsource
        // is actually a cloud of small lightsources around its center.
        XYZ DiffuseLight = {{0,0,0}}, SpecularLight = {{0,0,0}};
        XYZ Pigment = {{1, 0.98, 0.94}}; // default pigment
        for(unsigned i=0; i<NumLights; ++i)
            for(unsigned j=0; j<NumArealightVectors; ++j)
            {
                XYZ V;
                XYZ_add_struct(&V, &(Lights[i].where), &(ArealightVectors[j]));
                XYZ_sub_struct_to(&V, &HitLoc);
                double LightDist = XYZ_len(&V);
                XYZ_normalize(&V);
                double DiffuseEffect = XYZ_dot(&HitNormal, &V) / (double)NumArealightVectors;
                double Attenuation = (1 + pow(LightDist / 34.0, 2.0));
                DiffuseEffect /= Attenuation;
                if(DiffuseEffect > 1e-3)
                {
                    double ShadowDist = LightDist - 1e-4;
                    XYZ a,b;
                    XYZ eye;
                    XYZ_mul_value(&eye, &V, 1e-4);
                    XYZ_add_struct_to(&eye, &HitLoc);
                    int q,t = RayFindObstacle(&eye, &V, &ShadowDist, &q, &a, &b);
                    if(t == -1) // No obstacle occluding the light?
                    {
                        XYZ_mul_value(&a, &(Lights[i].colour), DiffuseEffect);
                        XYZ_add_struct_to(&DiffuseLight, &a);
                    }
                        //DiffuseLight += Lights[i].colour * DiffuseEffect;
            }   }
        if(k > 1)
        {
            // Add specular light/reflection, unless recursion depth is at max
            XYZ V;
            XYZ_neg(&V, dir);
            XYZ_mirror_arround(&V, &HitNormal);
            XYZ eye;
            XYZ_mul_value(&eye, &V, 1e-4);
            XYZ_add_struct_to(&eye, &HitLoc);
            RayTrace(&SpecularLight, &eye, &V, k-1);
        }
        switch(HitType)
        {
            case 0: // plane
                XYZ_mul_value_to(&DiffuseLight, 0.9);
                XYZ_mul_value_to(&SpecularLight, 0.5);
                // Color the different walls differently
                switch(HitIndex % 3)
                {
                    case 0:
                        XYZ_set_values(&Pigment, 0.9, 0.7, 0.6); 
                        break;
                    case 1: 
                        XYZ_set_values(&Pigment, 0.6, 0.7, 0.7);
                        break;
                    case 2: 
                        XYZ_set_values(&Pigment, 0.5, 0.8, 0.3);
                        break;
                }
                break;
            case 1: // sphere
                XYZ_mul_value_to(&DiffuseLight, 1.0);
                XYZ_mul_value_to(&SpecularLight, 0.34);
        }
        XYZ res;
        XYZ_add_struct(&res, &DiffuseLight, &SpecularLight);
        XYZ_mul_struct_to(&res, &Pigment);
        XYZ_set_struct(&resultcolor, &res);
    }
}

// Declarations for the 8x8 Knoll-Yliluoma dithering
const unsigned CandCount = 64;
const double Gamma = 2.2;
const double Ungamma = 1.0 / 2.2;
unsigned Dither8x8[8][8];
XYZ Pal[16], PalG[16];
double luma[16];
void InitDither()
{
    // We will use the default 16-color EGA/VGA palette.

    io_out_byte(0x3C7, 0); // Read palette from VGA.
    for(unsigned i=0; i<16; ++i)
    {
        if(i==8) io_out_byte(0x3C7, 64-8);
        for(unsigned n=0; n<3; ++n)
            Pal[i].d[n] = io_in_byte(0x3C9);
        XYZ_mul_value_to(&(Pal[i]), 1/63.0);
        XYZ_pow(&(PalG[i]), &(Pal[i]), Gamma);
        luma[i] = XYZ_luma(&(Pal[i]));
    }

    io_in_byte(0x3da);
	io_out_byte(0x3c0, 0x20);
    // Create bayer dithering matrix, adjusted for candidate count
    for(unsigned y=0; y<8; ++y)
        for(unsigned x=0; x<8; ++x)
        {
            unsigned i = x ^ y, j;
            j = (x & 4)/4u + (x & 2)*2u + (x & 1)*16u;
            i = (i & 4)/2u + (i & 2)*4u + (i & 1)*32u;
            Dither8x8[y][x] = (j+i)*CandCount/64u;
        }
}

int ray_demo_main()
{
    video_card_set_video_mode(0x12);
    video_card_turn_on_buffer();
    // ^  Use BIOS, set 640x480 16-color graphics mode.

    InitDither();
    InitArealightVectors();
    XYZ camangle      = { {0,0,0} };
    XYZ camangledelta = { {-.005, -.011, -.017} };
    XYZ camlook       = { {0,0,0} };
    XYZ camlookdelta  = { {-.001, .005, .004} };

    double zoom = 46.0, zoomdelta = 0.99;
    double contrast = 32, contrast_offset = -0.17;

    const unsigned W = 640, H = 480;

    for(unsigned frameno=0; frameno<9300; ++frameno)
    {
        // Put camera between the central sphere and the walls
        XYZ campos = { { 0.0, 0.0, 16.0} };
        // Rotate it around the center
        Matrix camrotatematrix, camlookmatrix;
        Matrix_init_rotate(&camrotatematrix, &camangle);
        Matrix_transform(&camrotatematrix, &campos);
        Matrix_init_rotate(&camlookmatrix, &camlook);

        // Determine the contrast ratio for this frame's pixels
        double thisframe_min = 100;
        double thisframe_max = -100;

      #pragma omp parallel for
        for(unsigned y=0; y<H; ++y)
        {
            for(unsigned x=0; x<W; ++x)
            {
                XYZ camray = { { x / (double)W - 0.5,
                                 y / (double)H - 0.5,
                                 zoom } };
                camray.d[0] *= 4.0/3; // Aspect ratio correction
                XYZ_normalize(&camray);
                Matrix_transform(&camlookmatrix, &camray);
                XYZ campix;
                RayTrace(&campix, &campos, &camray, MAXTRACE);
                XYZ_mul_value_to(&campix, 0.5);
              #pragma omp critical
              {
                // Update frame luminosity info for automatic contrast adjuster
                double lum = XYZ_luma(&campix);
                #pragma omp flush(thisframe_min,thisframe_max)
                if(lum < thisframe_min) thisframe_min = lum;
                if(lum > thisframe_max) thisframe_max = lum;
                #pragma omp flush(thisframe_min,thisframe_max)
              }
                // Exaggerate the colors to bring contrast better forth
                XYZ nCampix;
                XYZ_add_value(&nCampix, &campix, contrast_offset);
                XYZ_mul_value_to(&nCampix, contrast);
                XYZ_set_struct(&campix, &nCampix);
                // Clamp, and compensate for display gamma (for dithering)
                XYZ_clamp_with_desauration(&campix);
                XYZ campixG;
                XYZ_pow(&campixG, &campix, Gamma);
                XYZ qtryG = campixG;
                // Create candidate for dithering
                unsigned candlist[CandCount];
                for(unsigned i=0; i<CandCount; ++i)
                {
                    unsigned k = 0;
                    double b = 1e6;
                    // Find closest match from palette
                    for(unsigned j=0; j<16; ++j)
                    {
                        XYZ na;
                        XYZ_sub_struct(&na, &qtryG, &(PalG[j]));
                        double a = XYZ_squared(&na);
                        if(a < b) { b = a; k = j; }
                    }
                    candlist[i] = k;
                    if(i+1 >= CandCount) break;
                    // Compensate for error
                    XYZ nqtryG;
                    XYZ_sub_struct(&nqtryG, &campixG, &(PalG[k]));
                    XYZ_add_struct_to(&qtryG, &nqtryG);
                    XYZ_clamp(&qtryG);
                }
                // Order candidates by luminosity
                // using insertion sort.
                for(unsigned j=1; j<CandCount; ++j)
                {
                    unsigned k = candlist[j], i;
                    for(i=j; i>=1 && luma[candlist[i-1]] > luma[k]; --i)
                        candlist[i] = candlist[i-1];
                    candlist[i] = k;
                }
                // Draw pixel (use BIOS).
                unsigned color = candlist[Dither8x8[x & 7][y & 7]];
                video_card_draw_pixel(color, x, y);
                /*_asm {
                    mov ax, color
                    mov ah, 0x0C
                    xor bx, bx
                    mov cx, x
                    mov dx, y
                    int 0x10
                }*/
        }   }
        video_card_swap_buffers();
        // Tweak coordinates / camera parameters for the next frame
        double much = 1.0;

        // In the beginning, do some camera action (play with zoom)
        if(zoom <= 1.1)
            zoom = 1.1;
        else
        {
            if(zoom > 40) { if(zoomdelta > 0.95) zoomdelta -= 0.001; }
            else if(zoom < 3) { if(zoomdelta < 0.99) zoomdelta += 0.001; }
            zoom *= zoomdelta;
            much = 1.1 / pow(zoom/1.1, 3);
        }

        // Update the rotation angle
        XYZ t;
        XYZ_mul_value(&t, &camlookdelta, much);
        XYZ_add_struct_to(&camlook, &t);
        XYZ_mul_value(&t, &camangledelta, much);
        XYZ_add_struct_to(&camangle, &t);

        // Dynamically readjust the contrast based on the contents
        // of the last frame
        double middle = (thisframe_min + thisframe_max) * 0.5;
        double span   = (thisframe_max - thisframe_min);
        thisframe_min = middle - span*0.60; // Avoid dark tones
        thisframe_max = middle + span*0.37; // Emphasize bright tones
        double new_contrast_offset = -thisframe_min;
        double new_contrast        = 1 / (thisframe_max - thisframe_min);
        // Avoid too abrupt changes, though
        double l = 0.85;
        if(frameno == 0) l = 0.7;
        contrast_offset = (contrast_offset*l + new_contrast_offset*(1.0-l));
        contrast        = (contrast*l + new_contrast*(1.0-l));
    }

    video_card_set_video_mode(0x03);
    //_asm { mov ax, 0x03; int 0x10 };
    // Set 80x25 text mode.
}