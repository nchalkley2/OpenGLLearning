#include "project.h"
#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Image::dataDeleter::operator()(unsigned char* data)
{
	stbi_image_free(data);
}

Image::Image(const std::string& inPath): path(inPath)
{
	data = decltype(data)(stbi_load(inPath.c_str(), &width, &height, &numChannels, STBI_default));
}