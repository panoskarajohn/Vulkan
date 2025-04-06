#ifndef VULKAN_APP_H
#define VULKAN_APP_H

#include <vector>
#include <vulkan/vulkan.h>
#include <string>


class VulkanApp {
public:
    VulkanApp();
    ~VulkanApp();

    void run();

private:
    VkInstance instance;

    std::vector<const char *> validationLayers;
    std::vector<const char *> instanceExtensions;

    bool checkValidationLayerSupport();
    void createInstance();
    void cleanup();
    
};

#endif