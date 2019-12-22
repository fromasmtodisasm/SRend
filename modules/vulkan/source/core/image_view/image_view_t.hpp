#pragma once
#include "image_view.hpp"
#include "../image/image_t.hpp"

namespace vulkan
{
	// image_view_t -----------------------------------------------------------------------------------------

	class image_view_t
	{
	public:
		image_view_t(image image, image_subresource_range const& range,
			vk::ComponentMapping const& components);

		~image_view_t()
		{
			vezDestroyImageView(image_->get_device()->get_vk_device(), vk_image_view_);
		}

		image get_image() const
		{
			return image_;
		}

		image_subresource_range get_range() const
		{
			return range_;
		}

		vk::ImageView get_vk_image_view() const
		{
			return vk_image_view_;
		}

	private:
		image image_;
		image_subresource_range range_;
		vk::ImageView vk_image_view_;
	};
}