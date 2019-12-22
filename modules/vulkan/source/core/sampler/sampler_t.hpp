#pragma once
#include "../Device/DeviceImpl.hpp"
#include "sampler.hpp"

namespace vulkan
{
	// sampler_t ---------------------------------------------------------------------------------------------

	class sampler_t
	{
	public:
		sampler_t(device device, sampler_parameters const& parameters);

		~sampler_t()
		{
			vezDestroySampler(device_->get_vk_device(), vk_sampler_);
		}

		device get_device() const
		{
			return device_;
		}

		vk::Sampler get_vk_sampler() const
		{
			return vk_sampler_;
		}

	private:
		device device_;
		vk::Sampler vk_sampler_;
	};
}