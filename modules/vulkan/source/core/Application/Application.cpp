#include "ApplicationImpl.hpp"
#include "Application.hpp"


namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  ExtensionsFlags getSupportedExtensions()
  {
    ExtensionsFlags result;
    auto extensions = vk::enumerateInstanceExtensionProperties();

    for (auto const& ex : extensions)
    {
      std::string strEx = ex.extensionName;

      if (strEx.find("Surface") != strEx.size())
      {
        result |= ExtensionsFlagBits::Presentation;
      }
    }

    return result;
  }

  ValidationLayersFlags getSupportedValidationLayers()
  {
    ValidationLayersFlags result;
    auto layers = vk::enumerateInstanceLayerProperties();

    for (auto const& layer : layers)
    {
      std::string strLayer = layer.layerName;
      if (strLayer == "VK_LAYER_KHRONOS_validation")
      {
        result |= ValidationLayersFlagBits::StandardValidation;
      }
    }

    return result;
  }

  // Application ------------------------------------------------------------------------------------------------------

  Application::Application(ApplicationInfo const& appInfo, ExtensionsFlags extensions, ValidationLayersFlags layers,
      utils::debug::Messenger const& messenger)
      : pimpl_(std::make_shared<ApplicationImpl>(appInfo, extensions, layers, messenger))
  {
  }

  std::vector<PhysicalDevice> Application::getPhysicalDevices() const
  {
    return pimpl_->getPhysicalDevices();
  }

  PresentationManager Application::getPresentationManager() const
  {
    return PresentationManager();
  }

}  // namespace vulkan
