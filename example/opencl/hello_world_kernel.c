#include "syntax.h"

__kernel void HelloWorld(__constant uint64_t * const a, __constant uint64_t * const b, __global uint64_t * const out)
{
    uint idx = get_global_id(0);
    out[idx] = a[idx] + b[idx];
}