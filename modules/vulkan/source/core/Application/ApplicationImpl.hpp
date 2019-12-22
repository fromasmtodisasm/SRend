#pragma once
#include "Application.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  using UniqueVkDebugMessenger = vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic>;

  // ApplicationImpl --------------------------------------------------------------------------------------------------

  class ApplicationImpl
  {
   public:
    ApplicationImpl(ApplicationInfo const& appInfo, ExtensionsFlags extensions, ValidationLayersFlags layers,
        utils::debug::Messenger messenger);

    ~ApplicationImpl();

    [[nodiscard]] ExtensionsFlags getEnabledExtensions() const
    {
      return enabledExtensions_;
    }

    [[nodiscard]] vk::Instance getVkInstance() const
    {
      return vkInstance_;
    }

    [[nodiscard]] vk::DispatchLoaderDynamic const& getVkDllLoader() const
    {
      return vkDllLoader_;
    }

    [[nodiscard]] std::vector<PhysicalDevice> const& getPhysicalDevices() const
    {
      return physicalDevices_;
    }

   private:
    ExtensionsFlags enabledExtensions_;
    vk::Instance vkInstance_;
    vk::DispatchLoaderDynamic vkDllLoader_;
    utils::debug::Messenger messenger_;
    UniqueVkDebugMessenger vkDebugMessenger_;
    std::vector<PhysicalDevice> physicalDevices_;
  };

}  // namespace vulkan