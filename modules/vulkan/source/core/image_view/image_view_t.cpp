#include "image_view_t.hpp"

namespace vulkan
{
	// utils -------------------------------------------------------------------------------------------------

	vk::ImageViewType pick_image_view_type(image image, image_subresource_range const& range)
	{
		if (range.layer_count > 1)
		{
			if (image->get_extent().height == 1)
			{
				return vk::ImageViewType::e1DArray;
			}
			else if (image->get_extent().depth == 1)
			{
				return vk::ImageViewType::e2DArray;
			}
			else
			{
				throw std::runtime_error("3D image array no supported");
			}
		}
		else
		{
			if (image->get_extent().height == 1)
			{
				return vk::ImageViewType::e1D;
			}
			else if (image->get_extent().depth == 1)
			{
				return vk::ImageViewType::e2D;
			}
			else
			{
				return vk::ImageViewType::e3D;
			}
		}
	}

	VezImageSubresourceRange to_vk_image_range(image_subresource_range const& range)
	{
		return { range.base_mip_level, range.level_count, range.base_array_layer, range.layer_count };
	}

	vk::ImageView create_vk_image_view(image image, image_subresource_range const& range,
		vk::ComponentMapping const& components)
	{
		VezImageViewCreateInfo create_info = {};
		create_info.image = image->get_vk_image();
		create_info.format = static_cast<VkFormat>(image->get_format());
		create_info.subresourceRange = to_vk_image_range(range);
		create_info.components = components;
		create_info.viewType = static_cast<VkImageViewType>(pick_image_view_type(image, range));

		VkImageView image_view = nullptr;
		check_result(vezCreateImageView(image->get_device()->get_vk_device(), &create_info, &image_view));

		return image_view;
	}

	// image_view_t ------------------------------------------------------------------------------------------

	image_view_t::image_view_t(image image, image_subresource_range const& range,
		vk::ComponentMapping const& components) : 
		image_(image),
		range_(range),
		vk_image_view_(create_vk_image_view(image, range, components))
	{
	}
}
