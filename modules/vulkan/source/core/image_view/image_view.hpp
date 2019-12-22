#pragma once
#include "../image/image.hpp"

namespace vulkan
{
	// image_view --------------------------------------------------------------------------------------------

	class image_view_t;
	using image_view = std::shared_ptr<image_view_t>;

	image_view create_image_view(image image, image_subresource_range const& range,
		vk::ComponentMapping const& components = {});

	image_view create_image_view(image image);

	image_view create_image_view(image image);

	vk::Extent3D get_extent(image_view view);

	vk::Format get_format(image_view view);

	image_subresource_range get_range(image_view view);

	vk::SampleCountFlagBits get_sample_count(image_view view);

	void cmd_copy(command_buffer cmd_buf, image_view src_image, image_copy_range const& src_range, 
		image_view dst_image, image_copy_range const& dst_range);

	void cmd_copy(command_buffer cmd_buf, image_view src_image, image_subresource_range const& src_range,
		image_view dst_image, image_subresource_range const& dst_range );

	void cmd_copy(command_buffer cmd_buf, image_view src_image, image_view dst_image);

	void cmd_copy(command_buffer command_buffer, buffer buffer, image_view view,
		image_copy_range const& range);

	void cmd_copy(command_buffer command_buffer, buffer buffer, image_view view,
		image_subresource_range const& range);

	void cmd_copy(command_buffer command_buffer, buffer buffer, image_view view);
}