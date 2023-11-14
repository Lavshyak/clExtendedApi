#include <string>
#include <iostream>
#include "ClContextHelper.h"
#include "Queries.h"
#include "HelloWorld.h"
using namespace clExtendedApi;
int main()
{
    std::string opencl_files_directory = R"(opencl)";
    ClContextHelper
        cl_context_helper(queries::GetDeviceBy(1, 0),
                          &opencl_files_directory);
    HelloWorld hello_world(&cl_context_helper);

    hello_world.SetCommonKernelArgs(1000);
    hello_world.Run();
    std::vector<uint64_t> out;
    hello_world.GetOut(out);

    for(size_t i = 0; i < 1000; i++)
    {
        if(out[i] != i*2)
        {
            throw std::exception();
        }
    }

    std::cout << "ok, end." << std::endl;

    return 0;
}