#pragma once

#include <vulkan/vulkan.h>

#include <array>
#include <vector>

struct PerFrameData
{
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    VkFence fence;
    VkSemaphore imageAcquiredSemaphore;
};

struct PerImageData
{
    VkImageView imageView;
    VkFramebuffer framebuffer;

    VkSemaphore renderCompleteSemaphore;
};

class RendererBase
{
public:
    static constexpr size_t MAX_FRAMES_IN_FLIGHT = 2;
protected:
    RendererBase();
    RendererBase(const RendererBase&) = delete;
    RendererBase(RendererBase&&);
    ~RendererBase();

    RendererBase& operator=(const RendererBase&) = delete;
    RendererBase& operator=(RendererBase&&);

    struct {
        VkInstance instance;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice;
        uint32_t queueFamilyIndex;

        VkDevice device;
        VkQueue queue;

        VkRenderPass renderPass;

        uint32_t frameIndex;
        std::array<PerFrameData, MAX_FRAMES_IN_FLIGHT> perFrame;

        VkExtent2D swapchainSize;
        VkSwapchainKHR swapchain;
        std::vector<PerImageData> perImage;
    } _d;
};