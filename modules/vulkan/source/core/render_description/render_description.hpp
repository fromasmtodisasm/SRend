#pragma once
#include <variant>
#include "../Device/Device.hpp"

namespace vulkan
{
	class render_description_t;
	using render_description = std::shared_ptr<render_description_t>;

	// utils ------------------------------------------------------------------------------------------------

	struct color_clear_value
	{
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
	};

	struct depth_clear_value
	{
		float depth = 1.0f;
		uint32_t stensil = 0;
	};

	struct attachment_info
	{
		std::variant<color_clear_value, depth_clear_value> clear_value;
		vk::AttachmentLoadOp load_op;
		vk::AttachmentStoreOp store_op;
	};

	// render_description -----------------------------------------------------------------------------------

	render_description create_render_description(device device,
		std::vector<attachment_info> const& attachment_infos);
}