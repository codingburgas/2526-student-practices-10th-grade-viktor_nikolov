#include "lib.h"
#include <algorithm>

void Menu()
{
    Admin adminUser("Alice_Manager", 1, 5);
    User* currentUser = &adminUser;

    std::vector<Movie> movies = {
        { 1, "Inception", "Sci-Fi" },
        { 2, "The Dark Knight", "Action" },
        { 3, "Interstellar", "Sci-Fi" }
    };
    std::vector<Payment> incomingPayments;
    Cinema c1;
    c1.name = "Grand Central Cinema";
    c1.shows =
    {
        {"14:00", "Hall A", 1},
        {"17:30", "Hall B", 2},
        {"20:00", "Hall A", 1}
    };

    int choice;

    do
    {
        std::ifstream file("../menu.txt");
        std::string line;

        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }
        file.close();

        std::cout << "\nEnter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::cout << "\n--- Movie Database Catalog ---\n";
            if (movies.empty()) {
                std::cout << "No movies available in the database.\n";
                break;
            }

            for (size_t i = 0; i < movies.size(); ++i) {
                std::cout << "- " << movies[i].title << " (" << movies[i].genre << ")\n";
            }

            std::cout << "\n[SEARCH BAR] Enter movie title to search: ";
            std::string searchQuery;
            std::cin >> std::ws;
            std::getline(std::cin, searchQuery);

            std::string searchLower = searchQuery;
            std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

            bool found = false;
            std::cout << "\n--- Search Results ---\n";
            for (const auto& m : movies) {
                std::string movieTitleLower = m.title;
                std::transform(movieTitleLower.begin(), movieTitleLower.end(), movieTitleLower.begin(), ::tolower);


                if (movieTitleLower.find(searchLower) != std::string::npos) {
                    found = true;
                    std::cout << "[AVAILABLE] \"" << m.title << "\" [" << m.genre << "]\n";

                    bool hasShows = false;
                    for (const auto& show : c1.shows) {
                        if (show.movieId == m.id) {
                            if (!hasShows) {
                                std::cout << "  -> Showtimes: ";
                                hasShows = true;
                            }
                            std::cout << show.time << " (" << show.hallName << ")  ";
                        }
                    }
                    if (!hasShows) {
                        std::cout << "  -> No scheduled showtimes currently.";
                    }
                    std::cout << "\n";
                }
            }

            if (!found) {
                std::cout << "[NOT FOUND] Sorry, \"" << searchQuery << "\" is not available.\n";
            }
            break;
        }
        case 2:
        {
            std::cout << "\n--- Current Showtimes ---\n";
            std::cout << "Cinema: " << c1.name << "\n";
            std::cout << "--------------------------\n";

            for (size_t i = 0; i < c1.shows.size(); ++i) {
                std::string currentMovieTitle = "Unknown Movie";
                for (const auto& m : movies) {
                    if (m.id == c1.shows[i].movieId) {
                        currentMovieTitle = m.title;
                        break;
                    }
                }
                std::cout << i + 1 << ". [" << currentMovieTitle << "] | "
                    << c1.shows[i].time << " | " << c1.shows[i].hallName << "\n";
            }
            break;
        }
        case 3:
        {
            std::cout << "\n--- Seat Booking ---\n";
            std::cout << "Select Showtime (1-" << c1.shows.size() << "): ";
            int showIdx;
            std::cin >> showIdx;

            if (showIdx < 1 || showIdx > static_cast<int>(c1.shows.size())) {
                std::cout << "Invalid showtime.\n";
                break;
            }

            Show& selectedShow = c1.shows[showIdx - 1];

            std::string bookingMovieTitle = "Unknown Movie";
            for (const auto& m : movies) {
                if (m.id == selectedShow.movieId) {
                    bookingMovieTitle = m.title;
                    break;
                }
            }

            std::cout << "\nBooking for: " << bookingMovieTitle << " (" << selectedShow.time << ")\n";
            std::cout << "Seating Layout (0 = Available, X = Booked):\n";
            std::cout << "   1 2 3 4 5\n";
            for (int r = 0; r < 5; ++r)
            {
                std::cout << r + 1 << "  ";
                for (int c = 0; c < 5; ++c)
                {
                    if (selectedShow.seating[r][c] == 0) std::cout << "0 ";
                    else std::cout << "X ";
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

                incomingPayments.push_back({ bookingMovieTitle, selectedShow.time, row, col, price });

                std::cout << "\n[SUCCESS] Seat booked successfully!\n";
                std::cout << "Price for this seat: $" << price << "\n";
            }
            break;
        }
        case 4:
        {
            std::cout << "\n--- Incoming Payments History ---\n";

            if (incomingPayments.empty()) {
                std::cout << "No incoming payments recorded yet.\n";
                break;
            }

            double totalRevenue = 0.0;
            for (size_t i = 0; i < incomingPayments.size(); ++i) {
                const auto& p = incomingPayments[i];
                std::cout << i + 1 << ". Movie: \"" << p.movieTitle << "\"\n"
                    << "   Time: " << p.showTime << "\n"
                    << "   Seat: Row " << p.row << ", Col " << p.col << "\n"
                    << "   Amount Paid: $" << p.amount << "\n"
                    << "---------------------------------\n";
                totalRevenue += p.amount;
            }

            std::cout << "Total Revenue Collected: $" << totalRevenue << "\n";
            break;
        }

        case 5:
            if (currentUser->isAdmin)
            {
                Admin* adminPtr = static_cast<Admin*>(currentUser);
                int adminChoice;

                do {
                    std::cout << "\n[ADMIN ACCESS GRANTED]\n";
                    std::cout << "1. Add Show (Type Movie Name)\n2. Delete Show\n3. View/Edit Movies\n4. Back to Main Menu\n";
                    std::cout << "Enter Admin Action: ";
                    std::cin >> adminChoice;

                    if (adminChoice == 1)
                    {
                        Show newShow;
                        std::cout << "Enter Show Time (e.g. 22:15): ";
                        std::cin >> newShow.time;
                        std::cout << "Enter Hall Name (e.g. Hall C): ";
                        std::cin >> newShow.hallName;

                        std::cout << "Enter Movie Title: ";
                        std::string typedTitle;
                        std::cin >> std::ws;
                        std::getline(std::cin, typedTitle);

                        int targetMovieId = -1;
                        for (const auto& m : movies) {
                            if (m.title == typedTitle) {
                                targetMovieId = m.id;
                                break;
                            }
                        }

                        if (targetMovieId == -1) {
                            Movie newMovie;
                            newMovie.id = static_cast<int>(movies.size() + 1);
                            newMovie.title = typedTitle;
                            std::cout << "New movie detected! Enter genre for \"" << typedTitle << "\": ";
                            std::getline(std::cin, newMovie.genre);

                            movies.push_back(newMovie);
                            targetMovieId = newMovie.id;
                        }

                        newShow.movieId = targetMovieId;

                        for (int r = 0; r < 5; ++r)
                            for (int c = 0; c < 5; ++c)
                                newShow.seating[r][c] = 0;

                        c1.shows.push_back(newShow);
                        std::cout << "[SUCCESS] Show for \"" << typedTitle << "\" added successfully!\n";
                    }
                    else if (adminChoice == 2)
                    {
                        if (c1.shows.empty()) {
                            std::cout << "[INFO] No shows available to delete.\n";
                            continue;
                        }

                        std::cout << "\nSelect show number to delete:\n";
                        for (size_t i = 0; i < c1.shows.size(); ++i) {
                            std::string sTitle = "Unknown Movie";
                            for (const auto& m : movies) {
                                if (m.id == c1.shows[i].movieId) { sTitle = m.title; break; }
                            }
                            std::cout << i + 1 << ". [" << sTitle << "] | " << c1.shows[i].time << " | " << c1.shows[i].hallName << "\n";
                        }

                        int delIdx;
                        std::cout << "Enter number: ";
                        std::cin >> delIdx;

                        if (delIdx >= 1 && delIdx <= static_cast<int>(c1.shows.size())) {
                            c1.shows.erase(c1.shows.begin() + (delIdx - 1));
                            std::cout << "[SUCCESS] Show deleted successfully!\n";
                        }
                        else {
                            std::cout << "[ERROR] Invalid selection.\n";
                        }
                    }
                    else if (adminChoice == 3)
                    {
                        std::cout << "\n--- Movie Database ---\n";
                        for (size_t i = 0; i < movies.size(); ++i) {
                            std::cout << i + 1 << ". " << movies[i].title << " [" << movies[i].genre << "]\n";
                        }

                        std::cout << "\n1. Edit Existing Movie Title\n2. Back\nChoice: ";
                        int subChoice;
                        std::cin >> subChoice;

                        if (subChoice == 1) {
                            std::cout << "Select movie number to edit (1-" << movies.size() << "): ";
                            int editIdx;
                            std::cin >> editIdx;

                            if (editIdx >= 1 && editIdx <= static_cast<int>(movies.size())) {
                                std::cout << "Enter new title: ";
                                std::cin >> std::ws;
                                std::getline(std::cin, movies[editIdx - 1].title);

                                std::cout << "Enter new genre: ";
                                std::getline(std::cin, movies[editIdx - 1].genre);
                                std::cout << "[SUCCESS] Movie updated!\n";
                            }
                            else {
                                std::cout << "[ERROR] Invalid choice.\n";
                            }
                        }
                    }
                } while (adminChoice != 4);
            }
            else {
                std::cout << "\n[ERROR] Access Denied. You are not an admin.\n";
            }
            break;

        case 6:
            std::cout << "Goodbye!\n";
            break;

        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        std::cout << "\n====================================\n";

    } while (choice != 6);
}