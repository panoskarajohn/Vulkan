#pragma once

#define GLFW_INCLUDE_VULCAN
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>
#include <vulkan/vulkan.h>
#include <string>


class VulkanApp {
public:
    VulkanApp();
    ~VulkanApp();

    void run();

private:
    GLFWwindow* window;
    VkInstance instance;

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    std::vector<const char *> validationLayers;
    std::vector<const char *> instanceExtensions;

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    bool checkValidationLayerSupport();
    void createInstance();
    
};
