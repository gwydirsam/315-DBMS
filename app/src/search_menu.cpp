
#include <search_menu.h>

search_menu:: string search_menu() {
	
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
	
	switch(num_input) {
			case 1: cout << "* Enter Author: "; 
					cin >> str_input;
					search_by_author(str_input);
					break;
			case 2: cout << "* Enter Title: "; 
					cin >> str_input;
					search_by_title(str_input);
					break;
			case 3: cout << "* Enter Tag(s): "; 
					cin >> str_input;
					search_by_tag(str_input);
					break;
			case 4: cout << "* Enter Date: "; 
					cin >> str_input;
					search_by_dates(str_input);
					break;
			case 5: main_menu();
					break;
			default: 
					cout << "Incorrect input exiting program."; 
					exit(); 
					break;
	}
}

search_menu:: search_by_author(str_input) {
	//author names
}

search_menu:: search_by_title(str_input) {
	//title names
}

search_menu:: search_by_tags(str_input) {
	//tag names
}

search_menu:: search_by_dates(str_input) {
	//dates
}

search_menu:: return_to_menu() {
	//return to menu
}