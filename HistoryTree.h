#pragma once
#include <string>
#include <filesystem>

class HistoryTree
{
public:
	static void Add(std::filesystem::path path, std::string message, std::string author);
};

