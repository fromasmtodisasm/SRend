#include "Device.hpp"
#include "../CommandBuffer/CommandBufferImpl.hpp"
#include "DeviceImpl.hpp"

namespace vulkan
{
  // Device -----------------------------------------------------------------------------------------------------------

  Device::Device(const Application& application, const PhysicalDevice& physicalDevice)
      : pimpl_(std::make_shared<DeviceImpl>(application, physicalDevice))
  {
  }

  std::vector<std::shared_ptr<TransferCommandBuffer>> Device::allocateTransferCommandBuffers(utils::SizeT count) const
  {
    return allocateImplTransferCommandBuffers(pimpl_->getVkDevice(), pimpl_->getQueues().transferQueue, count);
  }

  std::shared_ptr<TransferCommandBuffer> Device::allocateTransferCommandBuffer() const
  {
    return allocateTransferCommandBuffers(1).front();
  }

  std::vector<std::shared_ptr<ComputeCommandBuffer>> Device::allocateComputeCommandBuffers(utils::SizeT count) const
  {
    return allocateImplComputeCommandBuffers(pimpl_->getVkDevice(), pimpl_->getQueues().computeQueue, count);
  }

  std::shared_ptr<ComputeCommandBuffer> Device::allocateComputeCommandBuffer() const
  {
    return allocateComputeCommandBuffers(1).front();
  }

  std::vector<std::shared_ptr<GraphicCommandBuffer>> Device::allocateGraphicCommandBuffers(utils::SizeT count) const
  {
    return allocateImplGraphicCommandBuffers(pimpl_->getVkDevice(), pimpl_->getQueues().graphicQueue, count);
  }

  std::shared_ptr<GraphicCommandBuffer> Device::allocateGraphicCommandBuffer() const
  {
    return allocateGraphicCommandBuffers(1).front();
  }

  std::vector<vk::Semaphore> Device::submitTransferCommandBuffers(
      std::vector<std::pair<std::shared_ptr<TransferCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    return submitImplTransferCommandBuffers(pimpl_->getVkDevice(), pimpl_->getQueues().transferQueue, submitInfos);
  }

  vk::Semaphore Device::submitTransferCommandBuffer(
      std::shared_ptr<TransferCommandBuffer> commandBuffer, std::vector<WaitInfo> const& waitInfos)
  {
    return submitTransferCommandBuffers({{commandBuffer, waitInfos}}).front();
  }

  std::vector<vk::Semaphore> Device::submitComputeCommandBuffers(
      std::vector<std::pair<std::shared_ptr<ComputeCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    return submitImplComputeCommandBuffers(pimpl_->getVkDevice(), pimpl_->getQueues().computeQueue, submitInfos);
  }

  vk::Semaphore Device::submitComputeCommandBuffer(
      std::shared_ptr<ComputeCommandBuffer> commandBuffer, std::vector<WaitInfo> const& waitInfos)
  {
    return submitComputeCommandBuffers({{commandBuffer, waitInfos}}).front();
  }

  std::vector<vk::Semaphore> Device::submitGraphicCommandBuffers(
      std::vector<std::pair<std::shared_ptr<GraphicCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos)
  {
    return submitImplGraphicCommandBuffers(pimpl_->getVkDevice(), pimpl_->getQueues().computeQueue, submitInfos);
  }

  vk::Semaphore Device::submitGraphicCommandBuffer(
      std::shared_ptr<GraphicCommandBuffer> commandBuffer, std::vector<WaitInfo> const& waitInfos)
  {
    return submitComputeCommandBuffers({{commandBuffer, waitInfos}}).front();
  }

}  // namespace vulkan
