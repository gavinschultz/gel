#include "fixed.h"
#include "debug.h"

fixed itofp(int num)
{
    return (fixed)(num << FIXPOINT_SHIFT);
}

fixed ftofp(float num)
{
    return (fixed)(num * FIXPOINT_SCALE);
}

fixed dtofp(double num)
{
    return (fixed)(num * FIXPOINT_SCALE);
}

float fptof(fixed num)
{
    return (float)(num / (float)FIXPOINT_SCALE);
}

fixed fpdiv(fixed dividend, fixed divisor)
{
    return (fixed)((((int64_t)dividend) << FIXPOINT_SHIFT) / divisor);
}

fixed fpadd(fixed num1, fixed num2)
{
    return num1 + num2;
}

fixed fpsub(fixed num1, fixed num2)
{
    return num1 - num2;
}

fixed fpmul(fixed num1, fixed num2)
{
    return (fixed)(((int64_t)num1 * num2) >> FIXPOINT_SHIFT);
}

void fptest()
{
    int i = 10;
    float f = 20.0;
    fixed fpi, fpf;
    fixed divfp1, mulfp1, subfp1, addfp1;
    fixed divfp2, mulfp2, subfp2, addfp2;

    fpi = itofp(i);
    trace("i: %d fpi: %ld, fpi-f: %f", i, fpi, fptof(fpi));
    fpf = ftofp(f);
    trace("f: %f fpf: %ld, fpf-f: %f", f, fpf, fptof(fpf));

    divfp1 = fpdiv(fpi, fpf);
    mulfp1 = fpmul(fpi, fpf);
    subfp1 = fpsub(fpi, fpf);
    addfp1 = fpadd(fpi, fpf);
    divfp2 = fpdiv(fpf, fpi);
    mulfp2 = fpmul(fpf, fpi);
    subfp2 = fpsub(fpf, fpi);
    addfp2 = fpadd(fpf, fpi);
    trace("dividing (%i / %f) fp: %ld f: %f", i, f, divfp1, fptof(divfp1));
    trace("multiply (%i * %f) fp: %ld f: %f", i, f, mulfp1, fptof(mulfp1));
    trace("add      (%i + %f) fp: %ld f: %f", i, f, addfp1, fptof(addfp1));
    trace("subtract (%i - %f) fp: %ld f: %f", i, f, subfp1, fptof(subfp1));
    trace("dividing (%f / %i) fp: %ld f: %f", f, i, divfp2, fptof(divfp2));
    trace("multiply (%f * %i) fp: %ld f: %f", f, i, mulfp2, fptof(mulfp2));
    trace("add      (%f + %i) fp: %ld f: %f", f, i, addfp2, fptof(addfp2));
    trace("subtract (%f - %i) fp: %ld f: %f", f, i, subfp2, fptof(subfp2));
}
