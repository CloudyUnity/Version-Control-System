#include "Adder.h"

void Adder::Add(std::filesystem::path path, std::vector<std::string> files) {

	auto infoPath = path / ".vcs/CurrentInfo.txt";
	std::ifstream istream(infoPath.string());
	std::string info = "";
	istream >> info;
	istream.close();

	int versionID = std::stoi(info);
	auto currentVersionPath = VersionManager::GetVersion(path, versionID);
	std::string delta = DeltaManager::GetDelta(currentVersionPath, path, "");

	auto cwcPath = path / ".vcs/CWC.txt";
	istream = std::ifstream(cwcPath.string());
	std::string existingDeltas = "";
	istream >> existingDeltas;
	istream.close();

	delta = DeltaManager::MergeDeltas(delta, existingDeltas);

	std::ofstream ofs(cwcPath.string());
	ofs << delta;
	ofs.close();
}