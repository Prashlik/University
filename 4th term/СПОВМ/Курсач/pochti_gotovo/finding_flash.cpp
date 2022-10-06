#include <filesystem>
#include <iostream>
#include <string>
#include <vector>


namespace fs = std::filesystem;
const string pw1 = "password";
const string pw2 = "пароль";

int main()
{
    vstd::ector<fs::path> pathes;
    std::string directory_name = "/media/";
    std::string extension = ".txt";

    for (auto &p : fs::recursive_directory_iterator(directory_name))
    {
        if (!fs::is_directory(p.status()))
            continue;

        std::string name(p.path().filename());

        pathes.push_back(p.path());
    }

    for (int i = 0; i < pathes.size(); i++)
        cout << pathes[i] << '\n';
}