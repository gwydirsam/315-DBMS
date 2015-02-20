#ifndef SEARCH_MENU_H_
#define SEARCH_MENU_H_

#include <iostream>

class search_menu() {
	//Constructor:
	//Destructor:
	//Global:
		std:: string str_input;
		std:: int search_input;
		std:: int selection_input;
	//Getters:
	//Setters:
	
	void search_menu();
	string search_by_author(str_input);
	string search_by_title(str_input);
	string search_by_tags(str_input);
	string search_by_dates(str_input);
	string return_to_menu() {};

}

#endif  //SEARCH_MENU_H_
