#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>

// Helper function to check for validation layer support
bool checkValidationLayerSupport(const std::vector<const char*>& validationLayers) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;
        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

int main() {
    VkInstance instance;
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Test";
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Enable validation layers
    std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    // Enable portability enumeration
    std::vector<const char*> instanceExtensions = {
        VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
        VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
    };

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Check if validation layers are supported
    if (checkValidationLayerSupport(validationLayers)) {
        std::cout << "Validation layers are supported." << std::endl;
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        std::cerr << "Validation layers requested, but not available!" << std::endl;
    }

    // Enable instance extensions
    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();

    // Enable portability enumeration bit
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (result == VK_SUCCESS) {
        std::cout << "Vulkan instance created successfully!" << std::endl;
    } else {
        std::cerr << "Failed to create Vulkan instance!" << std::endl;

        // Print detailed error message based on VkResult
        switch (result) {
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                std::cerr << "Error: Out of host memory" << std::endl;
                break;
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                std::cerr << "Error: Out of device memory" << std::endl;
                break;
            case VK_ERROR_INITIALIZATION_FAILED:
                std::cerr << "Error: Initialization failed" << std::endl;
                break;
            case VK_ERROR_LAYER_NOT_PRESENT:
                std::cerr << "Error: Layer not present" << std::endl;
                break;
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                std::cerr << "Error: Extension not present" << std::endl;
                break;
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                std::cerr << "Error: Incompatible driver" << std::endl;
                break;
            default:
                std::cerr << "Error: Unknown Vulkan error" << std::endl;
                break;
        }
        return 1;
    }

    vkDestroyInstance(instance, nullptr);

    return 0;
}