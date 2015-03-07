#include "menu.h"

void Menu::exit() {
	//exit main menu
}

void Menu::print_menu() {
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
			 std::cout <<"Incorrect input restarting this step.\nPlease try to enter 1-3."; 
			 print_menu(); break;
	}
}

//search menu
void Menu::search_menu() {
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
					std::getline(std::cin,str_input);
					search_by_author(str_input);
					break;
			case 2: std::cout << "* Enter Title: "; 
					std::getline(std::cin,str_input);
					search_by_title(str_input);
					break;
			case 3: std::cout << "* Enter Tag(s): "; 
					std::getline(std::cin,str_input);
					search_by_tags(str_input);
					break;
			case 4: std::cout << "* Enter Date: "; 
					std::cin >> str_input;
					std::getline(std::cin,str_input);
					break;
			case 5: print_menu();
					break;
			default: 
					std::cout <<
					"Incorrect input restarting this step.\nPlease try to enter 1-5."; 
					search_menu();
					break;
	}
}

//probably this will be passed the equivalent of a relation on group 16s DMS
void Menu::post_manage_system(std::string str_input) {
	int selection_input;
	// Post's Management System Dialogue
	//TODO std::cout << "["<< relation.title() <<"]\n\n"; 
	std::cout << "[]\n\n";
	std::cout << "1. View\n"; 
	std::cout << "2. Edit\n"; 
	std::cout << "3. Delete\n";
	std::cout << "4. Comment\n";
	std::cout << "5. Return to Main Menu\n\n";
	std::cout<< "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
			case 1: // TODO print_post
					// print_tags
					// print_comments and comments_on_comments
					post_manage_system(str_input);
					break;
			case 2: //TODO!!!
					break;
			case 3: //TODO!!! 
					//Maybe just deletion the relation from their 
					//version of open tables and its file
					break;
			case 4: comments_menu(str_input);
					break;
			case 5: print_menu();
					break;
			default: 
					std::cout <<
					"Incorrect input restarting this step.\nPlease try to enter 1-5."; 
					search_menu();
					break;
	}
}

//probably this will be passed the equivalent of a relation on group 16s DMS
void Menu::comments_menu(std::string str_input) {

	int selection_input;
	//Comment System Dialogue
	//TODO std::cout << "[Commenting on "<< relation.title() <<"]\n\n";
	std::cout << "[]\n\n";
	std::cout << "1. Comment on post\n";
	std::cout << "2. Comment on comment\n\n";
	std::cout << "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
		case 1: comment_on_post(str_input); //relation
				break;
		case 2: comment_on_comment(str_input); //relation
				break;
		default: 
			 std::cout <<"Incorrect input restarting this step.\nPlease try to enter 1-3."; 
			 print_menu(); break;
	}

}

//probably this will be passed the equivalent of a relation on group 16s DMS
void Menu::comment_on_post(std::string str_input) {
	std::string name;
	std::string comment;
	std::cout << "* Enter name: ";
	std::getline(std::cin,name);
	std::cout << "\n* Enter comment: ";
	std::getline(std::cin,comment);
	//TODO do command on relation
	std::cout << "\nComment added.";
	post_manage_system(str_input);
}

//probably this will be passed the equivalent of a relation on group 16s DMS
void Menu::comment_on_comment(std::string str_input) {
	int ID;
	std::string name;
	std::string comment;
	std::cout << "* Enter ID: ";
	std::cin >> ID;
	std::cout << "* Enter name: ";
	std::getline(std::cin,name);
	std::cout << "\n* Enter comment: ";
	std::getline(std::cin,comment);
	// USE ID to select the correct comment to comment on.
	//TODO do command on relation
	std::cout << "\nComment added.";
	post_manage_system(str_input);
}

std::string Menu::make_post() {
	std::string post;
	std::cout << "New post: " << std::endl;
	std::getline(std::cin, post);
	return post;
}

std::string Menu::search_by_author(std::string str_input) {
	std::string author = str_input;
	int ID;
	std::cout << "[" << author << "'s Posts]\n";
	//Search database for posts
	//Store posts in a vector;
	//Select a post by ID, which is vector loc = ID - 1;
	//Then last on to be return to main menu
	std::cout << "* Enter ID: "; 
	std::cin >> ID;
	// if(ID == vector post.size()) GOTO print_menu()
	//return post_mangage_system(vector post.at(ID-1));
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


