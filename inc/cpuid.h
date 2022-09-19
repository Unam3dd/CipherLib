#ifndef CPUID_H
#define CPUID_H

//////////////////////////////////
//
//			CPUID
//
//////////////////////////////////

#define cpuid(func,ax,bx,cx,dx)\
 __asm__ __volatile__ ("cpuid":\
 "=a" (ax), "=b" (bx), "=c" (cx), "=d" (dx) : "a" (func));

#endif
