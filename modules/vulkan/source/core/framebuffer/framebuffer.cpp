#include "../command_buffer/CommandBufferImpl.hpp"
#include "../render_description/render_description_t.hpp"
#include "framebuffer_t.hpp"

namespace vulkan
{
	// framebuffer -------------------------------------------------------------------------------------------

	framebuffer create_framebuffer(device device, vk::Extent3D const& extent,
		std::vector<image_view> const& render_attachments)
	{
		return std::make_shared<framebuffer_t>(device, extent, render_attachments);
	}

	void cmd_begin_render_pass(command_buffer command_buffer, framebuffer framebuffer,
		render_description render_description)
	{
		command_buffer->begin_render_pass(framebuffer->get_vk_framebuffer(),
			render_description->get_vk_attachment_infos());
	}
}