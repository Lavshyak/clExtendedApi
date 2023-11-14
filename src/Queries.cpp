#include <iostream>
#include "Queries.h"

// The code below may be stolen from the Internet. be careful

void clExtendedApi::queries::QueryPlatform() {
  //get platforms count
  cl_uint platform_count;
  clGetPlatformIDs(0, nullptr, &platform_count);
  printf("platforms count: '%u' \n", platform_count);

  //get platforms
  auto *platforms = new cl_platform_id[platform_count];
  clGetPlatformIDs(platform_count, platforms, nullptr);

  for (int i_platform = 0; i_platform < platform_count; i_platform++) {
	char *platform_info_value;
	size_t platform_info_value_size;
	clGetPlatformInfo(platforms[i_platform], CL_PLATFORM_NAME, 0, nullptr, &platform_info_value_size);
	platform_info_value = (char *)malloc(platform_info_value_size);
	clGetPlatformInfo(platforms[i_platform], CL_PLATFORM_NAME, platform_info_value_size, platform_info_value, nullptr);
	printf("%d. Platform: %s\n", i_platform, platform_info_value);
	free(platform_info_value);

	cl_uint device_count;
	clGetDeviceIDs(platforms[i_platform], CL_DEVICE_TYPE_ALL, 0, nullptr, &device_count);
	auto devices = new cl_device_id[device_count];
	clGetDeviceIDs(platforms[i_platform], CL_DEVICE_TYPE_ALL, device_count, devices, nullptr);

	printf("devices count: '%u' \n", device_count);

	for (int i_device = 0; i_device < device_count; i_device++) {
	  char *device_info_value;
	  size_t device_info_value_size;

	  // print device name
	  clGetDeviceInfo(devices[i_device], CL_DEVICE_NAME, 0, nullptr, &device_info_value_size);
	  device_info_value = (char *)malloc(device_info_value_size);
	  clGetDeviceInfo(devices[i_device], CL_DEVICE_NAME, device_info_value_size, device_info_value, nullptr);
	  printf("%d. Device: %s\n", i_device, device_info_value);
	  free(device_info_value);

	  // print hardware device version
	  clGetDeviceInfo(devices[i_device], CL_DEVICE_VERSION, 0, nullptr, &device_info_value_size);
	  device_info_value = (char *)malloc(device_info_value_size);
	  clGetDeviceInfo(devices[i_device], CL_DEVICE_VERSION, device_info_value_size, device_info_value, nullptr);
	  printf(" %d.%d Hardware version: %s\n", i_device, 1, device_info_value);
	  free(device_info_value);

	  // print software driver version
	  clGetDeviceInfo(devices[i_device], CL_DRIVER_VERSION, 0, nullptr, &device_info_value_size);
	  device_info_value = (char *)malloc(device_info_value_size);
	  clGetDeviceInfo(devices[i_device], CL_DRIVER_VERSION, device_info_value_size, device_info_value, nullptr);
	  printf(" %d.%d Software version: %s\n", i_device, 2, device_info_value);
	  free(device_info_value);

	  // print c version supported by compiler for device
	  clGetDeviceInfo(devices[i_device], CL_DEVICE_OPENCL_C_VERSION, 0, nullptr, &device_info_value_size);
	  device_info_value = (char *)malloc(device_info_value_size);
	  clGetDeviceInfo(devices[i_device],
					  CL_DEVICE_OPENCL_C_VERSION,
					  device_info_value_size,
					  device_info_value,
					  nullptr);
	  printf(" %d.%d OpenCL C version: %s\n", i_device, 3, device_info_value);
	  free(device_info_value);

	  // print parallel compute units
	  cl_uint max_compute_units;
	  clGetDeviceInfo(devices[i_device], CL_DEVICE_MAX_COMPUTE_UNITS,
					  sizeof(max_compute_units), &max_compute_units, nullptr);
	  printf(" %d.%d Parallel compute units: %d\n", i_device, 4, max_compute_units);
	}

	free(devices);
  }

  free(platforms);
}

[[maybe_unused]] void clExtendedApi::queries::SetPlatform(cl_platform_id &platform) {
  clGetPlatformIDs(1, &platform, nullptr);
}

[[maybe_unused]] void clExtendedApi::queries::SetDevice(cl_platform_id *platform, cl_device_id &device) {
  clGetDeviceIDs(*platform, CL_DEVICE_TYPE_GPU, 1, &device, nullptr);
}



cl::Device clExtendedApi::queries::GetDeviceBy(size_t platform_idx, size_t device_idx) {
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);

	if (all_platforms.size()==0) {
		std::cout<<" No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform platform=all_platforms[platform_idx];
	std::cout << "Using platform: " << platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	// get default device (CPUs, GPUs) of the default platform
	std::vector<cl::Device> all_devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if(all_devices.size()==0){
		std::cout<<" No devices found. Check OpenCL installation!\n";
		exit(1);
	}

	// use device[1] because that's a GPU; device[0] is the CPU
	cl::Device device=all_devices[device_idx];
	std::cout << "Using device: " << device.getInfo<CL_DEVICE_NAME>() << "\n";

	return device;
}