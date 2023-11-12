#include "DeltaManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::string DeltaManager::GetDelta(std::filesystem::path v1, std::filesystem::path v2, std::string relativeParent = "")
{
	std::string delta = "";

	if (!std::filesystem::exists(v1) || !std::filesystem::exists(v2))
		return "";

	for (const auto& entry : std::filesystem::directory_iterator(v2)) {
		
		auto relative = std::filesystem::relative(entry, v2);
		auto relativeV1 = v1 / relative;

		if (entry.is_directory()) {			
			std::string relativePar = relative.string() + "\\";
			std::string subDelta = GetDelta(relativeV1, entry, relativePar);
			delta = MergeDeltas(delta, subDelta) + "\n";
		}

		if (!std::filesystem::exists(relativeV1)) {
			delta += "+++ " + relativeParent + relative.string() + "\n";
			continue;
		}

		std::ifstream ifs1(relativeV1);
		std::ifstream ifs2(entry.path());
		std::string str1, str2;
		std::stringstream buf1, buf2;

		buf1 << ifs1.rdbuf();		
		str1 = buf1.str();

		buf2 << ifs2.rdbuf();
		str2 = buf2.str();

		ifs1.close();
		ifs2.close();

		std::string changes = GetChanges(str1, str2);
		if (changes == "")
			continue;

		delta += "=== " + relativeParent + relative.string() + "\n" + changes + "\n";
	}

	for (const auto& entry : std::filesystem::directory_iterator(v1)) {
		std::filesystem::path relative = std::filesystem::relative(entry, v1);
		if (!std::filesystem::exists(v2 / relative)) {
			delta += "--- " + relativeParent + relative.string() + "\n";
		}
	}

	return delta;
}

std::string DeltaManager::GetChanges(std::string str1, std::string str2)
{
	if (str1._Equal(str2)) {
		return "";
	}

	std::istringstream ss1(str1), ss2(str2);
	std::vector<std::string> split1, split2;
	std::string temp;	
	char separator = '\n';

	while (std::getline(ss1, temp, separator)) {
		split1.push_back(temp);
	}
	while (std::getline(ss2, temp, separator)) {
		split2.push_back(temp);
	}

	std::string delta = "";

	int i = 0, j = 0;
	while (i < split1.size() || j < split2.size()) {

		bool inRange = i < split1.size() && j < split2.size();	
		if (inRange && split1.at(i)._Equal(split2.at(j))) {			
			i++;
			j++;
			continue;
		}			

		int k = split2.size();
		delta += "@@ " + std::to_string(i) + "\n";

		while (i < split1.size()) {

			auto it = find(split2.begin() + j, split2.end(), split1.at(i));
			if (it != split2.end()) {
				k = it - split2.begin();
				break;
			}

			delta += "-" + split1.at(i) + "\n";
			i++;
		}

		for (; j < k; j++) {
			delta += "+" + split2.at(j) + "\n";
		}

		delta += "@END\n";
	}

	return delta;
}

std::string DeltaManager::MergeDeltas(std::string delta1, std::string delta2)
{
	return delta1 + delta2;
}
