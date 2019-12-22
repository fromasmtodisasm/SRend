#include "sampler_t.hpp"
#include "../image_view/image_view_t.hpp"

namespace vulkan
{
	// sampler -----------------------------------------------------------------------------------------------

	sampler create_sampler(device device, sampler_parameters const& parameters)
	{
		return std::make_shared<sampler_t>(device, parameters);
	}

	void cmd_bind(command_buffer command_buffer, binding_info const& binding_info, image_view image_view,
		sampler sampler)
	{
		vezCmdBindImageView(image_view->get_vk_image_view(), sampler->get_vk_sampler(), binding_info.set,
			binding_info.binding, binding_info.index);
	}
}