#include "image_view_t.hpp"

namespace vulkan
{
	// image_view interface ---------------------------------------------------------------------------------

	image_view create_image_view(image image, image_subresource_range const& range,
		vk::ComponentMapping const& components)
	{
		return std::make_shared<image_view_t>(image, range, components);
	}

	image_view create_image_view(image image)
	{
		return create_image_view(image, { 0, get_mip_levels_count(image), 0, get_array_layers_count(image) });
	}

	vk::Extent3D get_extent(image_view view)
	{
		return get_extent(view->get_image());
	}

	vk::Format get_format(image_view view)
	{
		return view->get_image()->get_format();
	}

	image_subresource_range get_range(image_view view)
	{
		return view->get_range();
	}

	vk::SampleCountFlagBits get_sample_count(image_view view)
	{
		return view->get_image()->get_sample_count();
	}

	void cmd_copy(command_buffer cmd_buf, image_view src_image, image_copy_range const& src_range,
		image_view dst_image, image_copy_range const& dst_range)
	{
		image_copy_range src_range_ = src_range;
		src_range_.range.base_mip_level += get_range(src_image).base_mip_level;
		src_range_.range.base_array_layer += get_range(src_image).base_array_layer;

		image_copy_range dst_range_ = dst_range;
		dst_range_.range.base_mip_level += get_range(dst_image).base_mip_level;
		dst_range_.range.base_array_layer += get_range(dst_image).base_array_layer;

		cmd_copy(cmd_buf, src_image->get_image(), src_range_, dst_image->get_image(), dst_range_);
	}

	void cmd_copy(command_buffer cmd_buf, image_view src_image, image_subresource_range const& src_range,
		image_view dst_image, image_subresource_range const& dst_range)
	{
		cmd_copy(cmd_buf, src_image->get_image(), { get_extent(src_image), {}, src_range },
			dst_image->get_image(), { get_extent(dst_image), {}, dst_range });
	}

	void cmd_copy(command_buffer cmd_buf, image_view src_image, image_view dst_image)
	{
		auto src_range = get_range(src_image);
		auto dst_range = get_range(dst_image);

		cmd_copy(cmd_buf, src_image,
			image_subresource_range{ 0, src_range.level_count, 0, src_range.layer_count }, dst_image,
			image_subresource_range{ 0, dst_range.level_count, 0, dst_range.layer_count });
	}

	void cmd_copy(command_buffer command_buffer, buffer buffer, image_view view,
		image_copy_range const& range)
	{
		image_copy_range copy_range = range;
		copy_range.range.base_mip_level += get_range(view).base_mip_level;
		copy_range.range.base_array_layer += get_range(view).base_array_layer;

		vulkan::cmd_copy(command_buffer, buffer, view->get_image(), copy_range);
	}

	void cmd_copy(command_buffer command_buffer, buffer buffer, image_view view,
		image_subresource_range const& range)
	{
		cmd_copy(command_buffer, buffer, view, { get_extent(view), {}, range });
	}

	void cmd_copy(command_buffer command_buffer, buffer buffer, image_view view)
	{
		cmd_copy(command_buffer, buffer, view, get_range(view));
	}
}