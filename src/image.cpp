#include "project.h"
#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
namespace stb
{
#include <stb_image.h>
};

void Image::dataDeleter::operator()(unsigned char* data)
{
	stb::stbi_image_free(data);
}

Image::Image(const std::string& inPath): path(inPath)
{
	data = decltype(data)(stb::stbi_load(inPath.c_str(), &width, &height, &numChannels, stb::STBI_default));
}