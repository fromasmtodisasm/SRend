#include "PhysicalDeviceImpl.hpp"

namespace vulkan
{
  // PhysicalDevice ---------------------------------------------------------------------------------------------------

  vk::PhysicalDeviceProperties PhysicalDevice::getProperties() const
  {
    return pimpl_->getVkPhysicalDevice().getProperties();
  }

  std::vector<PhysicalDeviceFeatures> PhysicalDevice::getFeatures() const
  {
    return pimpl_->getFeatures();
  }

  std::vector<DeviceExtensions> PhysicalDevice::getSupportedDeviceExtensions() const
  {
    return pimpl_->getSupportedExtensions();
  }
}  // namespace vulkan
