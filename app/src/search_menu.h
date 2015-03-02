#ifndef SEARCH_MENU_H_
#define SEARCH_MENU_H_

#include <iostream>
#include <string>


class search_menu {
public:
	//Constructor:
	//Destructor:
	//Global:
		std::string str_input;
		int search_input;
		int selection_input;
	//Getters:
	//Setters:
	
	void searches_menu();
	std::string search_by_author(std::string str_input);
	std::string search_by_title(std::string str_input);
	std::string search_by_tags(std::string str_input);
	std::string search_by_dates(std::string str_input);
	std::string return_to_menu();

};

#endif  //SEARCH_MENU_H_
