#include "CommandBufferImpl.hpp"
#include <VEZ.h>
#include "../../utils.hpp"

namespace vulkan
{
  // utils ------------------------------------------------------------------------------------------------------------

  template <typename T>
  std::vector<VkCommandBuffer> toVkCommandBuffers(std::vector<std::pair<T, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkCommandBuffer> result;
    result.reserve(submitInfos.size());

    for (auto const& info : submitInfos)
    {
      result.push_back(implCast<BaseCommandBufferImpl>(info.first)->getVkCommandBuffer());
    }

    return result;
  }

  template <typename T>
  std::vector<VkSemaphore> toVkSemaphores(std::vector<std::pair<T, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkSemaphore> result;

    for (auto const& info : submitInfos)
    {
      for (auto const& waitInfo : info.second)
      {
        result.push_back(waitInfo.waitSemaphore);
      }
    }

    return result;
  }

  template <typename T>
  std::vector<VkPipelineStageFlags> toVkWaitStages(std::vector<std::pair<T, std::vector<WaitInfo>>> const& submitInfos)
  {
    std::vector<VkPipelineStageFlags> result;

    for (auto const& info : submitInfos)
    {
      for (auto const& waitInfo : info.second)
      {
        result.push_back(static_cast<VkPipelineStageFlags>(waitInfo.waitStages));
      }
    }

    return result;
  }

  template <typename T, typename TImpl>
  std::vector<std::shared_ptr<T>> allocateBaseCommandBuffers(vk::Device device, vk::Queue queue, utils::SizeT count)
  {
    VezCommandBufferAllocateInfo allocInfo = {};
    allocInfo.queue = queue;
    allocInfo.commandBufferCount = static_cast<uint32_t>(count);

    std::vector<vk::CommandBuffer> vkCommandBuffers(count);
    checkResult(
        vezAllocateCommandBuffers(device, &allocInfo, reinterpret_cast<VkCommandBuffer*>(vkCommandBuffers.data())));

    std::vector<std::shared_ptr<T>> result;
    result.reserve(vkCommandBuffers.size());

    for (auto vkCommandBuffer : vkCommandBuffers)
    {
      result.push_back(std::make_shared<TImpl>(device, vkCommandBuffer));
    }

    return result;
  }

  template <typename T>
  std::vector<vk::Semaphore> submitBaseCommandBuffers(vk::Device device, vk::Queue queue,
      std::vector<std::pair<std::shared_ptr<T>, std::vector<WaitInfo>>> const& submitInfos)
  {
    vezEndCommandBuffer();

    std::vector<vk::Semaphore> signalSemaphores(submitInfos.size());
    std::vector<VkCommandBuffer> commandBuffers = toVkCommandBuffers(submitInfos);
    std::vector<VkSemaphore> waitSemaphores = toVkSemaphores(submitInfos);
    std::vector<VkPipelineStageFlags> waitStages = toVkWaitStages(submitInfos);

    VezSubmitInfo vkSubmitInfo = {};
    vkSubmitInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
    vkSubmitInfo.pCommandBuffers = commandBuffers.data();
    vkSubmitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
    vkSubmitInfo.pWaitSemaphores = waitSemaphores.data();
    vkSubmitInfo.pWaitDstStageMask = waitStages.data();
    vkSubmitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
    vkSubmitInfo.pSignalSemaphores = reinterpret_cast<VkSemaphore*>(signalSemaphores.data());

    VkFence waitFence = nullptr;
    checkResult(vezQueueSubmit(queue, 1, &vkSubmitInfo, &waitFence));
    checkResult(vezWaitForFences(device, 1, &waitFence, true, UINT64_MAX));
    vezDestroyFence(device, waitFence);

    return signalSemaphores;
  }

  VezStencilOpState toVkStencilOpState(StencilOpInfo const& info)
  {
    return {static_cast<VkStencilOp>(info.fail_op), static_cast<VkStencilOp>(info.pass_op),
        static_cast<VkStencilOp>(info.depth_fail_op), static_cast<VkCompareOp>(info.compare_op)};
  }

  std::vector<VkViewport> toVkViewports(std::vector<ViewportState> const& viewportInfos)
  {
    std::vector<VkViewport> result;
    result.reserve(viewportInfos.size());

    for (auto const& viewportInfo : viewportInfos)
    {
      result.push_back(viewportInfo.viewport);
    }

    return result;
  }

  std::vector<VkRect2D> toVkScissors(std::vector<ViewportState> const& viewportInfos)
  {
    std::vector<VkRect2D> result;
    result.reserve(viewportInfos.size());

    for (auto const& viewportInfo : viewportInfos)
    {
      result.push_back(viewportInfo.scissor);
    }

    return result;
  }

  // BaseCommandBufferImpl --------------------------------------------------------------------------------------------

  BaseCommandBufferImpl::~BaseCommandBufferImpl()
  {
    vezFreeCommandBuffers(vkDevice_, 1, reinterpret_cast<VkCommandBuffer*>(&vkCommandBuffer_));
  }

  void BaseCommandBufferImpl::begin(vk::CommandBufferUsageFlags usage)
  {
    checkResult(vezBeginCommandBuffer(vkCommandBuffer_, static_cast<VkCommandBufferResetFlags>(usage)));
  }

  // TransferCommandBufferImpl ----------------------------------------------------------------------------------------

  std::vector<std::shared_ptr<TransferCommandBuffer>> allocateTransferCommandBuffers(
      vk::Device device, vk::Queue queue, utils::SizeT count)
  {
    return allocateBaseCommandBuffers<TransferCommandBuffer, TransferCommandBufferImpl>(device, queue, count);
  }

    std::vector<vk::Semaphore> submitTransferCommandBuffers(vk::Device device, vk::Queue queue,
      std::vector<std::pair<std::shared_ptr<TransferCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    return submitBaseCommandBuffers(device, queue, submitInfos);
  }

  // ComputeCommandBufferImpl -----------------------------------------------------------------------------------------

  std::vector<std::shared_ptr<ComputeCommandBuffer>> allocateComputeCommandBuffers(
      vk::Device device, vk::Queue queue, utils::SizeT count)
  {
    return allocateBaseCommandBuffers<ComputeCommandBuffer, ComputeCommandBufferImpl>(device, queue, count);
  }

    std::vector<vk::Semaphore> submitComputeCommandBuffers(vk::Device device, vk::Queue queue,
      std::vector<std::pair<std::shared_ptr<ComputeCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    return submitBaseCommandBuffers(device, queue, submitInfos);
  }

  // GraphicCommandBufferImpl -----------------------------------------------------------------------------------------

  void GraphicCommandBufferImpl::draw(
      utils::IndexT firstVertex, utils::SizeT vertexCount, utils::IndexT firstInstance, utils::SizeT instanceCount)
  {
    vezCmdDraw(static_cast<uint32_t>(vertexCount), static_cast<uint32_t>(instanceCount),
        static_cast<uint32_t>(firstVertex), static_cast<uint32_t>(firstInstance));
  }

  void GraphicCommandBufferImpl::drawIndexed(utils::IndexT firstIndex, utils::SizeT indexCount,
      utils::IndexT firstInstance, utils::SizeT instanceCount, utils::OffsetT vertexOffset)
  {
    vezCmdDrawIndexed(static_cast<uint32_t>(indexCount), static_cast<uint32_t>(instanceCount),
        static_cast<uint32_t>(firstIndex), static_cast<int32_t>(vertexOffset), static_cast<uint32_t>(firstInstance));
  }

  void GraphicCommandBufferImpl::setViewportState(std::vector<ViewportState> const& viewports)
  {
    auto vkViewports = toVkViewports(viewports);
    auto vkScissors = toVkScissors(viewports);

    vezCmdSetViewport(0, static_cast<uint32_t>(viewports.size()), vkViewports.data());
    vezCmdSetScissor(0, static_cast<uint32_t>(vkScissors.size()), vkScissors.data());
    vezCmdSetViewportState(static_cast<uint32_t>(viewports.size()));
  }

  void GraphicCommandBufferImpl::setDepthStencilState(
      std::optional<DepthState> const& depthState, std::optional<StencilState> const& stencilState)
  {
    VezDepthStencilState info = {};
    info.depthTestEnable = depthState.has_value();
    if (info.depthTestEnable)
    {
      info.depthWriteEnable = depthState->writeEnable;
      info.depthCompareOp = static_cast<VkCompareOp>(depthState->compareOp);
      info.depthBoundsTestEnable = depthState->boundsTestEnable;
    }

    info.stencilTestEnable = stencilState.has_value();
    if (info.stencilTestEnable)
    {
      info.front = toVkStencilOpState(stencilState->front);
      info.back = toVkStencilOpState(stencilState->back);
    }

    vezCmdSetDepthStencilState(&info);
  }

  std::vector<std::shared_ptr<GraphicCommandBuffer>> allocateGraphicCommandBuffers(
      vk::Device device, vk::Queue queue, utils::SizeT count)
  {
    return allocateBaseCommandBuffers<GraphicCommandBuffer, GraphicCommandBufferImpl>(device, queue, count);
  }

    std::vector<vk::Semaphore> submitGraphicCommandBuffers(vk::Device device, vk::Queue queue,
      std::vector<std::pair<std::shared_ptr<GraphicCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    return submitBaseCommandBuffers(device, queue, submitInfos);
  }

}  // namespace vulkan