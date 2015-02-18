while(true)
{

//maybe another class for methods?
//switch statement to select methods/output

}

void main_menu() {
	int input;
	cout << "[Main Menu]\n\n";
	cout << "1. Make a new post.\n";
	cout << "2. Search for a post.\n";
	cout << "3. Exit.\n\n";
	cout << "* Enter command: ";
	cin >> input;
	cout << "\n";
	switch(input){
	case 1: make_post(); break;
	case 2: search_menu(); break;
	case 3: exit();
	default: cout <<"Incorrect input exiting program."; exit(); break;
	}
}

void search_menu() {
	//this may need to be changed to display categories of database?
	//also call database function or something
	int num_input;
	string str_input
	cout << "[Search Menu]\n\nSearch by:\n1. Author\n2. Title\n3. Tag(s)\n";
	cout << "4. Date\n5. Return to Main Menu.\n\n* Enter command: ";
	cin >> num_input;
	cout << "\n";
	switch(num_input){
	case 1: cout << "* Enter Author: "; 
	cin >> str_input;
	search_by_author(str_input);
	break;
	case 2: cout << "* Enter Title: "; 
	cin >> str_input;
	search_by_title(str_input);
	break;
	case 3: cout << "* Enter Title: "; 
	cin >> str_input;
	search_by_title(str_input);
	break;
	case 4: break;
	case 5: main_menu(); break;
	default: cout <<"Incorrect input exiting program."; exit(); break;
	}
}