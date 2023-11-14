#include <iostream>
#include "ClContextHelper.h"
#include "Tools.h"

clExtendedApi::ClContextHelper::ClContextHelper(cl::Device &&device_id, std::string *opencl_kernel_sources_directory_path) {
    opencl_kernel_sources_directory_path_ = *opencl_kernel_sources_directory_path;

    device_ = device_id;

    this->context_ = cl::Context(device_id);
    this->commandQueue_ = cl::CommandQueue(this->context_, this->device_);

    WaitClFinish();
}

clExtendedApi::ClContextHelper::~ClContextHelper() {
    WaitClFinish();
}

cl::Program clExtendedApi::ClContextHelper::BuildProgramWith(const std::vector<std::string> &kernel_file_names) {
    //program
    cl_int err;
    std::vector<std::string> kernel_file_contents;
    Tools::getKernelsSources(opencl_kernel_sources_directory_path_, kernel_file_names, kernel_file_contents);

    auto sources = cl::Program::Sources();
    sources.push_back(kernel_file_names[0]);

    cl::Program program(context_, kernel_file_contents, &err);

    std::string options = "-I " + GetOpenclKernelSourcesDirectoryPath();

    std::cout << "Program::build start with " << kernel_file_names[0] << std::endl;

    try {
        program.build(GetDevice(), options.c_str(), nullptr, nullptr);
    } catch (cl::BuildError &buildError) {
        std::cout << "Build error\n";
        std::cout << "Code: " << buildError.err() << std::endl;
        std::cout << "What: " << buildError.what() << std::endl;
        std::cout << "Log: \n" << buildError.getBuildLog()[0].second << std::endl;
        std::cout << "End of log\n";

        throw;
    }

    std::cout << "clBuildProgram end with " << kernel_file_names[0] << std::endl;

    std::cout << "Opencl program built succes\n";

    std::string buildLog = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(GetDevice(), &err);
    if (buildLog != "\n") {
        std::cerr << "Build log:" << std::endl
                  << buildLog << std::endl << "End of build log.\n";
    }

    return program;
}

void clExtendedApi::ClContextHelper::WaitClFinish() {
    commandQueue_.finish();
}