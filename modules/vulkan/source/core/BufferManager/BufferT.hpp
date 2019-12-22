#pragma once
#include "../Device/DeviceImpl.hpp"
#include "BufferManager.hpp"

namespace vulkan
{
  // buffer_t
  // ---------------------------------------------------------------------------------------------

  class buffer_t
  {
   public:
    buffer_t(device device, utils::Allocator::Allocation const& Allocation, vk::Buffer buffer)
        : device_(device), allocation_(Allocation), buffer_(buffer)
    {
    }

    device get_device() const
    {
      return device_;
    }

    vk::Buffer get_vk_buffer() const
    {
      return buffer_;
    }

    utils::size_t size() const
    {
      return allocation_.size();
    }

    utils::offset_t offset() const
    {
      return allocation_.offset();
    }

   private:
    device device_;
    utils::Allocator::Allocation allocation_;
    vk::Buffer buffer_;
  };
}  // namespace vulkan