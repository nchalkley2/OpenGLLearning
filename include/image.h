#pragma once
#include <cstddef>
#include <memory>
#include <string>

class Image
{
public:
	Image(const std::string& inPath);

private:
	int width;
	int height;
	int numChannels;

	struct dataDeleter
	{
		void operator()(unsigned char* data);
	};

	std::unique_ptr<unsigned char, dataDeleter> data;
	std::string path;
};