#pragma once
#include "ClContextHelper.h"
#include "vector"

namespace clExtendedApi
{
    class OpenclProgramUser {
      protected:
        cl::Program cl_program_;

        ClContextHelper* cl_context_helper_ = nullptr;

        cl::Kernel CreateKernel(const std::string& kernel_name);

      private:
        inline OpenclProgramUser()= default;

      public:
        OpenclProgramUser(ClContextHelper* cl_context, const std::vector<std::string> &kernel_file_names);
        ~OpenclProgramUser();
    };

}
