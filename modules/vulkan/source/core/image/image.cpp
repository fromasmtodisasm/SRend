#include "../Device/DeviceImpl.hpp"
#include "../buffer_manager/buffer_t.hpp"
#include "../command_buffer/CommandBufferImpl.hpp"
#include "image_t.hpp"

namespace vulkan
{
	// helpers ----------------------------------------------------------------------------------------------

	uint32_t min_size(uint32_t src_size, uint32_t src_offset, uint32_t dst_size, uint32_t dst_offset)
	{
		if (src_size + src_offset > dst_size + dst_offset)
		{
			return dst_size + dst_offset - src_offset;
		}
		else
		{
			return src_size + src_offset - dst_offset;
		}
	}

	vk::Extent3D min_extent(vk::Extent3D const& src_extent, vk::Offset3D const& src_offset,
		vk::Extent3D const& dst_extent, vk::Offset3D const& dst_offset)
	{
		return {
			min_size(src_extent.width, src_offset.x, dst_extent.width, dst_offset.x),
			min_size(src_extent.height, src_offset.y, dst_extent.height, dst_offset.y),
			min_size(src_extent.depth, src_offset.z, dst_extent.depth, dst_offset.z)
		};
	}

	// image interface --------------------------------------------------------------------------------------

	image create_image(device device, vk::Format format, vk::ImageUsageFlags usage,
		vk::Extent3D const& extent, vk::ImageCreateFlags create_flags, uint32_t array_layers,
		uint32_t mip_levels, vk::SampleCountFlagBits sample_count, memory_usage memory_usage, 
		vk::ImageTiling tiling)
	{
		return std::make_shared<image_t>(device, format, usage, extent, create_flags, array_layers,
			mip_levels, sample_count, memory_usage, tiling);
	}

	vk::Extent3D get_extent(image image)
	{
		return image->get_extent();
	}

	vk::Format get_format(image image)
	{
		return image->get_format();
	}

	uint32_t get_array_layers_count(image image)
	{
		return image->get_array_layers();
	}

	uint32_t get_mip_levels_count(image image)
	{
		return image->get_mip_levels();
	}

	vk::SampleCountFlagBits get_sample_count(image image)
	{
		return image->get_sample_count();
	}

	void cmd_copy(command_buffer command_buffer, image src_image, image_copy_range const& src_range,
		image dst_image, image_copy_range const& dst_range)
	{
		uint32_t array_layers_copy_count = std::min(src_range.range.layer_count, dst_range.range.layer_count);
		uint32_t mip_levels_copy_count = std::min(src_range.range.level_count, dst_range.range.level_count);

		VezImageSubresourceLayers src_copy_layers = { 0, src_range.range.base_array_layer, array_layers_copy_count };
		VezImageSubresourceLayers dst_copy_layers = { 0, src_range.range.base_array_layer, array_layers_copy_count };

		VezImageCopy copy_info = {};
		copy_info.srcOffset = src_range.offset;
		copy_info.dstOffset = dst_range.offset;
		copy_info.extent = min_extent(src_range.extent, src_range.offset, dst_range.extent, dst_range.offset);
		copy_info.srcSubresource = src_copy_layers;
		copy_info.dstSubresource = dst_copy_layers;

		std::vector<VezImageCopy> copy_infos(mip_levels_copy_count, copy_info);

		for (uint32_t i = 0; i != mip_levels_copy_count; ++i)
		{
			copy_infos[i].srcSubresource.mipLevel = src_range.range.base_mip_level + i;
			copy_infos[i].dstSubresource.mipLevel = dst_range.range.base_mip_level + i;
		}

		vezCmdCopyImage(src_image->get_vk_image(), dst_image->get_vk_image(), mip_levels_copy_count,
			copy_infos.data());
	}

	void cmd_copy(command_buffer command_buffer, image src_image,
		image_subresource_range const& src_range, image dst_image, image_subresource_range const& dst_range)
	{
		cmd_copy(command_buffer, src_image, { src_image->get_extent(), {}, src_range }, dst_image,
			{ dst_image->get_extent(), {}, dst_range });
	}

	void cmd_copy(command_buffer command_buffer, image src_image, image dst_image)
	{
		cmd_copy(command_buffer,src_image,
			image_subresource_range{ 0, src_image->get_mip_levels(), 0, src_image->get_array_layers() },
			dst_image,
			image_subresource_range{ 0, dst_image->get_mip_levels(), 0, dst_image->get_array_layers() });
	}

	void cmd_copy(command_buffer command_buffer, buffer buffer, image image,
		image_copy_range const& range)
	{
		VezBufferImageCopy copy_range = { };
		copy_range.imageExtent = min_extent(range.extent, range.offset, image->get_extent(), { 0, 0, 0 });
		copy_range.bufferOffset = buffer->offset();
		copy_range.imageOffset = range.offset;
		copy_range.imageSubresource = { range.range.base_mip_level, range.range.base_array_layer,
			range.range.layer_count };

		std::vector<VezBufferImageCopy> copy_ranges(range.range.level_count, copy_range);
		for (uint32_t i = 0; i != range.range.level_count; ++i)
		{
			copy_ranges[i].imageSubresource.mipLevel += i;
		}

		vezCmdCopyBufferToImage(buffer->get_vk_buffer(), image->get_vk_image(),
			static_cast<uint32_t>(copy_ranges.size()), copy_ranges.data());
	}

	void cmd_copy(command_buffer command_buffer, buffer buffer, image image,
		image_subresource_range const& range)
	{
		cmd_copy(command_buffer, buffer, image, { get_extent(image), {}, range });
	}

	void cmd_copy(command_buffer command_buffer, buffer buffer, image image)
	{
		cmd_copy(command_buffer, buffer, image,
			image_subresource_range{ 0, image->get_mip_levels() , 0, image->get_array_layers() });
	}
}