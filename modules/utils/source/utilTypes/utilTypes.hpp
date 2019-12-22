#pragma once
#include <iosfwd>

namespace utils
{
  // Extent -----------------------------------------------------------------------------------------------------------

  template <typename T>
  class BasicExtent2D
  {
   public:
    BasicExtent2D() = default;

    explicit BasicExtent2D(T const &width, T const &height) : width_(width), height_(height)
    {
    }

    T width() const
    {
      return width_;
    }

    T height() const
    {
      return height_;
    }

    void setWidth(T const &val)
    {
      width_ = val;
    }

    void setHeight(T const &val)
    {
      height_ = val;
    }

   private:
    T width_ = {};
    T height_ = {};
  };

  template <typename T1, typename T2>
  bool operator==(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height();
  }

  template <typename T1, typename T2>
  bool operator!=(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1, typename T2>
  bool operator<(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    if (lhs.width() < rhs.width_) return true;
    if (rhs.width() < lhs.width()) return false;
    return lhs.height() < rhs.height();
  }

  template <typename T1, typename T2>
  bool operator>(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return rhs < lhs;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return !(rhs < lhs);
  }

  template <typename T1, typename T2>
  bool operator>=(BasicExtent2D<T1> const &lhs, BasicExtent2D<T2> const &rhs)
  {
    return !(lhs < rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicExtent2D<T> const &rhs)
  {
    os << rhs.width() << " " << rhs.height();
    return os;
  }

  template <typename T>
  std::istream &operator>>(std::istream &is, BasicExtent2D<T> &rhs)
  {
    T x, y;
    is >> x >> y;
    rhs.setWidth(x);
    rhs.setHeight(y);
    return is;
  }

  template <typename T>
  class BasicExtent3D
  {
   public:
    BasicExtent3D() = default;

    explicit BasicExtent3D(T const &width, T const &height, T const &depth)
        : width_(width), height_(height), depth_(depth)
    {
    }

    explicit operator BasicExtent2D<T>()
    {
      return BasicExtent2D<T>(width(), height());
    }

    T width() const
    {
      return width_;
    }

    T height() const
    {
      return height_;
    }

    T depth() const
    {
      return depth_;
    }

    void setWidth(T const &val)
    {
      width_ = val;
    }

    void setHeight(T const &val)
    {
      height_ = val;
    }

    void setDepth(T const &val)
    {
      depth_ = val;
    }

   private:
    T width_ = {};
    T height_ = {};
    T depth_ = {};
  };

  template <typename T1, typename T2>
  bool operator==(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height() && lhs.depth() == rhs.depth();
  }

  template <typename T1, typename T2>
  bool operator!=(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1, typename T2>
  bool operator<(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    if (lhs.width() < rhs.width()) return true;
    if (rhs.width() < lhs.width()) return false;
    if (lhs.height() < rhs.height()) return true;
    if (rhs.height() < lhs.height()) return false;
    return lhs.depth() < rhs.depth();
  }

  template <typename T1, typename T2>
  bool operator>(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return rhs < lhs;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return !(rhs < lhs);
  }

  template <typename T1, typename T2>
  bool operator>=(BasicExtent3D<T1> const &lhs, BasicExtent3D<T2> const &rhs)
  {
    return !(lhs < rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicExtent3D<T> const &rhs)
  {
    os << rhs.width() << " " << rhs.height() << " " << rhs.depth();
    return os;
  }

  template <typename T>
  std::istream &operator>>(std::istream &is, BasicExtent3D<T> &rhs)
  {
    T x, y, z;
    is >> x >> y >> z;
    rhs.setWidth(x);
    rhs.setHeight(y);
    rhs.setDepth(z);
    return is;
  }

  // Position -------------------------------------------------------------------------------------------------------

  template <typename T>
  class BasicPosition2D
  {
    template <typename T1, typename T2>
    friend bool operator==(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, BasicPosition2D<T1> const &rhs);

    template <typename T1>
    friend std::istream &operator>>(std::istream &is, BasicPosition2D<T1> &rhs);

    template <typename T1, typename T2>
    friend bool operator<(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator<=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs);

   public:
    BasicPosition2D() = default;

    explicit BasicPosition2D(T const &x, T const &y) : base_(x, y)
    {
    }

    T x() const
    {
      return base_.width();
    }

    T y() const
    {
      return base_.height();
    }

    void setX(T const &val)
    {
      base_.setWidth(val);
    }

    void setY(T const &val)
    {
      base_.setHeight(val);
    }

   private:
    BasicExtent2D<T> base_;
  };

  template <typename T1, typename T2>
  bool operator==(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ == rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator!=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1>
  std::ostream &operator<<(std::ostream &os, BasicPosition2D<T1> const &rhs)
  {
    return os << rhs.base_;
  }

  template <typename T1>
  std::istream &operator>>(std::istream &is, BasicPosition2D<T1> &rhs)
  {
    return is >> rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ < rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ > rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ <= rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>=(BasicPosition2D<T1> const &lhs, BasicPosition2D<T2> const &rhs)
  {
    return lhs.base_ >= rhs.base_;
  }

  template <typename T>
  class BasicPosition3D
  {
    template <typename T1, typename T2>
    friend bool operator==(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, BasicPosition3D<T1> const &rhs);

    template <typename T1>
    friend std::istream &operator>>(std::istream &is, BasicPosition3D<T1> &rhs);

    template <typename T1, typename T2>
    friend bool operator<(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator<=(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>=(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs);

   public:
    BasicPosition3D() = default;

    explicit BasicPosition3D(T const &x, T const &y, T const &z) : base_(x, y, z)
    {
    }

    explicit operator BasicExtent2D<T>()
    {
      return BasicExtent2D<T>(x(), y());
    }

    T x() const
    {
      return base_.width();
    }

    T y() const
    {
      return base_.height();
    }

    T z() const
    {
      return base_.depth();
    }

    void setX(T const &val)
    {
      base_.setWidth(val);
    }

    void setY(T const &val)
    {
      base_.setHeight(val);
    }

    void setZ(T const &val)
    {
      base_.setDepth(val);
    }

   private:
    BasicExtent3D<T> base_;
  };

  template <typename T>
  bool operator==(BasicPosition3D<T> const &lhs, BasicPosition3D<T> const &rhs)
  {
    return lhs.base_ == rhs.base_;
  }

  template <typename T>
  bool operator!=(BasicPosition3D<T> const &lhs, BasicPosition3D<T> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicPosition3D<T> const &rhs)
  {
    return os << rhs.base_;
  }

  template <typename T1>
  std::istream &operator>>(std::istream &is, BasicPosition3D<T1> &rhs)
  {
    return is >> rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs)
  {
    return lhs.base_ < rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs)
  {
    return lhs.base_ > rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs)
  {
    return lhs.base_ <= rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>=(BasicPosition3D<T1> const &lhs, BasicPosition3D<T2> const &rhs)
  {
    return lhs.base_ >= rhs.base_;
  }

  // Offset ---------------------------------------------------------------------------------------------------------

  template <typename T>
  class BasicOffset2D
  {
    template <typename T1, typename T2>
    friend bool operator==(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, BasicOffset2D<T1> const &rhs);

    template <typename T1>
    friend std::istream &operator>>(std::istream &is, BasicOffset2D<T1> &rhs);

    template <typename T1, typename T2>
    friend bool operator<(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator<=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs);

   public:
    BasicOffset2D() = default;

    explicit BasicOffset2D(T const &x, T const &y) : base_(x, y)
    {
    }

    T x() const
    {
      return base_.width();
    }

    T y() const
    {
      return base_.height();
    }

    void setX(T const &val)
    {
      base_.setWidth(val);
    }

    void setY(T const &val)
    {
      base_.setHeight(val);
    }

   private:
    BasicExtent2D<T> base_;
  };

  template <typename T1, typename T2>
  bool operator==(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ == rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator!=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T1>
  std::ostream &operator<<(std::ostream &os, BasicOffset2D<T1> const &rhs)
  {
    return os << rhs.base_;
  }

  template <typename T1>
  std::istream &operator>>(std::istream &is, BasicOffset2D<T1> &rhs)
  {
    return is >> rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ < rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ > rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ <= rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>=(BasicOffset2D<T1> const &lhs, BasicOffset2D<T2> const &rhs)
  {
    return lhs.base_ >= rhs.base_;
  }

  template <typename T>
  class BasicOffset3D
  {
    template <typename T1, typename T2>
    friend bool operator==(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, BasicOffset3D<T1> const &rhs);

    template <typename T1>
    friend std::istream &operator>>(std::istream &is, BasicOffset3D<T1> &rhs);

    template <typename T1, typename T2>
    friend bool operator<(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator<=(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

    template <typename T1, typename T2>
    friend bool operator>=(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs);

   public:
    BasicOffset3D() = default;

    explicit BasicOffset3D(T const &x, T const &y, T const &z) : base_(x, y, z)
    {
    }

    explicit operator BasicExtent2D<T>()
    {
      return BasicExtent2D<T>(x(), y());
    }

    T x() const
    {
      return base_.width();
    }

    T y() const
    {
      return base_.height();
    }

    T z() const
    {
      return base_.depth();
    }

    void setX(T const &val)
    {
      base_.setWidth(val);
    }

    void setY(T const &val)
    {
      base_.setHeight(val);
    }

    void setZ(T const &val)
    {
      base_.setDepth(val);
    }

   private:
    BasicExtent3D<T> base_;
  };

  template <typename T>
  bool operator==(BasicOffset3D<T> const &lhs, BasicOffset3D<T> const &rhs)
  {
    return lhs.base_ == rhs.base_;
  }

  template <typename T>
  bool operator!=(BasicOffset3D<T> const &lhs, BasicOffset3D<T> const &rhs)
  {
    return !(lhs == rhs);
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, BasicOffset3D<T> const &rhs)
  {
    return os << rhs.base_;
  }

  template <typename T1>
  std::istream &operator>>(std::istream &is, BasicOffset3D<T1> &rhs)
  {
    return is >> rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs)
  {
    return lhs.base_ < rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs)
  {
    return lhs.base_ > rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator<=(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs)
  {
    return lhs.base_ <= rhs.base_;
  }

  template <typename T1, typename T2>
  bool operator>=(BasicOffset3D<T1> const &lhs, BasicOffset3D<T2> const &rhs)
  {
    return lhs.base_ >= rhs.base_;
  }

  // aliases ----------------------------------------------------------------------------------------------------------

  using SizeT = std::size_t;
  using OffsetT = SizeT;
  using AlignmentT = SizeT;
  using IndexT = SizeT;

  using Extent2D = BasicExtent2D<unsigned>;
  using Extent2Df = BasicExtent2D<float>;

  using Extent3D = BasicExtent3D<unsigned>;
  using Extent3Df = BasicExtent3D<float>;

  using Position2D = BasicPosition2D<unsigned>;
  using Position2Df = BasicPosition2D<float>;

  using Position3D = BasicPosition3D<unsigned>;
  using Position3Df = BasicPosition3D<float>;

  using Offset2D = BasicOffset2D<int>;
  using Offset2Df = BasicOffset2D<float>;

  using Offset3D = BasicOffset3D<int>;
  using Offset3Df = BasicOffset3D<float>;

}  // namespace utils