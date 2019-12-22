#pragma once
#include <optional>
#include "../Device/Device.hpp"
#include "../image_view/image_view.hpp"

namespace vulkan
{
	class sampler_t;
	using sampler = std::shared_ptr<sampler_t>;

	// utils -------------------------------------------------------------------------------------------------

	struct sampler_address_modes
	{
		vk::SamplerAddressMode u;
		vk::SamplerAddressMode v;
		vk::SamplerAddressMode w;
	};

	struct sampler_filters
	{
		vk::Filter mag;
		vk::Filter min;
	};

	struct sampler_lods
	{
		float mip_lod_bias;
		float min_lod;
		float max_lod;
	};

	struct sampler_parameters
	{
		sampler_filters filter;
		vk::SamplerMipmapMode mipmap_mode;
		sampler_address_modes address_mode;
		sampler_lods lod;
		std::optional<float> max_anisotropy;
		std::optional<vk::CompareOp> compare_op;
		vk::BorderColor border_color;
		bool unnormalized_coordinates;
	};

	// sampler -----------------------------------------------------------------------------------------------

	sampler create_sampler(device device, sampler_parameters const& parameters = {});

	void cmd_bind(command_buffer command_buffer, binding_info const& binding_info,
		image_view image_view, sampler sampler);
}