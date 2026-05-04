#include "lib.h"
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

    Movie m1 = { 1, "Inception", "Sci-Fi" };
    Cinema c1;
    c1.name = "Grand Central Cinema";
    c1.shows =
    {
        {"14:00", "Hall A", 1},
        {"17:30", "Hall B", 1},
        {"20:00", "Hall A", 1}
    };

    switch (choice)
    {
    case 1: std::cout << "Searching movies...\n"; break;
    case 2:
    {
        std::cout << "\n--- Current Showtimes ---\n";
        std::cout << "Cinema: " << c1.name << "\n";
        std::cout << "Movie: " << m1.title << " (" << m1.genre << ")\n";
        std::cout << "--------------------------\n";

        for (size_t i = 0; i < c1.shows.size(); ++i) {
            std::cout << i + 1 << ". " << c1.shows[i].time << " | " << c1.shows[i].hallName << "\n";
        }
        break;
    }
    case 3:
    {
        std::cout << "\n--- Seat Booking ---\n";
        std::cout << "Select Showtime (1-3): ";
        int showIdx;
        std::cin >> showIdx;

        if (showIdx < 1 || showIdx > 3) {
            std::cout << "Invalid showtime.\n";
            break;
        }

        Show& selectedShow = c1.shows[showIdx - 1];

        std::cout << "\nSeating Layout (0 = Available, X = Booked):\n";
        std::cout << "   1 2 3 4 5\n";
        for (int r = 0; r < 5; ++r) 
        {
            std::cout << r + 1 << "  ";
            for (int c = 0; c < 5; ++c) 
            {
                if (selectedShow.seating[r][c] == 0) 
                {
                    std::cout << "0 ";
                }
                else {
                    std::cout << "X ";
                }
            }
            std::cout << "\n";
        }

        std::cout << "\nEnter Row (1-5): ";
        int row;
        std::cin >> row;

        std::cout << "Enter Column (1-5): ";
        int col;
        std::cin >> col;

        if (row < 1 || row > 5 || col < 1 || col > 5) 
        {
            std::cout << "[ERROR] Invalid seat position!\n";
            break;
        }

        if (selectedShow.seating[row - 1][col - 1] == 1) 
        {
            std::cout << "[ERROR] Seat is already taken.\n";
        }
        else 
        {
            selectedShow.seating[row - 1][col - 1] = 1;

            double price = 10.0;
            if (row == 1) price = 25.0;
            else if (row == 2) price = 15.0;

            std::cout << "\n[SUCCESS] Seat booked successfully!\n";
            std::cout << "Price for this seat: $" << price << "\n";
        }
        break;
    }
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