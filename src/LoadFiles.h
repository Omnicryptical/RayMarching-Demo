#pragma once

#include <string>
#include <fstream>
#include <sstream>

static std::string LoadTextFile(std::string filename)
{
	std::ifstream stream;
    stream.open(filename.c_str(), std::ifstream::in);

	std::string line;
	std::stringstream ss;
	for (std::string line; std::getline(stream, line); ) {
		ss << line << '\n';
	}

	return ss.str();
}
