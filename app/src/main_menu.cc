
#include "main_menu.h"
#include "search_menu.h"

void main_menu:: print_menu() {
	
	//Menu Dialogue 
	std::cout << "[Main Menu]\n\n";
	std::cout << "1. Make a new post.\n";
	std::cout << "2. Search for a post.\n";
	std::cout << "3. Exit.\n\n";
	std::cout << "* Enter command: ";
	std::cout << "\n";
	
	//Choice selection
	switch(selection_input) {
		case 1: make_post(); 
				break;
		case 2: search_menu_.search_menu(); 
				break;
		case 3: exit();
				break;
		default: 
			std::cout << "Incorrect input exiting program."; 
			exit(); 
			break;
	}
}

std::string main_menu:: make_post() {
	std::string post;
	std::cout << "New post: " << std::endl;
	std::getline(std::cin, post);
	return post;
}

void main_menu:: exit() {
	//exit main menu
}