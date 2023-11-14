#ifndef CLION_DEFINES_CL
#define CLION_DEFINES_CL

#ifdef __CLION_IDE__

    #include "stdio.h"

#define __kernel

#define __private
#define __local
#define __global
#define __generic

#define __constant const


/* Note: long is *always* 64-bit in OpenCL */

//8bit
typedef unsigned char uchar;
//16bit
typedef unsigned short ushort;
//32bit
typedef unsigned int uint;
//64bit
typedef unsigned long ulong;
//64_32 bit
typedef unsigned long size_t;

typedef uint atomic_uint;

typedef int ptrdiff_t;
typedef atomic_uint *atomic_uintptr_t;

//костыль
static uint fuu;
//костыль
//#define atomic_fetch_add(ptr,val) fuu
uint atomic_fetch_add(atomic_uintptr_t a, ptrdiff_t p) {
  return *a;
}

typedef void *uintptr_t;

typedef uchar bool;
#define true 1
#define false 0

void foo() {
  //8bit
  bool b = true || false;
  //8bit
  char c;
  unsigned char uc;
  uchar uuc;
  //16bit
  short s;
  unsigned short us;
  ushort uus;
  //32bit
  int i;
  unsigned int ui;
  uint uui;
  //64bit
  long l;
  unsigned long ul;
  ulong uul;

  //32bit
  float f;
  //64bit
  double d;
  //32 or 64 bit
  size_t st;
}

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef float half;

typedef struct float2 { float x; } float2;
typedef struct float3 { float x, y, z; } float3;
typedef struct float4 { float x, y, z, w; } float4;

// https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/commonFunctions.html
typedef void *gentype;
gentype clamp(gentype x, float minval, float maxval);
gentype degrees(gentype radians);
gentype max(gentype x, gentype y);
gentype min(gentype x, gentype y);
gentype mix(gentype x, gentype y, gentype a);
gentype radians(gentype degrees);
gentype sign(gentype x);
gentype smoothstep(gentype edge0, gentype edge1, gentype x);
gentype step(gentype edge, gentype x);

// https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/barrier.html
typedef enum cl_mem_fence_flags {
  CLK_LOCAL_MEM_FENCE,
  CLK_GLOBAL_MEM_FENCE
} cl_mem_fence_flags;
void barrier(cl_mem_fence_flags flags);

// https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/vectorDataLoadandStoreFunctions.html
#define gentypen float4

gentype rotate(gentype a, gentype b);
gentype bitselect(gentype a, gentype b, gentype c);

gentypen vload4(size_t offset, const gentype *p);
void vstore4(gentypen data, size_t offset, gentype *p);
void vstore4(gentypen data, size_t offset, gentype *p);
#undef gentypen
float vload_half(size_t offset, const half *p);
float4 vload_half4(size_t offset, const half *p);
void vstore_half(float data, size_t offset, half *p);
void vstore_half4(float4 data, size_t offset, half *p);
float4 vloada_half4(size_t offset, const half *p);
void vstorea_half4(float4 data, size_t offset, half *p);

// https://www.khronos.org/registry/OpenCL/sdk/1.2/docs/man/xhtml/workItemFunctions.html
uint get_work_dim();
size_t get_global_size(uint dimindx);
size_t get_global_id(uint dimindx);
size_t get_local_size(uint dimindx);
size_t get_local_id(uint dimindx);
size_t get_num_groups(uint dimindx);
size_t get_group_id(uint dimindx);
size_t get_global_offset(uint dimindx);

#ifndef STATIC_KEYWORD
#define STATIC_KEYWORD static
#endif

#endif

#endif //CLION_DEFINES_CL
