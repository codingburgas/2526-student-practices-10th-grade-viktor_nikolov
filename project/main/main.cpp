#include "../Library/lib.h"
int main()
{
	void f()
	{
		std::cout << ifstream("menu/txt").rdbuf();
	}
	
}
