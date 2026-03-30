#include "lib.h"
int f(int a, int b)
{
	return a + b;
}
void Menu()
{
    std::ifstream file("../menu.txt");

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
    int choice;
    std::cin >> choice;
    Admin adminUser("Alice_Manager", 1, 5);
    User* currentUser = &adminUser;
    switch (choice) {
    case 1: std::cout << "Searching movies...\n"; break;
    case 2: std::cout << "Viewing showtimes...\n"; break;
    case 3: std::cout << "Booking seat...\n"; break;
    case 4: std::cout << "Processing payment...\n"; break;

    case 5:
        if (currentUser->isAdmin) 
        {
            Admin* adminPtr = static_cast<Admin*>(currentUser);
            std::cout << "\n[ADMIN ACCESS GRANTED]\n";
            std::cout << "Admin ID: " << adminPtr->id << "\n";
            std::cout << "Security Level: " << adminPtr->accessLevel << "\n";
            std::cout << "1. Add Movie\n2. Delete Show\n";
        }
        else {
            std::cout << "\n[ERROR] Access Denied. You are not an admin.\n";
        }
        break;

    case 6: std::cout << "Goodbye!\n"; break;
    default: std::cout << "Invalid choice.\n"; break;
    }
}