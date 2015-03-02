#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <iostream>
#include <string>

#include "search_menu.h"

class main_menu {
public:
	//Constructor:
	//Destructor:
	//Global:
		int selection_input;
	//Getters:
	//Setters:
		
	//Functions:
	void print_menu();
	std::string make_post();
	void exit();
private:
search_menu search_menu_;
};
#endif  // MAIN_MENU_H_
