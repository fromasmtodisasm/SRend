#pragma once
#include "../Application/Application.hpp"
#include "../CommandBuffer/CommandBuffer.hpp"

namespace vulkan
{
  // Device -----------------------------------------------------------------------------------------------------------

  class DeviceImpl;

  class Device
  {
   public:
    explicit Device(std::shared_ptr<DeviceImpl> pimpl) : pimpl_(std::move(pimpl))
    {
    }

    [[nodiscard]] std::shared_ptr<DeviceImpl> getImpl() const
    {
      return pimpl_;
    }

    Device(const Application& application, const PhysicalDevice& physicalDevice);

    [[nodiscard]] std::vector<std::shared_ptr<TransferCommandBuffer>> allocateTransferCommandBuffers(
        utils::SizeT count) const;

    [[nodiscard]] std::shared_ptr<TransferCommandBuffer> allocateTransferCommandBuffer() const;

    [[nodiscard]] std::vector<std::shared_ptr<ComputeCommandBuffer>> allocateComputeCommandBuffers(
        utils::SizeT count) const;

    [[nodiscard]] std::shared_ptr<ComputeCommandBuffer> allocateComputeCommandBuffer() const;

    [[nodiscard]] std::vector<std::shared_ptr<GraphicCommandBuffer>> allocateGraphicCommandBuffers(
        utils::SizeT count) const;

    [[nodiscard]] std::shared_ptr<GraphicCommandBuffer> allocateGraphicCommandBuffer() const;

    std::vector<vk::Semaphore> submitTransferCommandBuffers(
        std::vector<std::pair<std::shared_ptr<TransferCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

    vk::Semaphore submitTransferCommandBuffer(
        std::shared_ptr<TransferCommandBuffer>, std::vector<WaitInfo> const& submitInfos);

    std::vector<vk::Semaphore> submitComputeCommandBuffers(
        std::vector<std::pair<std::shared_ptr<ComputeCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

    vk::Semaphore submitComputeCommandBuffer(
        std::shared_ptr<ComputeCommandBuffer>, std::vector<WaitInfo> const& submitInfos);

    std::vector<vk::Semaphore> submitGraphicCommandBuffers(
        std::vector<std::pair<std::shared_ptr<GraphicCommandBuffer>, std::vector<WaitInfo>>> const& submitInfos);

    vk::Semaphore submitGraphicCommandBuffer(
        std::shared_ptr<GraphicCommandBuffer>, std::vector<WaitInfo> const& submitInfos);

   private:
    std::shared_ptr<DeviceImpl> pimpl_;
  };

}  // namespace vulkan