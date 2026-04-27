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
    switch (choice) 
    {
    case 1: std::cout << "Searching movies...\n"; break;
    case 2: 
    { 
        std::cout << "\n--- Current Showtimes ---\n";

        Movie m1 = { 1, "Inception", "Sci-Fi" };
        Cinema c1;
        c1.name = "Grand Central Cinema";
        c1.shows = 
        {
            {"14:00", "Hall A", 1},
            {"17:30", "Hall B", 1},
            {"20:00", "Hall A", 1}
        };

        std::cout << "Cinema: " << c1.name << "\n";
        std::cout << "Movie: " << m1.title << " (" << m1.genre << ")\n";
        std::cout << "--------------------------\n";

        for (const auto& s : c1.shows) {
            std::cout << "Time: " << s.time << " | " << s.hallName << "\n";
        }

        break;
    }
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