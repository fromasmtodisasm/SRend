#include "DeviceImpl.hpp"
#include <VEZ.h>
#include "../../utils.hpp"
#include "../Application/ApplicationImpl.hpp"
#include "../PhysicalDevice/PhysicalDeviceImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  std::vector<char const*> getVkDeviceExtensions(ExtensionsFlags extensions)
  {
    std::vector<char const*> result;

    if (extensions & ExtensionsFlagBits::Presentation)
    {
      result.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }

    return result;
  }

  vk::Device createVkDevice(const PhysicalDevice& physicalDevice, ExtensionsFlags extensions)
  {
    auto vkExtensions = getVkDeviceExtensions(extensions);

    VezDeviceCreateInfo createInfo = {};
    createInfo.enabledExtensionCount = static_cast<uint32_t>(vkExtensions.size());
    createInfo.ppEnabledExtensionNames = vkExtensions.data();

    VkDevice vkDevice = nullptr;
    checkResult(vezCreateDevice(physicalDevice.getImpl()->getVkPhysicalDevice(), &createInfo, &vkDevice));
    return vkDevice;
  }

  DeviceQueues createQueues(vk::Device device)
  {
    DeviceQueues result;

    vezGetDeviceGraphicsQueue(device, 0, reinterpret_cast<VkQueue*>(&result.graphicQueue));
    vezGetDeviceComputeQueue(device, 0, reinterpret_cast<VkQueue*>(&result.computeQueue));
    vezGetDeviceTransferQueue(device, 0, reinterpret_cast<VkQueue*>(&result.transferQueue));

    return result;
  }

  // device_t ---------------------------------------------------------------------------------------------------------

  DeviceImpl::DeviceImpl(Application application, PhysicalDevice physicalDevice)
      : vkDevice_(createVkDevice(physicalDevice, application.getImpl()->getEnabledExtensions())),
        queues_(createQueues(vkDevice_))
  {
  }

  DeviceImpl::~DeviceImpl()
  {
    vezDestroyDevice(vkDevice_);
  }

}  // namespace vulkan
