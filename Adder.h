#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include "VersionManager.h"
#include "DeltaManager.h"

class Adder
{
public:
	static void Add(std::filesystem::path path, std::vector<std::string> files);
};

