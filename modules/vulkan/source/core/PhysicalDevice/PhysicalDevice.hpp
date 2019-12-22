#pragma once
#include <utils/utils.hpp>
#include <vulkan/vulkan.hpp>

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  enum class DeviceExtensions
  {
    Swapchain

  };

  enum class PhysicalDeviceFeatures
  {
    RobustBufferAccess,
    FullDrawIndexUint32,
    ImageCubeArray,
    IndependentBlend,
    GeometryShader,
    TessellationShader,
    SampleRateShading,
    DualSrcBlend,
    LogicOp,
    MultiDrawIndirect,
    DrawIndirectFirstInstance,
    DepthClamp,
    DepthBiasClamp,
    FillModeNonSolid,
    DepthBounds,
    WideLines,
    LargePoints,
    AlphaToOne,
    MultiViewport,
    SamplerAnisotropy,
    TextureCompressionEtc2,
    TextureCompressionAstcLdr,
    TextureCompressionBc,
    OcclusionQueryPrecise,
    PipelineStatisticsQuery,
    VertexPipelineStoresAndAtomics,
    FragmentStoresAndAtomics,
    ShaderTessellationAndGeometryPointSize,
    ShaderImageGatherExtended,
    ShaderStorageImageExtendedFormats,
    ShaderStorageImageMultisample,
    ShaderStorageImageReadWithoutFormat,
    ShaderStorageImageWriteWithoutFormat,
    ShaderUniformBufferArrayDynamicIndexing,
    ShaderSampledImageArrayDynamicIndexing,
    ShaderStorageBufferArrayDynamicIndexing,
    ShaderStorageImageArrayDynamicIndexing,
    ShaderClipDistance,
    ShaderCullDistance,
    ShaderFloat64,
    ShaderInt64,
    ShaderInt16,
    ShaderResourceResidency,
    ShaderResourceMinLod,
    SparseBinding,
    SparseResidencyBuffer,
    SparseResidencyImage2D,
    SparseResidencyImage3D,
    SparseResidency2Samples,
    SparseResidency4Samples,
    SparseResidency8Samples,
    SparseResidency16Samples,
    SparseResidencyAliased,
    VariableMultisampleRate,
    InheritedQueries,
  };

  // PhysicalDevice ---------------------------------------------------------------------------------------------------

  class PhysicalDeviceImpl;

  class PhysicalDevice
  {
   public:
    explicit PhysicalDevice(std::shared_ptr<PhysicalDeviceImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<PhysicalDeviceImpl> getImpl() const
    {
      return pimpl_;
    }

    [[nodiscard]] vk::PhysicalDeviceProperties getProperties() const;

    [[nodiscard]] std::vector<PhysicalDeviceFeatures> getFeatures() const;

    [[nodiscard]] std::vector<DeviceExtensions> getSupportedDeviceExtensions() const;

   private:
    std::shared_ptr<PhysicalDeviceImpl> pimpl_;
  };

}  // namespace vulkan
