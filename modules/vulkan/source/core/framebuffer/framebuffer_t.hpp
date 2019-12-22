#pragma once
#include "../Device/DeviceImpl.hpp"
#include "framebuffer.hpp"

namespace vulkan
{
	// framebuffer_t ----------------------------------------------------------------------------------------

	class framebuffer_t
	{
	public:
		framebuffer_t(device device, vk::Extent3D const& extent,
			std::vector<image_view> const& attachments);

		~framebuffer_t()
		{
			vezDestroyFramebuffer(device_->get_vk_device(), vk_framebuffer_);
		}

		device get_device() const
		{
			return device_;
		}

		std::vector<image_view> get_attachments() const
		{
			return attachments_;
		}

		VezFramebuffer get_vk_framebuffer() const
		{
			return vk_framebuffer_;
		}

	private:
		device device_;
		std::vector<image_view> attachments_;
		VezFramebuffer vk_framebuffer_;
	};
}