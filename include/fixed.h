#ifndef  FIXED_INC
#define  FIXED_INC

#include "SDL.h"
#include <stdlib.h>

#define FIXPOINT_SHIFT  16
#define FIXPOINT_SCALE  65536

typedef int32_t fixed;

fixed itofp(int num);
fixed ftofp(float num);
fixed dtofp(double num);
float fptof(fixed fp_num);
fixed fpdiv(fixed dividend, fixed divisor);
fixed fpadd(fixed num1, fixed num2);
fixed fpsub(fixed num1, fixed num2);
fixed fpmul(fixed num1, fixed num2);
void fptest(void);

#endif
