#include "../Device/DeviceImpl.hpp"
#include "BufferManager.hpp"
#include "BufferT.hpp"

namespace vulkan
{
  // utils
  // -------------------------------------------------------------------------------------------------

  VezMemoryFlags to_vk_memory_usage(memory_usage flag);

  // buffer_block
  // ------------------------------------------------------------------------------------------

  class buffer_block
  {
   public:
    buffer_block(device device, vk::BufferUsageFlags usage, memory_usage memory_usage,
        utils::size_t block_size, utils::Allocator::Allocator const& Allocator);

    ~buffer_block()
    {
      vezDestroyBuffer(device_->get_vk_device(), vk_buffer_);
    }

    buffer allocate(utils::size_t size, utils::alignment_t alignment)
    {
      if (allocator_.requiedExtension(size, alignment) + allocator_.size() > block_size_)
      {
        throw std::runtime_error("no place for Allocation");
      }
      return std::make_shared<buffer_t>(device_, allocator_.allocate(size, alignment), vk_buffer_);
    }

   private:
    device device_;
    utils::Allocator::Allocator allocator_;
    utils::size_t block_size_;
    vk::Buffer vk_buffer_;
  };

  // buffer_manager_t
  // --------------------------------------------------------------------------------------

  class buffer_manager_t
  {
   public:
    buffer_manager_t(device device, vk::BufferUsageFlags usage, memory_usage memory_usage,
        utils::size_t block_size, utils::Allocator::Allocator const& Allocator)
        : device_(device),
          usage_(usage),
          memory_usage_(memory_usage),
          block_size_(block_size),
          allocator_(Allocator)
    {
    }

    buffer allocate(utils::size_t size, utils::alignment_t alignment)
    {
      for (auto& block : buffer_blocks_)
      {
        try
        {
          return block.allocate(size, alignment);
        }
        catch (std::runtime_error const&)
        {
        }
      }
      buffer_blocks_.emplace_back(device_, usage_, memory_usage_, block_size_, allocator_);
      return buffer_blocks_.back().allocate(size, alignment);
    }

   private:
    device device_;
    vk::BufferUsageFlags usage_;
    memory_usage memory_usage_;
    utils::size_t block_size_;
    utils::Allocator::Allocator allocator_;
    std::vector<buffer_block> buffer_blocks_;
  };
}  // namespace vulkan