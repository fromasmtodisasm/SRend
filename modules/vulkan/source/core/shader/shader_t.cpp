#include "shader_t.hpp"

namespace vulkan
{
  // helpers
  // ----------------------------------------------------------------------------------------------

  vk::ShaderModule create_vk_shader_module(
      device device, vk::ShaderStageFlagBits stage, std::string const& code)
  {
    VezShaderModuleCreateInfo moduleCreateInfo = {};
    moduleCreateInfo.stage = static_cast<VkShaderStageFlagBits>(stage);
    moduleCreateInfo.pCode = reinterpret_cast<uint32_t const*>(code.data());
    moduleCreateInfo.codeSize = code.size();
    moduleCreateInfo.pEntryPoint = "main";

    VkShaderModule result = nullptr;
    if (vezCreateShaderModule(device->get_vk_device(), &moduleCreateInfo,
            reinterpret_cast<VkShaderModule*>(&result)) != VK_SUCCESS)
    {
      throw std::runtime_error("failed to create Shader module");
    }
    return result;
  }

  // shader_module impl
  // -----------------------------------------------------------------------------------

  vulkan::shader_t::shader_t(device device, vk::ShaderStageFlagBits stage, std::string const& code)
      : device_(device), vk_shader_module_(create_vk_shader_module(device, stage, code))
  {
  }
}  // namespace vulkan