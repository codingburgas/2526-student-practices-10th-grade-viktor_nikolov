#include "../Library/lib.h"
void Menu()
{
    std::ifstream file("../menu.txt");

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}
int main()
{
    Menu();
}
