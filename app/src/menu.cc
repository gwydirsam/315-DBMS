#include "menu.h"

std::string Menu::print_menu() {
	int selection_input;
	//Menu Dialogue 
	std::cout << "[Main Menu]\n\n";
	std::cout << "1. Make a new post.\n";
	std::cout << "2. Search for a post.\n";
	std::cout << "3. Exit.\n\n";
	std::cout << "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	//Choice selection
	switch(selection_input) {
		case 1: make_post(); 
				break;
		case 2: search_menu(); 
				break;
		case 3: exit();
				break;
		default: 
			std::cout << "Incorrect input exiting program."; 
			exit(); 
			break;
	}
}

std::string Menu::make_post() {
	std::string post;
	std::cout << "New post: " << std::endl;
	std::getline(std::cin, post);
	return post;
}

void Menu::exit() {
	//exit main menu
}

//search menu
std::string Menu::search_menu() {
	std::string str_input;
	int selection_input;
	//Search Menu Dialogue
	std::cout << "[Search Menu]\n\n";
	std::cout << "Search by:\n";
	std::cout << "1.\tAuthor\n"; 
	std::cout << "2.\tTitle\n"; 
	std::cout << "3.\tTag(s)\n";
	std::cout << "4.\tDate\n";
	std::cout << "5.\tReturn to Main Menu\n\n";
	std::cout<< "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
			case 1: std::cout << "* Enter Author: "; 
					std::cin >> str_input;
					search_by_author(str_input);
					break;
			case 2: std::cout << "* Enter Title: "; 
					std::cin >> str_input;
					search_by_title(str_input);
					break;
			case 3: std::cout << "* Enter Tag(s): "; 
					std::cin >> str_input;
					search_by_tags(str_input);
					break;
			case 4: std::cout << "* Enter Date: "; 
					std::cin >> str_input;
					search_by_dates(str_input);
					break;
			case 5: Menu();
					break;
			default: 
					std::cout << "Incorrect input exiting program."; 
					exit(); 
					break;
	}
}

std::string Menu::search_by_author(std::string str_input) {
	std::string author;
	std::cout << "" << std::endl;
	std::cin >> author;
	return author;
}

std::string Menu::search_by_title(std::string str_input) {
	std::string title;
	std::cout << "" << std::endl;
	std::cin >> title;
	return title;
}

std::string Menu::search_by_tags(std::string str_input) {
	std::string tags;
	std::cout << "" << std::endl;
	std::cin >> tags;
	return tags;
}

std::string Menu::search_by_dates(std::string str_input) {
	std::string dates;
	std::cout << "" << std::endl;
	std::cin >> dates;
	return dates;
}

std::string Menu::return_to_menu() {
	print_menu();
}

