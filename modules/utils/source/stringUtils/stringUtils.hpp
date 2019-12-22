#pragma once
#include <filesystem>
#include <string>

namespace utils
{
  std::string readIsToString(std::istream &is);

  std::string readFileToString(std::filesystem::path const &path);

  std::vector<std::string> readIsToStringVec(std::istream &is);

  std::vector<std::string> readFileToStringVec(std::filesystem::path const &path);

  std::string stringVecToString(std::vector<std::string> const &src);

}  // namespace utils