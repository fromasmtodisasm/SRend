#include "render_description_t.hpp"

namespace vulkan
{
	// render_description -----------------------------------------------------------------------------------

	render_description vulkan::create_render_description(device,
		std::vector<attachment_info> const& attachment_infos)
	{
		return std::make_shared<render_description_t>(attachment_infos);
	}
}
