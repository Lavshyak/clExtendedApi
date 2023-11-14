#include <fstream>
#include <utility>
#include <vector>
#include <CL/opencl.hpp>

#ifndef TOOLS_H
#define TOOLS_H
namespace clExtendedApi {
    namespace Tools {

        void getKernelsSources(const std::string &directoryPath,
                               const std::vector<std::string> &kernel_file_names,
                               std::vector<std::string> &kernel_file_contents);

        std::string getClSourceText(const std::string *filePath);

        constexpr const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                         '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

        void toHex(const uint8_t *bin, uint32_t bin_size, char *hex);

        uint8_t char2int(char input);

        void fromHex(const char *hex, uint32_t hex_size, uint8_t *bin);

        void ToHexAndPrint(const uint8_t *binary, size_t binary_size);

        std::string CurrentDateTime();
    }
}


#endif //TOOLS_H