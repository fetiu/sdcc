/*-------------------------------------------------------------------------
   math.h: Floating point math function declarations

   Copyright (C) 2001, Jesus Calvino-Fraga, jesusc@ieee.org

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2.1, or (at your option) any
   later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License 
   along with this library; see the file COPYING. If not, write to the
   Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.

   As a special exception, if you link this library with other files,
   some of which are compiled with SDCC, to produce an executable,
   this library does not by itself cause the resulting executable to
   be covered by the GNU General Public License. This exception does
   not however invalidate any other reasons why the executable file
   might be covered by the GNU General Public License.
-------------------------------------------------------------------------*/

/* Version 1.0 - Initial release */

#ifndef _INC_MATH
#define _INC_MATH

#define HUGE_VALF   3.402823466e+38

#define PI          3.1415926536
#define TWO_PI      6.2831853071
#define HALF_PI     1.5707963268
#define QUART_PI    0.7853981634
#define iPI         0.3183098862
#define iTWO_PI     0.1591549431
#define TWO_O_PI    0.6366197724

/* EPS=B**(-t/2), where B is the radix of the floating-point representation
   and there are t base-B digits in the significand.  Therefore, for floats
   EPS=2**(-12).  Also define EPS2=EPS*EPS. */
#define EPS 244.14062E-6
#define EPS2 59.6046E-9

union float_long
{
    float f;
    long l;
};

#if defined(SDCC_MATH_LIB) && defined(SDCC_mcs51) && !defined(SDCC_USE_XSTACK) && !defined(SDCC_STACK_AUTO) && !defined(_SDCC_NO_ASM_LIB_FUNCS)
/* Compile the mcs51 assembly version only when all these
   conditions are met.  Since not all the functions are
   reentrant, do not compile with --stack-auto is used. */
#define MATH_ASM_MCS51
#endif


/* Functions on the z80 & gbz80 are always reentrant and so the "reentrant" */
/* keyword is not defined. */
#if defined(SDCC_z80) || defined(SDCC_z180) || defined(SDCC_r2k) || defined(SDCC_gbz80)
#define _FLOAT_FUNC_REENTRANT
#else
#define _FLOAT_FUNC_REENTRANT __reentrant
#endif

/**********************************************
 * Prototypes for float ANSI C math functions *
 **********************************************/

/* Trigonometric functions */
float sinf(const float x) _FLOAT_FUNC_REENTRANT;
float cosf(const float x) _FLOAT_FUNC_REENTRANT;
float tanf(const float x) _FLOAT_FUNC_REENTRANT;
float cotf(const float x) _FLOAT_FUNC_REENTRANT;
float asinf(const float x) _FLOAT_FUNC_REENTRANT;
float acosf(const float x) _FLOAT_FUNC_REENTRANT;
float atanf(const float x) _FLOAT_FUNC_REENTRANT;
float atan2f(const float x, const float y);

/* Hyperbolic functions */
float sinhf(const float x) _FLOAT_FUNC_REENTRANT;
float coshf(const float x) _FLOAT_FUNC_REENTRANT;
float tanhf(const float x) _FLOAT_FUNC_REENTRANT;

/* Exponential, logarithmic and power functions */
float expf(const float x);
float logf(const float x) _FLOAT_FUNC_REENTRANT;
float log10f(const float x) _FLOAT_FUNC_REENTRANT;
float powf(const float x, const float y);
float sqrtf(const float a) _FLOAT_FUNC_REENTRANT;

/* Nearest integer, absolute value, and remainder functions */
float fabsf(const float x) _FLOAT_FUNC_REENTRANT;
float frexpf(const float x, int *pw2);
float ldexpf(const float x, const int pw2);
float ceilf(float x) _FLOAT_FUNC_REENTRANT;
float floorf(float x) _FLOAT_FUNC_REENTRANT;
float modff(float x, float * y);

#endif  /* _INC_MATH */

