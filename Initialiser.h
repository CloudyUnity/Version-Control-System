#pragma once
#include <filesystem>
#include <iostream>

class Initialiser
{
public:
	static void InitVCS(std::filesystem::path path);
};

