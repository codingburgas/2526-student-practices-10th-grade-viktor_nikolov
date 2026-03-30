#pragma once
#include <iostream>
#include <fstream>
#include "string"
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