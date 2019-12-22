#pragma once
#include <utils/utils.hpp>
#include <vulkan/vulkan.hpp>

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  struct WaitInfo
  {
    WaitInfo() = default;

    WaitInfo(vk::Semaphore const& waitSemaphore, vk::Flags<vk::PipelineStageFlagBits> const& waitStages)
        : waitSemaphore(waitSemaphore), waitStages(waitStages)
    {
    }

    vk::Semaphore waitSemaphore;
    vk::PipelineStageFlags waitStages;
  };

  struct DepthState
  {
    DepthState() = default;

    DepthState(bool writeEnable, vk::CompareOp compareOp, bool boundsTestEnable)
        : writeEnable(writeEnable), compareOp(compareOp), boundsTestEnable(boundsTestEnable)
    {
    }

    bool writeEnable = false;
    vk::CompareOp compareOp = vk::CompareOp::eLessOrEqual;
    bool boundsTestEnable = false;
  };

  struct StencilOpInfo
  {
    StencilOpInfo() = default;

    StencilOpInfo(vk::StencilOp failOp, vk::StencilOp passOp, vk::StencilOp depthFailOp, vk::CompareOp compareOp)
        : fail_op(failOp), pass_op(passOp), depth_fail_op(depthFailOp), compare_op(compareOp)
    {
    }

    vk::StencilOp fail_op;
    vk::StencilOp pass_op;
    vk::StencilOp depth_fail_op;
    vk::CompareOp compare_op;
  };

  struct StencilState
  {
    StencilState() = default;

    StencilState(StencilOpInfo const& front, StencilOpInfo const& back) : front(front), back(back)
    {
    }

    StencilOpInfo front;
    StencilOpInfo back;
  };

  struct ViewportState
  {
    ViewportState() = default;

    ViewportState(vk::Viewport const& viewport, vk::Rect2D const& scissor) : viewport(viewport), scissor(scissor)
    {
    }

    vk::Viewport viewport;
    vk::Rect2D scissor;
  };

  // CommandBuffer ----------------------------------------------------------------------------------------------------

  class CommandBuffer
  {
   public:
    virtual ~CommandBuffer() = default;

    virtual void begin(vk::CommandBufferUsageFlags usage) = 0;
  };

  // TransferCommandBuffer --------------------------------------------------------------------------------------------

  class TransferCommandBuffer : public virtual CommandBuffer
  {
   public:
  };

  // ComputeCommandBuffer ---------------------------------------------------------------------------------------------

  class ComputeCommandBuffer : public virtual CommandBuffer
  {
   public:
  };

  // GraphicCommandBuffer ---------------------------------------------------------------------------------------------

  class GraphicCommandBuffer : public ComputeCommandBuffer, public TransferCommandBuffer
  {
   public:
    virtual void draw(utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance,
        utils::SizeT instanceCount) = 0;

    virtual void drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount, utils::IndexT firstInstance,
        utils::SizeT instanceCount, utils::OffsetT vertexOffset) = 0;

    virtual void setViewportState(std::vector<ViewportState> const& viewports) = 0;

    virtual void setDepthStencilState(
        std::optional<DepthState> const& depthState, std::optional<StencilState> const& stencilState) = 0;
  };

}  // namespace vulkan