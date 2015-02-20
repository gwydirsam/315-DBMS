
#include <main_menu.h>

main_menu:: void print_menu() {
	
	//Menu Dialogue 
	std::cout << "[Main Menu]\n\n";
	std::cout << "1. Make a new post.\n";
	std::cout << "2. Search for a post.\n";
	std::cout << "3. Exit.\n\n";
	std::cout << "* Enter command: ";
	std::cout << "\n";
	
	//Choice selection
	switch(input) {
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

main_menu:: string make_post() {
	//create post
}	

main_menu:: string search_menu() {
	//search through menu
}

main_menu:: void exit() {
	//exit main menu
}