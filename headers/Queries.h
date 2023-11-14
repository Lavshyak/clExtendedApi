#pragma once

#include "Tools.h"
namespace clExtendedApi {
    namespace queries {
        using namespace Tools;

        void QueryPlatform();

        cl::Device GetDeviceBy(size_t platform_idx, size_t device_idx);

        [[maybe_unused]] void SetPlatform(cl_platform_id &platform);

        [[maybe_unused]] void SetDevice(cl_platform_id *platform, cl_device_id &device);

    }
}
