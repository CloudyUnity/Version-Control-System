#include "Initialiser.h"
#include <fstream>

void Initialiser::InitVCS(std::filesystem::path path) 
{
    path /= ".vcs";
    if (std::filesystem::exists(path)) 
    {
        std::cout << "VCS already initliased in this directory";
        return;
    }

    std::cout << "Initialising VCS in " + path.string() << std::endl;

    std::filesystem::create_directories(path);

    auto tmpPath = path / "HistoryTree.txt";
    std::ofstream ofs(tmpPath.string());
    ofs.close();

    tmpPath = path / "VersionInfo.txt";
    ofs = std::ofstream(tmpPath.string());
    ofs.close();

    tmpPath = path / "CurrentInfo.txt";
    ofs = std::ofstream(tmpPath.string());
    ofs.close();
}
