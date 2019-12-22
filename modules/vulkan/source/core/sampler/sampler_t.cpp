#include "sampler_t.hpp"

namespace vulkan
{
	// utils -------------------------------------------------------------------------------------------------

	vk::Sampler create_vk_sampler(device device, sampler_parameters const& parameters)
	{
		VezSamplerCreateInfo create_info = {};
		create_info.magFilter = static_cast<VkFilter>(parameters.filter.mag);
		create_info.minFilter = static_cast<VkFilter>(parameters.filter.min);
		create_info.mipmapMode = static_cast<VkSamplerMipmapMode>(parameters.mipmap_mode);
		create_info.addressModeU = static_cast<VkSamplerAddressMode>(parameters.address_mode.u);
		create_info.addressModeV = static_cast<VkSamplerAddressMode>(parameters.address_mode.v);
		create_info.addressModeW = static_cast<VkSamplerAddressMode>(parameters.address_mode.w);
		create_info.mipLodBias = parameters.lod.mip_lod_bias;
		create_info.anisotropyEnable = parameters.max_anisotropy.has_value();
		create_info.maxAnisotropy = parameters.max_anisotropy.value();
		create_info.compareEnable = parameters.compare_op.has_value();
		create_info.compareOp = static_cast<VkCompareOp>(parameters.compare_op.value());
		create_info.minLod = parameters.lod.min_lod;
		create_info.maxLod = parameters.lod.max_lod;
		create_info.borderColor = static_cast<VkBorderColor>(parameters.border_color);
		create_info.unnormalizedCoordinates = parameters.unnormalized_coordinates;

		VkSampler result = nullptr;
		check_result(vezCreateSampler(device->get_vk_device(), &create_info, &result));
		return result;
	}

	// sampler_t ---------------------------------------------------------------------------------------------

	sampler_t::sampler_t(device device, sampler_parameters const& parameters) :
		device_(device), vk_sampler_(create_vk_sampler(device, parameters))
	{
	}
}