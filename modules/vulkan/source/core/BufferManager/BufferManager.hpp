#pragma once
#include <utils/allocator.hpp>
#include "../CommandBuffer/CommandBuffer.hpp"

namespace vulkan
{
  class buffer_t;
  using buffer = std::shared_ptr<buffer_t>;

  class buffer_manager_t;
  using buffer_manager = std::shared_ptr<buffer_manager_t>;

  // utils
  // -------------------------------------------------------------------------------------------------

  enum class memory_usage
  {
    cpu,
    gpu,
    cpu_to_gpu,
    gpu_to_cpu
  };

  struct buffer_copy_info
  {
    buffer src_buffer;
    utils::offset_t src_offset;
    buffer dst_buffer;
    utils::offset_t dst_offset;
    utils::size_t size;
  };

  struct binding_info
  {
    uint32_t binding;
    uint32_t index;
    uint32_t set;
  };

  // buffer
  // ------------------------------------------------------------------------------------------------

  utils::size_t get_current_size(buffer buffer);

  void cmd_copy(command_buffer cmd_buf, std::vector<buffer_copy_info> const& copy_infos);

  void cmd_copy(command_buffer cmd_buf, buffer src_buffer, utils::offset_t src_offset,
      buffer dst_buffer, utils::offset_t dst_offset, size_t size);

  void cmd_copy(command_buffer cmd_buf, buffer src_buffer_, buffer dst_buffer_);

  void cmd_fill(command_buffer cmd_buf, buffer buffer, void const* p_data, utils::size_t size,
      utils::offset_t offset = 0);

  void copy_memory(
      buffer buffer, void const* p_data, utils::size_t size, utils::offset_t offset = 0);

  // BufferManager
  // ----------------------------------------------------------------------------------------

  buffer_manager create_buffer_manager(device device, vk::BufferUsageFlags usage,
      memory_usage memory_usage, utils::size_t chunk_size,
      utils::Allocator::Allocator const& Allocator);

  buffer_manager create_buffer_manager(
      device device, vk::BufferUsageFlags usage, memory_usage memory_usage);

  buffer allocate(
      buffer_manager buffer_manager, utils::size_t size, utils::alignment_t alignment = 0);

  void cmd_bind(command_buffer command_buffer, binding_info const& binding_info,
      std::vector<buffer> const& buffers);

  void cmd_bind(command_buffer command_buffer, binding_info const& binding_info, buffer buffer);
}  // namespace vulkan