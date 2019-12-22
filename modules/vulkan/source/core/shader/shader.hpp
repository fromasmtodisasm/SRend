#pragma once
#include "../Device/Device.hpp"

namespace vulkan
{
  class shader_t;
  using shader = std::shared_ptr<shader_t>;

  // shader_module
  // -----------------------------------------------------------------------------------------

  shader create_shader(device device, vk::ShaderStageFlagBits stage, std::string const& code);

  shader create_shader(device device, vk::ShaderStageFlagBits stage, std::istream& is);

  shader create_shader(device device, std::filesystem::path const& shader_path);
}  // namespace vulkan