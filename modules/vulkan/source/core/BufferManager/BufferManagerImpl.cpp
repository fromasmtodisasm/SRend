#include "BufferManagerImpl.hpp"

namespace vulkan
{
  // utils
  // ------------------------------------------------------------------------------------------------

  VezMemoryFlags to_vk_memory_usage(memory_usage flag)
  {
    switch (flag)
    {
      case memory_usage::cpu:
        return VEZ_MEMORY_CPU_ONLY;
      case memory_usage::gpu:
        return VEZ_MEMORY_GPU_ONLY;
      case memory_usage::cpu_to_gpu:
        return VEZ_MEMORY_CPU_TO_GPU;
      case memory_usage::gpu_to_cpu:
        return VEZ_MEMORY_GPU_TO_CPU;
      default:
        throw std::runtime_error("undefined enum value");
    }
  }

  vk::Buffer create_vk_buffer(
      device device, vk::BufferUsageFlags usage, utils::size_t size, memory_usage memory_usage)
  {
    VezBufferCreateInfo create_info = {};
    create_info.size = size;
    create_info.usage = static_cast<VkBufferUsageFlags>(usage);

    VkBuffer buffer = nullptr;
    check_result(vezCreateBuffer(
        device->get_vk_device(), to_vk_memory_usage(memory_usage), &create_info, &buffer));
    return buffer;
  }

  // buffer_block
  // -----------------------------------------------------------------------------------------

  buffer_block::buffer_block(device device, vk::BufferUsageFlags usage, memory_usage memory_usage,
      utils::size_t block_size, utils::Allocator::Allocator const& Allocator)
      : device_(device),
        allocator_(Allocator),
        block_size_(block_size),
        vk_buffer_(create_vk_buffer(device, usage, block_size, memory_usage))
  {
  }
}  // namespace vulkan
