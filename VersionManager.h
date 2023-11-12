#pragma once
#include <filesystem>
#include <string>

class VersionManager
{
public:
	static std::filesystem::path GetVersion(std::filesystem::path repoPath, int versionID);
	static void BuildVersion(std::filesystem::path keyFrame, std::string delta);
};

