#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>

class Menu {
public:
	//Constructor:
	//Destructor:
	//Global:
		std::string str_input;
		int m_selection_input;
		int s_selection_input;
		int search_input;
	//Getters:
	//Setters:
	//Functions:
	void exit();
	std::string print_menu();
	std::string search_menu();
	std::string make_post();
	std::string search_by_author(std::string str_input);
	std::string search_by_title(std::string str_input);
	std::string search_by_tags(std::string str_input);
	std::string search_by_dates(std::string str_input);
	std::string return_to_menu();
};
#endif  // MENU_H_
