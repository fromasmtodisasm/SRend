#pragma once
#include <utils/debug.hpp>
#include "../PhysicalDevice/PhysicalDevice.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  // clang-format off

  SR_MAKE_BIT_FLAGS(Extensions, {
    Presentation = 1u << 0u
  };)

  SR_MAKE_BIT_FLAGS(ValidationLayers, {
    StandardValidation = 1u << 0u
  };)

  // clang-format on

  ExtensionsFlags getSupportedExtensions();

  ValidationLayersFlags getSupportedValidationLayers();

  struct ApplicationInfo
  {
    ApplicationInfo() = default;

    explicit ApplicationInfo(
        std::string appName, utils::VersionList appVersion, std::string engineName, utils::VersionList engineVersion)
        : appName(std::move(appName)),
          appVersion(std::move(appVersion)),
          engineName(std::move(engineName)),
          engineVersion(std::move((engineVersion)))
    {
    }

    std::string appName;
    utils::VersionList appVersion;
    std::string engineName;
    utils::VersionList engineVersion;
  };

  // Application ------------------------------------------------------------------------------------------------------

  class ApplicationImpl;

  class Application
  {
   public:
    explicit Application(std::shared_ptr<ApplicationImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<ApplicationImpl> getImpl() const
    {
      return pimpl_;
    }

    explicit Application(ApplicationInfo const& appInfo, ExtensionsFlags extensions = {},
        ValidationLayersFlags layers = {}, utils::debug::Messenger const& messenger = utils::debug::Messenger{});

    [[nodiscard]] std::vector<PhysicalDevice> getPhysicalDevices() const;

   private:
    std::shared_ptr<ApplicationImpl> pimpl_;
  };

}  // namespace vulkan