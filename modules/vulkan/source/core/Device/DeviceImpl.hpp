#pragma once
#include "Device.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct DeviceQueues
  {
    vk::Queue graphicQueue;
    vk::Queue computeQueue;
    vk::Queue transferQueue;
  };

  // DeviceImpl -------------------------------------------------------------------------------------------------------

  class DeviceImpl
  {
   public:
    DeviceImpl(Application application, PhysicalDevice physicalDevice);

    ~DeviceImpl();

    [[nodiscard]] vk::Device getVkDevice() const
    {
      return vkDevice_;
    }

    [[nodiscard]] DeviceQueues const& getQueues() const
    {
      return queues_;
    }

   private:
    vk::Device vkDevice_;
    DeviceQueues queues_;
  };

}  // namespace vulkan