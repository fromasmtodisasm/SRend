#include "BufferManagerImpl.hpp"

namespace vulkan
{
  // buffer
  // ------------------------------------------------------------------------------------------------

  utils::size_t get_current_size(buffer buffer)
  {
    return buffer->size();
  }

  void cmd_copy(command_buffer cmd_buf, std::vector<buffer_copy_info> const& copy_infos)
  {
    for (auto const& info : copy_infos)
    {
      VezBufferCopy range = {};
      range.size = info.size;
      range.srcOffset = info.src_buffer->offset() + info.src_offset;
      range.dstOffset = info.dst_buffer->offset() + info.dst_offset;

      vezCmdCopyBuffer(
          info.src_buffer->get_vk_buffer(), info.dst_buffer->get_vk_buffer(), 1, &range);
    }
  }

  void cmd_copy(command_buffer cmd_buf, buffer src_buffer, utils::offset_t src_offset,
      buffer dst_buffer, utils::offset_t dst_offset, size_t size)
  {
    cmd_copy(cmd_buf, {{src_buffer, src_offset, dst_buffer, dst_offset, size}});
  }

  void cmd_copy(command_buffer cmd_buf, buffer src_buffer, buffer dst_buffer)
  {
    cmd_copy(cmd_buf, {{src_buffer, 0, dst_buffer, 0, dst_buffer->size()}});
  }

  void cmd_fill(
      command_buffer, buffer buffer, void const* p_data, utils::size_t size, utils::offset_t offset)
  {
    vezCmdUpdateBuffer(buffer->get_vk_buffer(), buffer->offset() + offset, size, p_data);
  }

  void copy_memory(buffer buffer, void const* p_data, utils::size_t size, utils::offset_t offset)
  {
    VkDevice vk_device = buffer->get_device()->get_vk_device();

    void* p_mapped_data = nullptr;
    vezMapBuffer(vk_device, buffer->get_vk_buffer(), offset, size, &p_mapped_data);
    memcpy(reinterpret_cast<char*>(p_mapped_data) + offset, p_data, size);
    vezUnmapBuffer(vk_device, buffer->get_vk_buffer());
  }

  // BufferManager interface
  // ------------------------------------------------------------------------------

  buffer_manager create_buffer_manager(device device, vk::BufferUsageFlags usage,
      memory_usage memory_usage, utils::size_t chunk_size,
      utils::Allocator::Allocator const& Allocator)
  {
    return std::make_shared<buffer_manager_t>(device, usage, memory_usage, chunk_size, Allocator);
  }

  buffer_manager create_buffer_manager(
      device device, vk::BufferUsageFlags usage, memory_usage memory_usage)
  {
    return create_buffer_manager(device, usage, memory_usage, 300 * 1000 * 1000, {});
  }

  buffer allocate(buffer_manager buffer_manager, utils::size_t size, utils::alignment_t alignment)
  {
    return buffer_manager->allocate(size, alignment);
  }

  void cmd_bind(
      command_buffer, binding_info const& binding_info, std::vector<buffer> const& buffers)
  {
    for (auto const& buffer : buffers)
    {
      vezCmdBindBuffer(buffer->get_vk_buffer(), buffer->offset(), get_current_size(buffer),
          binding_info.set, binding_info.binding, binding_info.index);
    }
  }

  void cmd_bind(
      command_buffer command_buffer, binding_info const& binding_info, buffer binded_buffer)
  {
    cmd_bind(command_buffer, binding_info, std::vector<buffer>{binded_buffer});
  }
}  // namespace vulkan