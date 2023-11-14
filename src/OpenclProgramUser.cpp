#include "OpenclProgramUser.h"
#include "Tools.h"

clExtendedApi::OpenclProgramUser::OpenclProgramUser(ClContextHelper* cl_context, const std::vector<std::string> &kernel_file_names)
: cl_context_helper_(cl_context){
	cl_program_ = cl_context_helper_->BuildProgramWith(kernel_file_names);
}

clExtendedApi::OpenclProgramUser::~OpenclProgramUser() {
	cl_context_helper_->WaitClFinish();
}

cl::Kernel clExtendedApi::OpenclProgramUser::CreateKernel(const std::string& kernel_name) {

	auto kernel = cl::Kernel(cl_program_, kernel_name.c_str(), nullptr);

	return kernel;
}
