#pragma once
#include "../Device/DeviceImpl.hpp"
#include "shader.hpp"

namespace vulkan
{
	class shader_t
	{
	public:
		shader_t(device device, vk::ShaderStageFlagBits stage, std::string const& source);

		~shader_t()
		{
			vezDestroyShaderModule(device_->get_vk_device(), vk_shader_module_);
		}

		device get_device() const
		{
			return device_;
		}

		vk::ShaderModule get_vk_shader_module() const
		{
			return vk_shader_module_;
		}
	private:
		device device_;
		vk::ShaderModule vk_shader_module_;
	};
}