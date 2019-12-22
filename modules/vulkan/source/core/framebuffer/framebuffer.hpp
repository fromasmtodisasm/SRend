#pragma once
#include "../render_description/render_description.hpp"
#include "../image_view/image_view.hpp"

namespace vulkan
{
	class framebuffer_t;
	using framebuffer = std::shared_ptr<framebuffer_t>;

	// framebuffer -------------------------------------------------------------------------------------------

	framebuffer create_framebuffer(device device, vk::Extent3D const& extent,
		std::vector<image_view> const& render_attachments);

	void cmd_begin_render_pass(command_buffer command_buffer, framebuffer framebuffer,
		render_description render_description);
}