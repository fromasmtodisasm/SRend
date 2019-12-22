#include "PhysicalDeviceImpl.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  std::vector<PhysicalDeviceFeatures> getPhysicalDeviceFeatures(vk::PhysicalDevice vkPhysicalDevice)
  {
    auto feature = vkPhysicalDevice.getFeatures();
    std::vector<PhysicalDeviceFeatures> result;

    if (feature.robustBufferAccess) result.push_back(PhysicalDeviceFeatures::RobustBufferAccess);
    if (feature.fullDrawIndexUint32) result.push_back(PhysicalDeviceFeatures::FullDrawIndexUint32);
    if (feature.imageCubeArray) result.push_back(PhysicalDeviceFeatures::ImageCubeArray);
    if (feature.independentBlend) result.push_back(PhysicalDeviceFeatures::IndependentBlend);
    if (feature.geometryShader) result.push_back(PhysicalDeviceFeatures::GeometryShader);
    if (feature.tessellationShader) result.push_back(PhysicalDeviceFeatures::TessellationShader);
    if (feature.sampleRateShading) result.push_back(PhysicalDeviceFeatures::SampleRateShading);
    if (feature.dualSrcBlend) result.push_back(PhysicalDeviceFeatures::DualSrcBlend);
    if (feature.multiDrawIndirect) result.push_back(PhysicalDeviceFeatures::MultiDrawIndirect);
    if (feature.drawIndirectFirstInstance) result.push_back(PhysicalDeviceFeatures::DrawIndirectFirstInstance);
    if (feature.depthClamp) result.push_back(PhysicalDeviceFeatures::DepthClamp);
    if (feature.depthBiasClamp) result.push_back(PhysicalDeviceFeatures::DepthBiasClamp);
    if (feature.fillModeNonSolid) result.push_back(PhysicalDeviceFeatures::FillModeNonSolid);
    if (feature.depthBounds) result.push_back(PhysicalDeviceFeatures::DepthBounds);
    if (feature.wideLines) result.push_back(PhysicalDeviceFeatures::WideLines);
    if (feature.largePoints) result.push_back(PhysicalDeviceFeatures::LargePoints);
    if (feature.alphaToOne) result.push_back(PhysicalDeviceFeatures::AlphaToOne);
    if (feature.multiViewport) result.push_back(PhysicalDeviceFeatures::MultiViewport);
    if (feature.samplerAnisotropy) result.push_back(PhysicalDeviceFeatures::SamplerAnisotropy);
    if (feature.textureCompressionETC2) result.push_back(PhysicalDeviceFeatures::TextureCompressionEtc2);
    if (feature.textureCompressionASTC_LDR) result.push_back(PhysicalDeviceFeatures::TextureCompressionAstcLdr);
    if (feature.textureCompressionBC) result.push_back(PhysicalDeviceFeatures::TextureCompressionBc);
    if (feature.occlusionQueryPrecise) result.push_back(PhysicalDeviceFeatures::OcclusionQueryPrecise);
    if (feature.pipelineStatisticsQuery) result.push_back(PhysicalDeviceFeatures::PipelineStatisticsQuery);
    if (feature.vertexPipelineStoresAndAtomics)
      result.push_back(PhysicalDeviceFeatures::VertexPipelineStoresAndAtomics);
    if (feature.fragmentStoresAndAtomics) result.push_back(PhysicalDeviceFeatures::FragmentStoresAndAtomics);
    if (feature.shaderTessellationAndGeometryPointSize)
      result.push_back(PhysicalDeviceFeatures::ShaderTessellationAndGeometryPointSize);
    if (feature.shaderImageGatherExtended) result.push_back(PhysicalDeviceFeatures::ShaderImageGatherExtended);
    if (feature.shaderStorageImageExtendedFormats)
      result.push_back(PhysicalDeviceFeatures::ShaderStorageImageExtendedFormats);
    if (feature.shaderStorageImageMultisample) result.push_back(PhysicalDeviceFeatures::ShaderStorageImageMultisample);
    if (feature.shaderStorageImageReadWithoutFormat)
      result.push_back(PhysicalDeviceFeatures::ShaderStorageImageReadWithoutFormat);
    if (feature.shaderStorageImageWriteWithoutFormat)
      result.push_back(PhysicalDeviceFeatures::ShaderStorageImageWriteWithoutFormat);
    if (feature.shaderUniformBufferArrayDynamicIndexing)
      result.push_back(PhysicalDeviceFeatures::ShaderUniformBufferArrayDynamicIndexing);
    if (feature.shaderSampledImageArrayDynamicIndexing)
      result.push_back(PhysicalDeviceFeatures::ShaderSampledImageArrayDynamicIndexing);
    if (feature.shaderStorageBufferArrayDynamicIndexing)
      result.push_back(PhysicalDeviceFeatures::ShaderStorageBufferArrayDynamicIndexing);
    if (feature.shaderStorageImageArrayDynamicIndexing)
      result.push_back(PhysicalDeviceFeatures::ShaderStorageImageArrayDynamicIndexing);
    if (feature.shaderClipDistance) result.push_back(PhysicalDeviceFeatures::ShaderClipDistance);
    if (feature.shaderCullDistance) result.push_back(PhysicalDeviceFeatures::ShaderCullDistance);
    if (feature.shaderFloat64) result.push_back(PhysicalDeviceFeatures::ShaderFloat64);
    if (feature.shaderInt64) result.push_back(PhysicalDeviceFeatures::ShaderInt64);
    if (feature.shaderInt16) result.push_back(PhysicalDeviceFeatures::ShaderInt16);
    if (feature.shaderResourceResidency) result.push_back(PhysicalDeviceFeatures::ShaderResourceResidency);
    if (feature.shaderResourceMinLod) result.push_back(PhysicalDeviceFeatures::ShaderResourceMinLod);
    if (feature.sparseBinding) result.push_back(PhysicalDeviceFeatures::SparseBinding);
    if (feature.sparseResidencyBuffer) result.push_back(PhysicalDeviceFeatures::SparseResidencyBuffer);
    if (feature.sparseResidencyImage2D) result.push_back(PhysicalDeviceFeatures::SparseResidencyImage2D);
    if (feature.sparseResidencyImage3D) result.push_back(PhysicalDeviceFeatures::SparseResidencyImage3D);
    if (feature.sparseResidency2Samples) result.push_back(PhysicalDeviceFeatures::SparseResidency2Samples);
    if (feature.sparseResidency4Samples) result.push_back(PhysicalDeviceFeatures::SparseResidency4Samples);
    if (feature.sparseResidency8Samples) result.push_back(PhysicalDeviceFeatures::SparseResidency8Samples);
    if (feature.sparseResidency16Samples) result.push_back(PhysicalDeviceFeatures::SparseResidency16Samples);
    if (feature.sparseResidencyAliased) result.push_back(PhysicalDeviceFeatures::SparseResidencyAliased);
    if (feature.variableMultisampleRate) result.push_back(PhysicalDeviceFeatures::VariableMultisampleRate);
    if (feature.inheritedQueries) result.push_back(PhysicalDeviceFeatures::InheritedQueries);
    return result;
  }

  std::vector<DeviceExtensions> getDeviceSupportedExtensions(vk::PhysicalDevice vkPhysicalDevice)
  {
    std::vector<DeviceExtensions> result;
    auto extensions = vkPhysicalDevice.enumerateDeviceExtensionProperties();

    for (auto const& ex : extensions)
    {
      std::string strEx = ex.extensionName;

      if (strEx == VK_KHR_SWAPCHAIN_EXTENSION_NAME)
      {
        result.push_back(DeviceExtensions::Swapchain);
      }
    }

    return result;
  }

  // PhysicalDeviceImpl -----------------------------------------------------------------------------------------------

  PhysicalDeviceImpl::PhysicalDeviceImpl(vk::PhysicalDevice vkPhysicalDevice)
      : vk_physical_device_(vkPhysicalDevice),
        features_(getPhysicalDeviceFeatures(vkPhysicalDevice)),
        extensions_(getDeviceSupportedExtensions(vkPhysicalDevice))
  {
  }

}  // namespace vulkan