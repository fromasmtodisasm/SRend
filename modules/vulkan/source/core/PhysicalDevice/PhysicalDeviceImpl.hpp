#pragma once
#include "PhysicalDevice.hpp"

namespace vulkan
{
  // PhysicalDeviceImpl -----------------------------------------------------------------------------------------------

  class PhysicalDeviceImpl
  {
   public:
    explicit PhysicalDeviceImpl(vk::PhysicalDevice vkPhysicalDevice);

    [[nodiscard]] vk::PhysicalDevice getVkPhysicalDevice() const
    {
      return vk_physical_device_;
    }

    [[nodiscard]] std::vector<PhysicalDeviceFeatures> getFeatures() const
    {
      return features_;
    }

    [[nodiscard]] std::vector<DeviceExtensions> getSupportedExtensions() const
    {
      return extensions_;
    }

   private:
    vk::PhysicalDevice vk_physical_device_;
    std::vector<PhysicalDeviceFeatures> features_;
    std::vector<DeviceExtensions> extensions_;
  };

}  // namespace vulkan