#include "framebuffer_t.hpp"
#include "../image_view/image_view_t.hpp"

namespace vulkan
{
	// helpers ----------------------------------------------------------------------------------------------

	std::vector<vk::ImageView> to_vk_attachments(std::vector<image_view> const& attachments)
	{
		std::vector<vk::ImageView> result;
		for (auto const& info : attachments)
		{
			result.push_back(info->get_vk_image_view());
		}
		return result;
	}

	VezFramebuffer create_vk_framebuffer(device device, vk::Extent3D const& extent,
		std::vector<image_view> const& attachments)
	{
		auto vk_attachments = to_vk_attachments(attachments);

		VezFramebufferCreateInfo create_info = {};
		create_info.width = extent.width;
		create_info.height = extent.height;
		create_info.layers = extent.depth;
		create_info.attachmentCount = static_cast<uint32_t>(vk_attachments.size());
		create_info.pAttachments = reinterpret_cast<VkImageView const*>(vk_attachments.data());

		VezFramebuffer result = nullptr;
		check_result(vezCreateFramebuffer(device->get_vk_device(), &create_info, &result));
		return result;
	}

	// impl -------------------------------------------------------------------------------------------------

	framebuffer_t::framebuffer_t(device device, vk::Extent3D const& extent,
		std::vector<image_view> const& attachments) :
		device_(device), attachments_(attachments),
		vk_framebuffer_(create_vk_framebuffer(device, extent, attachments))
	{

	}
}
