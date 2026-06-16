#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

struct Movie {
    int id;
    std::string title;
    std::string genre;
};

struct Show {
    std::string time;
    std::string hallName;
    int movieId;
    int seating[5][5] = { 0 };
};

struct Cinema {
    std::string name;
    std::vector<Show> shows;
};
struct Payment {
    std::string movieTitle;
    std::string showTime;
    int row;
    int col;
    double amount;
};

class User {
public:
    std::string username;
    int id;
    bool isAdmin;
    User(std::string name, int userId, bool admin)
        : username(name), id(userId), isAdmin(admin) {
    }
};

class Admin : public User {
public:
    int accessLevel;
    Admin(std::string name, int userId, int access)
        : User(name, userId, true), accessLevel(access) {
    }
};
void Menu();