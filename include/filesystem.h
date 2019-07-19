#pragma once
#include <string>
#include <optional>

namespace Filesystem
{
	bool ReadFile(const std::string& path, std::string& outFileString);
};