#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;
const std::string pw1 = "assword";
const std::string pw2 = "арол";

int main()
{
    std::vector<fs::path> pathes;
    std::string directory_name = "/home/";

    for (auto &p : fs::recursive_directory_iterator(directory_name))
    {
        if (!fs::is_regular_file(p.status()))
            continue;

        std::string name(p.path().filename());

        if (name.find(pw1) != -1)
            pathes.push_back(p.path());
        if (name.find(pw2) != -1)
            pathes.push_back(p.path());
    }

    for (int i = 0; i < pathes.size(); i++)
        std::cout << pathes[i] << '\n';
}