#include <iostream>
#include <iomanip>
#include "Tools.h"
#include <vector>
#include <ctime>

void clExtendedApi::Tools::getKernelsSources(const std::string& directoryPath, const std::vector<std::string>& kernel_file_names, std::vector<std::string>& kernel_file_contents) {

	for(auto kernel_file_name : kernel_file_names)
	{
		std::string filePath = directoryPath + '\\' + kernel_file_name;
		kernel_file_contents.push_back(Tools::getClSourceText(&filePath));
	}
}

std::string clExtendedApi::Tools::getClSourceText(const std::string *filePath) {
	auto program_handle = fopen(filePath->c_str(), "rb");
	int bufferSize = 500000;
	char *buffer = new char[bufferSize];
	size_t readed_size = fread(buffer, sizeof(char), bufferSize, program_handle);

	auto text = std::string(buffer, readed_size);

	delete[] buffer;

	return text;
}



void clExtendedApi::Tools::toHex(const uint8_t *bin, uint32_t bin_size, char *hex) {
	for (uint32_t i = 0; i < bin_size; ++i) {
		hex[2 * i] = hexmap[(bin[i] & 0xF0) >> 4];
		hex[2 * i + 1] = hexmap[bin[i] & 0x0F];
	}
}

uint8_t clExtendedApi::Tools::char2int(char input) {
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	throw std::invalid_argument("Invalid input string");
}

void clExtendedApi::Tools::fromHex(const char *hex, uint32_t hex_size, uint8_t *bin) {
	hex_size /= 2;
	for (uint32_t i = 0; i < hex_size; i++) {
		bin[i] = char2int(hex[2 * i]) * 16 + char2int(hex[2 * i + 1]);
	}
}

void clExtendedApi::Tools::ToHexAndPrint(const uint8_t *binary, size_t binary_size) {
	std::ios_base::fmtflags f(std::cout.flags());  // save flags state
	std::cout << std::hex;
	for (size_t i = 0; i < binary_size; i++) {
		std::cout << std::setfill('0') << std::setw(2) << (int) binary[i] << ' ';
	}
	std::cout.flags(f);  // restore flags state
	std::cout << std::endl;
}

std::string clExtendedApi::Tools::CurrentDateTime() {
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	char buffer[128];
	strftime(buffer, sizeof(buffer), "%X", now);
	return buffer;
}