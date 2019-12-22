#pragma once
#include "CommandBuffer.hpp"

namespace vulkan
{
  // BaseCommandBufferImpl --------------------------------------------------------------------------------------------

  class BaseCommandBufferImpl : public virtual CommandBuffer
  {
   public:
    explicit BaseCommandBufferImpl(vk::Device vkDevice, vk::CommandBuffer vkCommandBuffer)
        : vkDevice_(vkDevice), vkCommandBuffer_(vkCommandBuffer)
    {
    }

    [[nodiscard]] vk::CommandBuffer getVkCommandBuffer() const
    {
      return vkCommandBuffer_;
    }

    ~BaseCommandBufferImpl() override;

    void begin(vk::CommandBufferUsageFlags usage) override;

   private:
    vk::Device vkDevice_;
    vk::CommandBuffer vkCommandBuffer_;
  };

  // TransferCommandBufferImpl ----------------------------------------------------------------------------------------

  class TransferCommandBufferImpl : public virtual TransferCommandBuffer, public BaseCommandBufferImpl
  {
   public:
    using BaseCommandBufferImpl::BaseCommandBufferImpl;
  };

  std::vector<std::shared_ptr<TransferCommandBuffer>> allocateImplTransferCommandBuffers(
      vk::Device device, vk::Queue queue, utils::SizeT count);

  std::vector<vk::Semaphore> submitImplTransferCommandBuffers(vk::Device device, vk::Queue queue,
      std::vector<std::pair<std::shared_ptr<TransferCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

  // ComputeCommandBufferImpl -----------------------------------------------------------------------------------------

  class ComputeCommandBufferImpl : public virtual ComputeCommandBuffer, public BaseCommandBufferImpl
  {
   public:
    using BaseCommandBufferImpl::BaseCommandBufferImpl;
  };

  std::vector<std::shared_ptr<ComputeCommandBuffer>> allocateImplComputeCommandBuffers(
      vk::Device device, vk::Queue queue, utils::SizeT count);

  std::vector<vk::Semaphore> submitImplComputeCommandBuffers(vk::Device device, vk::Queue queue,
      std::vector<std::pair<std::shared_ptr<ComputeCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

  // GraphicCommandBufferImpl -----------------------------------------------------------------------------------------

  class GraphicCommandBufferImpl : public virtual GraphicCommandBuffer, public BaseCommandBufferImpl
  {
   public:
    using BaseCommandBufferImpl::BaseCommandBufferImpl;

    void draw(utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance,
        utils::SizeT instanceCount) override;

    void drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount, utils::IndexT firstInstance,

        utils::SizeT instanceCount, utils::OffsetT vertexOffset) override;

    void setViewportState(std::vector<ViewportState> const& viewports) override;

    void setDepthStencilState(
        std::optional<DepthState> const& depthState, std::optional<StencilState> const& stencilState) override;
  };

  std::vector<std::shared_ptr<GraphicCommandBuffer>> allocateImplGraphicCommandBuffers(
      vk::Device device, vk::Queue queue, utils::SizeT count);

  std::vector<vk::Semaphore> submitImplGraphicCommandBuffers(vk::Device device, vk::Queue queue,
      std::vector<std::pair<std::shared_ptr<GraphicCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

}  // namespace vulkan