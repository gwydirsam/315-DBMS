
#include "search_menu.h"

std::string search_menu:: searches_menu() {
	
	//Search Menu Dialogue
	cout << "[Search Menu]\n\n";
	cout << "Search by:\n";
	cout << "1.\tAuthor\n"; 
	cout << "2.\tTitle\n"; 
	cout << "3.\tTag(s)\n";
	cout << "4.\tDate\n";
	cout << "5.\tReturn to Main Menu\n\n";
	cout<< "* Enter command: ";
	cin >> selection_input;
	cout << "\n";
	
	switch(selection_input) {
			case 1: std::cout << "* Enter Author: "; 
					std::cin >> str_input;
					search_by_author(std::string str_input);
					break;
			case 2: std::cout << "* Enter Title: "; 
					std::cin >> str_input;
					search_by_title(std::string str_input);
					break;
			case 3: std::cout << "* Enter Tag(s): "; 
					std::cin >> str_input;
					search_by_tag(std::string str_input);
					break;
			case 4: std::cout << "* Enter Date: "; 
					std::cin >> str_input;
					search_by_dates(std::string str_input);
					break;
			case 5: main_menu();
					break;
			default: 
					std::cout << "Incorrect input exiting program."; 
					exit(); 
					break;
	}
}

std::string search_menu:: search_by_author(std::string str_input) {
	std::string author;
	std::cout << "" << std::endl;
	std::cin >> author;
	return author;
}

std::string search_menu:: search_by_title(std::string str_input) {
	std::string title;
	std::cout << "" << std::endl;
	std::cin >> title;
	return title;
}

std::string search_menu:: search_by_tags(std::string str_input) {
	std::string tags;
	std::cout << "" << std::endl;
	std::cin >> tags;
	return tags;
}

std::string search_menu:: search_by_dates(std::string str_input) {
	std::string dates;
	std::cout << "" << std::endl;
	std::cin >> dates;
	return dates;
}

void search_menu:: return_to_menu() {
	print_menu();
}


