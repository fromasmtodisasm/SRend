#include "render_description_t.hpp"

namespace vulkan
{
	// utils ------------------------------------------------------------------------------------------------

	VkClearValue to_vk_clear_value(attachment_info const& info)
	{
		VkClearValue result = {};

		if (std::holds_alternative<color_clear_value>(info.clear_value))
		{
			auto clear_value = std::get<color_clear_value>(info.clear_value);
			result.color = { clear_value.r, clear_value.g, clear_value.b };
		}
		else
		{
			auto clear_value = std::get<depth_clear_value>(info.clear_value);
			result.depthStencil = { clear_value.depth, clear_value.stensil };
		}
		return result;
	}

	std::vector<VezAttachmentInfo> to_vk_attachment_infos(
		std::vector<attachment_info> const& attachment_infos)
	{
		std::vector<VezAttachmentInfo> result;
		for (auto const& info : attachment_infos)
		{
			result.push_back({ static_cast<VkAttachmentLoadOp>(info.load_op),
				static_cast<VkAttachmentStoreOp>(info.store_op), to_vk_clear_value(info) });
		}
		return result;
	}

	// render_description_t ---------------------------------------------------------------------------------

	render_description_t::render_description_t(std::vector<attachment_info> const& attachment_infos) :
		vk_attachment_infos_(to_vk_attachment_infos(attachment_infos))
	{
	}
}
