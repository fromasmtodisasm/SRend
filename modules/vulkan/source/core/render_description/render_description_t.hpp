#pragma once
#include "render_description.hpp"
#include <VEZ/VEZ.h>

namespace vulkan
{
	// render_description_t ---------------------------------------------------------------------------------

	class render_description_t
	{
	public:
		render_description_t(std::vector<attachment_info> const& attachment_infos);

		std::vector<VezAttachmentInfo> get_vk_attachment_infos() const
		{
			return vk_attachment_infos_;
		}

	private:
		std::vector<VezAttachmentInfo> vk_attachment_infos_;
	};
}