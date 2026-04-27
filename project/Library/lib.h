#pragma once
#include <iostream>
#include <fstream>
#include "string"
#include <vector>
int f(int, int);
void Menu();
struct User
{
	std::string Username;
	int id;
	bool isAdmin = false;
	User(std::string name, int userId) : Username(name), id(userId) {}
};
struct Admin : User 
{
	int accessLevel;
	Admin(std::string name, int userId, int level) : User(name, userId), accessLevel(level) 
	{
		isAdmin = true;
	}
};


struct Show {
	std::string time;
	std::string hallName;
	int movieID;
};

struct Movie {
	int id;
	std::string title;
	std::string genre;
};

struct Cinema {
	std::string name;
	std::vector<Show> shows;
};