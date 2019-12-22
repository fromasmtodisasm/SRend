#include "image_t.hpp"
#include "../buffer_manager/buffer_manager_t.hpp"

namespace vulkan
{
	// helpers ----------------------------------------------------------------------------------------------

	vk::ImageType pick_image_type(vk::Extent3D const& extent)
	{
		if (extent.height == 1)
		{
			return vk::ImageType::e1D;
		}
		else if (extent.depth == 1)
		{
			return vk::ImageType::e2D;
		}
		else
		{
			return vk::ImageType::e3D;
		}
	}

	vk::Image create_vk_image(
		device device,
		vk::Format format,
		vk::ImageUsageFlags usage,
		vk::Extent3D const& extent,
		vk::ImageCreateFlags create_flags,
		uint32_t array_layers,
		uint32_t mip_levels,
		vk::SampleCountFlagBits sample_count,
		memory_usage memory_usage,
		vk::ImageTiling tiling
	)
	{
		VezImageCreateInfo create_info = {};
		create_info.flags = static_cast<VkImageCreateFlags>(create_flags);
		create_info.usage = static_cast<VkImageUsageFlags>(usage);
		create_info.format = static_cast<VkFormat>(format);
		create_info.extent = extent;
		create_info.arrayLayers = array_layers;
		create_info.mipLevels = mip_levels;
		create_info.samples = static_cast<VkSampleCountFlagBits>(sample_count);
		create_info.tiling = static_cast<VkImageTiling>(tiling);
		create_info.imageType = static_cast<VkImageType>(pick_image_type(extent));

		VkImage result = nullptr;
		check_result(vezCreateImage(device->get_vk_device(), to_vk_memory_usage(memory_usage),
			&create_info, &result));
		return result;
	}

	// impl -------------------------------------------------------------------------------------------------

	image_t::image_t(
		device device,
		vk::Format format,
		vk::ImageUsageFlags usage,
		vk::Extent3D const& extent,
		vk::ImageCreateFlags create_flags,
		uint32_t array_layers,
		uint32_t mip_levels,
		vk::SampleCountFlagBits sample_count,
		memory_usage memory_usage,
		vk::ImageTiling tiling
	) :
		device_(device),
		format_(format),
		extent_(extent),
		array_layers_(array_layers),
		mip_levels_(mip_levels),
		sample_count_(sample_count),
		vk_image_(create_vk_image(
			device,
			format,
			usage,
			extent,
			create_flags,
			array_layers,
			mip_levels,
			sample_count,
			memory_usage,
			tiling
		))
	{
	}
}
