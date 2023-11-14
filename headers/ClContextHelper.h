#ifndef CL_CONTEXT_HELPER_H
#define CL_CONTEXT_HELPER_H

#include <cstdint>
#include <string>
#include "Tools.h"
#include <vector>

namespace clExtendedApi {
    class ClContextHelper {
      private:
        cl::Device device_;
        cl::Context context_;
        cl::CommandQueue commandQueue_;
        std::string opencl_kernel_sources_directory_path_;

      public:
        ClContextHelper(cl::Device &&device_id, std::string *opencl_kernel_sources_directory_path);
        ~ClContextHelper();

        cl::Program BuildProgramWith(const std::vector<std::string> &kernel_file_names);

        inline const cl::Device &GetDevice() {
            return device_;
        }

        inline const cl::Context &GetContext() {
            return context_;
        }

        inline const cl::CommandQueue &GetCommandQueue() {
            return commandQueue_;
        }

        inline std::string &GetOpenclKernelSourcesDirectoryPath() {
            return opencl_kernel_sources_directory_path_;
        }

        void WaitClFinish();
    };
}
//#include "ClContextHelper.tpp"
#endif //CL_CONTEXT_HELPER_H