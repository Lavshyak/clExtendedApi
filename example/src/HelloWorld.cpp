#include <iostream>
#include "HelloWorld.h"
HelloWorld::HelloWorld(ClContextHelper *cl_context) : OpenclProgramUser(cl_context, k_kernel_files_names_) {
    kernel_hello_world_ = CreateKernel("HelloWorld");
}
void HelloWorld::SetCommonKernelArgs(size_t a_len) {
    d_a_.Resize(a_len);
    d_a_.Resize(a_len);
    d_b_.Resize(a_len);

    std::vector<uint64_t> arr;
    for(uint64_t i = 0; i < a_len; i++)
    {
        arr.push_back(i);
    }

    d_a_.WriteFrom(arr.data());
    d_b_.WriteFrom(arr.data());

    kernel_hello_world_.setArg(0, d_a_.GetBuffer());
    kernel_hello_world_.setArg(1, d_b_.GetBuffer());
    kernel_hello_world_.setArg(2, d_out_.GetBuffer());

    elements_count_ = a_len;
}
void HelloWorld::Run() {
    cl_context_helper_->GetCommandQueue()
        .enqueueNDRangeKernel(kernel_hello_world_,
                              0,
                              cl::NDRange(elements_count_),
                              cl::NullRange,
                              nullptr,
                              nullptr);

    try {
        cl_context_helper_->WaitClFinish();
    }
    catch (cl::Error &err) {
        std::cout << "Unknown error, may be in gpu code. This is bad and serious." << std::endl;
        throw;
    }
}
void HelloWorld::GetOut(std::vector<uint64_t> &out) {
    out.resize(elements_count_);
    d_out_.ReadTo(out.data());
}
