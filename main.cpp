#include "vulkan/VulcanApp.h"
#include <iostream>

int main() {
    try {
        VulkanApp app;
        app.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}