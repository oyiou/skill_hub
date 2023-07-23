//
// Created by leever on 2023/5/12.
//

#ifndef C_HELLO_TRIANGLE_H
#define C_HELLO_TRIANGLE_H

#include "vulkan_programing_guide.h"

const int WIDTH = 800;
const int HEIGHT = 600;

const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class HelloTriangleApplication {
public:
    void run();
private:
    GLFWwindow *window;
    VkInstance instance;
private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    VkResult createInstance(const VkInstanceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkInstance *instance);

    VkResult real_vkCreateInstance(const VkInstanceCreateInfo *pInfo, const VkAllocationCallbacks *pCallbacks, VkInstance *instance);
};

#endif //C_HELLO_TRIANGLE_H
