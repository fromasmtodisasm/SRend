#include <regex>
#include "shader_t.hpp"

namespace vulkan
{
  // utils
  // -------------------------------------------------------------------------------------------------

  vk::ShaderStageFlagBits pick_stage_from_str(std::string const& file_format)
  {
    if (file_format == "vert")
    {
      return vk::ShaderStageFlagBits::eVertex;
    }
    if (file_format == "frag")
    {
      return vk::ShaderStageFlagBits::eFragment;
    }
    throw std::runtime_error("invalid Shader file format");
  }

  vk::ShaderStageFlagBits pick_stage(std::filesystem::path const& path)
  {
    std::regex regex("([[:alpha:]]+)(.)(vert|frag)");
    std::string filename = path.filename().string();
    std::smatch result;

    if (std::regex_search(filename, result, regex))
    {
      return pick_stage_from_str(result[3].str());
    }
    throw std::runtime_error("specified defective path to Shader");
  }

  // shader_module
  // -----------------------------------------------------------------------------------------

  shader create_shader(device device, vk::ShaderStageFlagBits stage, std::string const& code)
  {
    return std::make_shared<shader_t>(device, stage, code);
  }

  shader create_shader(device device, vk::ShaderStageFlagBits stage, std::istream& is)
  {
    return create_shader(device, stage, utils::readIsToString(is));
  }

  shader create_shader(device device, std::filesystem::path const& shader_path)
  {
    return create_shader(device, pick_stage(shader_path), utils::readFileToString(shader_path));
  }
}  // namespace vulkan