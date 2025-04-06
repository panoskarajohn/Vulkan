#include "VulcanApp.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

VulkanApp::VulkanApp() 
    : validationLayers{"VK_LAYER_KHRONOS_validation"},
      instanceExtensions{
          VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
          VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME} {}

VulkanApp::~VulkanApp() {
    cleanup();
}

void VulkanApp::run() {
    createInstance();
    std::cout << "Vulkan application is running!" << std::endl;
}

bool VulkanApp::checkValidationLayerSupport() {
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

void VulkanApp::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Test";
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    if (checkValidationLayerSupport()) {
        std::cout << "Validation layers are supported." << std::endl;
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        std::cerr << "Validation layers requested, but not available!" << std::endl;
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance");
    }

    std::cout << "Vulkan instance created successfully!" << std::endl;
}

void VulkanApp::cleanup() {
    if (instance) {
        vkDestroyInstance(instance, nullptr);
        instance = nullptr;
    }
}