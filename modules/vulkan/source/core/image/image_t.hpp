#pragma once
#include "../Device/DeviceImpl.hpp"
#include "image.hpp"

namespace vulkan
{
	// image_t ----------------------------------------------------------------------------------------------

	class image_t
	{
	public:
		image_t(device device, vk::Format format, vk::ImageUsageFlags usage, vk::Extent3D const& extent,
			vk::ImageCreateFlags create_flags, uint32_t array_layers, uint32_t mip_levels,
			vk::SampleCountFlagBits sample_count, memory_usage memory_usage, vk::ImageTiling tiling);

		~image_t()
		{
			vezDestroyImage(device_->get_vk_device(), vk_image_);
		}

		device get_device() const
		{
			return device_;
		}

		vk::Format get_format() const
		{
			return format_;
		}

		vk::Extent3D get_extent() const
		{
			return extent_;
		}

		uint32_t get_array_layers() const
		{
			return array_layers_;
		}

		uint32_t get_mip_levels() const
		{
			return mip_levels_;
		}

		vk::SampleCountFlagBits get_sample_count() const
		{
			return sample_count_;
		}

		vk::Image get_vk_image() const
		{
			return vk_image_;
		}

	private:
		device device_;
		vk::Format format_;
		vk::Extent3D extent_;
		uint32_t array_layers_;
		uint32_t mip_levels_;
		vk::SampleCountFlagBits sample_count_;
		vk::Image vk_image_;
	};
}