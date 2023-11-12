#include <filesystem>
#include <string>
#include <iostream>
#include "Initialiser.h"
#include "DeltaManager.h"

int main(int argc, char* argv[])
{
    auto currentPath = std::filesystem::current_path();

    if (argc <= 1)
    {
        std::cout << "Program opened with no arguments. Terminating program";
        return 0;
    }
    if (argv[1] == nullptr) {
        std::cout << "Invalid arguments" << std::endl;
        return 0;
    }
    std::string arg1 = argv[1];

    if (arg1 == "init")
        Initialiser::InitVCS(currentPath);

    std::filesystem::path path1 = std::filesystem::path("C:\\Users\\finnw\\OneDrive\\Documents\\VCS Test Repo");
    std::filesystem::path path2 = std::filesystem::path("C:\\Users\\finnw\\OneDrive\\Documents\\VCS Test Repo - Copy");

    std::string s1 = "A\nB\nC\nD";
    std::string s2 = "A\nX\nD";

    if (arg1 == "test") {
        //std::cout << DeltaManager::GetChanges(s1, s2) << std::endl;

        std::string s = DeltaManager::GetDelta(path1, path2, "");
        std::cout << s << std::endl;
    }

    if (arg1 == "add") { 
        //DeltaManager::GetDelta(currentPath, currentPath);
    }

    if (strcmp(argv[1], "commit") == 0) {
        // Take CWC
        // Create new version/delta
        // Clear CWC
    }

    if (strcmp(argv[1], "rollback") == 0) {
        // Get following arg (int)
        // Find version/delta for that int
        // Build version from delta
        // Clear repo data except .vcs
        // Copy version into repo
        // Clear CWC
    }

    if (strcmp(argv[1], "diff") == 0) {
        // Get following args (file names x2)
        // Display delta between files in console
    }

    if (strcmp(argv[1], "branch") == 0) {
        // Get version 
        // Replace current Repo
        // Add to HistoryTree and versions
    }

    // std::cout << "Program completed. Press any key to continue." << std::endl;
    // std::cin.get();

    return 0;
}
