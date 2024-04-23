#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <boost/format.hpp>
#include "VulkanApplication.h"

int main()
{
    const auto app = std::make_unique<VulkanApplication>(1280, 720, "Hello Vulkan!");

    try
    {
        app->run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
