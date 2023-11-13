#pragma once
#include <string>
#include <filesystem>

class DeltaManager
{
public:
	static std::string GetDelta(std::filesystem::path v1, std::filesystem::path v2, std::string relativeParent);
	static std::string MergeDeltas(std::string delta1, std::string delta2);
	static std::string GetChanges(std::string str1, std::string str2);
	static void ApplyDelta(std::filesystem::path path, std::string delta);
};

