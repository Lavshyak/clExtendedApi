#ifndef RC4GPU_OPENCL_EXAMPLE_SRC_HELLOWORLD_H_
#define RC4GPU_OPENCL_EXAMPLE_SRC_HELLOWORLD_H_

#include "OpenclProgramUser.h"
#include "DeviceBuffer.h"

using namespace clExtendedApi;
class HelloWorld : OpenclProgramUser {
  private:
    DeviceBuffer<uint64_t> d_a_{cl_context_helper_, CL_MEM_READ_ONLY};
    DeviceBuffer<uint64_t> d_b_{cl_context_helper_, CL_MEM_READ_ONLY};
    DeviceBuffer<uint64_t> d_out_{cl_context_helper_, CL_MEM_READ_WRITE};

    static inline const std::vector<std::string> k_kernel_files_names_ = {"hello_world_kernel.c"};
    cl::Kernel kernel_hello_world_;

    size_t elements_count_;

  public:
    explicit HelloWorld(ClContextHelper *cl_context);

    void SetCommonKernelArgs(size_t a_len);
    void Run();

    void GetOut(std::vector<uint64_t>& out);
};

#endif //RC4GPU_OPENCL_EXAMPLE_SRC_HELLOWORLD_H_
