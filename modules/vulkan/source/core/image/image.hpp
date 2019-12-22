#pragma once
#include "../buffer_manager/buffer_manager.hpp"
#include "../command_buffer/CommandBuffer.hpp"

namespace vulkan
{
	class image_t;
	using image = std::shared_ptr<image_t>;

	// utils classes ----------------------------------------------------------------------------------------
	
	struct image_subresource_range
	{
		uint32_t base_mip_level;
		uint32_t level_count;
		uint32_t base_array_layer;
		uint32_t layer_count;
	};

	struct image_copy_range
	{
		vk::Extent3D extent;
		vk::Offset3D offset;
		image_subresource_range range;
	};

	// image interface --------------------------------------------------------------------------------------

	image create_image(device device, vk::Format format, vk::ImageUsageFlags usage,
		vk::Extent3D const& extent, vk::ImageCreateFlags create_flags = {}, uint32_t array_layers = 1, 
		uint32_t mip_levels = 1, vk::SampleCountFlagBits sample_count = vk::SampleCountFlagBits::e1,
		memory_usage memory_usage = memory_usage::gpu, vk::ImageTiling tiling = vk::ImageTiling::eOptimal);

	vk::Format get_format(image image);

	vk::Extent3D get_extent(image image);

	uint32_t get_array_layers_count(image image);

	uint32_t get_mip_levels_count(image image);

	vk::SampleCountFlagBits get_sample_count(image image);

	void cmd_copy(command_buffer command_buffer, image src_image, image_copy_range const& src_range, 
		image dst_image, image_copy_range const& dst_range);

	void cmd_copy(command_buffer command_buffer, image src_image,
		image_subresource_range const& src_range, image dst_image, image_subresource_range const& dst_range);

	void cmd_copy(command_buffer command_buffer, image src_image, image dst_image);

	void cmd_copy(command_buffer command_buffer, buffer buffer, image image,
		image_copy_range const& range);

	void cmd_copy(command_buffer command_buffer, buffer buffer, image image,
		image_subresource_range const& range);

	void cmd_copy(command_buffer command_buffer, buffer buffer, image image);
}