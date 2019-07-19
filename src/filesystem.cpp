#include "project.h"
#include "filesystem.h"
#include <fstream>

bool Filesystem::ReadFile(const std::string& path, std::string& outFileString)
{
	using namespace std;
	try
	{
		ifstream file;
		string fileString;

		file.exceptions(ifstream::failbit | ifstream::badbit);

		file.open(path);
		file.seekg(ifstream::end);
		outFileString.reserve(file.tellg());
		file.seekg(ifstream::beg);

		outFileString.assign(std::istreambuf_iterator<char>(file), {});

		return true;
	}
	catch (exception& e)
	{
		std::cout << "Filesystem::ReadFile exception\n" << e.what() << "\n";
		return false;
	}
}
