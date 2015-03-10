#include "menu.h"

Menu::Menu() {
	parser.lex("CREATE TABLE posts (title VARCHAR(50), author VARCHAR(20), content VARCHAR(1000000), tags VARCHAR(100), comments  VARCHAR(1000000), date VARCHAR(20)) PRIMARY KEY (title, author);");
	works = parser.program();
	parser.lex("INSERT INTO posts VALUES FROM (\"Test1\", \"Kade\", \"Does the app work? Does view work?\", \"testing, app, view\", \"OH BOY IT WORKS\", \"(3/8/15)\");");
	works = parser.program();
	parser.lex("INSERT INTO posts VALUES FROM (\"The app\", \"Admin\", \"Testing edit content and tags\", \"testing, content\", \"Hello???\", \"(3/8/15)\");");
	works = parser.program();
	parser.lex("INSERT INTO posts VALUES FROM (\"Test2\", \"Kade\", \"renaming test\", \"testing, app, rename\", \"OH BOY IT WORKS\", \"(3/8/15)\");");
	works = parser.program();
	parser.lex("WRITE posts;");
	works = parser.program();
	parser.lex("CREATE TABLE result (title VARCHAR(50), author VARCHAR(20), content VARCHAR(1000000), tags VARCHAR(100), comments  VARCHAR(1000000), date VARCHAR(20)) PRIMARY KEY (title, author);");
	works = parser.program();
	}
void Menu::exit() {
	
	parser.lex("WRITE posts;");
	works = parser.program();
	parser.lex("EXIT;");
	works = parser.program();
	std::cout << "Goodbye.";
	
	//exit main menu
}

void Menu::print_menu() {
	int selection_input = 0;
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
			 std::cout <<"Incorrect input restarting this step.\nPlease try to enter 1-3.\n"; 
			 print_menu(); break;
	}
}

//search menu
void Menu::search_menu() {
	std::string str_input;
	std::string post;
	int selection_input = 0;
	//Search Menu Dialogue
	std::cout << "[Search Menu]\n\n";
	std::cout << "Search by:\n";
	std::cout << "1. Author\n"; 
	std::cout << "2. Title\n"; 
	std::cout << "3. Tag(s)\n";
	std::cout << "4. Date\n";
	std::cout << "5. Return to Main Menu\n\n";
	std::cout<< "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
			case 1: std::cout << "* Enter Author: "; 
					std::cin >> str_input;
					//std::getline(std::cin,str_input);
					post = search_by_author(str_input);
					post_manage_system(post);
					break;
			case 2: std::cout << "* Enter Title: "; 
					std::getline(std::cin,str_input);
					post = search_by_title(str_input);
					post_manage_system(post);
					break;
			case 3: std::cout << "* Enter Tag(s): "; 
					std::getline(std::cin,str_input);
					post = search_by_tags(str_input);
					post_manage_system(post);
					break;
			case 4: std::cout << "* Enter Date: "; 
					std::cin >> str_input;
					std::getline(std::cin,str_input);
					break;
			case 5: print_menu();
					break;
			default: 
					std::cout <<
					"Incorrect input restarting this step.\nPlease try to enter 1-5.\n"; 
					search_menu(); break;
	}
}

//probably this will be passed the equivalent of a relation on group 16s DMS
void Menu::edit_menu(std::string str_input) {
	int selection_input = 0;
	//Edit Menu Dialogue
	//TODO std::cout << "["<< relation.title() <<"'s Edit Menu]\n\n"; 
	std::cout << "[Edit Menu]\n\n";
	std::cout << "1. Author\n"; 
	std::cout << "2. Title\n"; 
	std::cout << "3. Tag(s)\n";
	std::cout << "4. Content\n";
	std::cout << "5. Comments\n";
	std::cout << "6. Return to Main Menu\n\n";
	std::cout<< "* Enter command: ";
	std::cin >> selection_input;
	std::cout << "\n";
	
	switch(selection_input) {
			
			case 1: edit_author(str_input); print_menu(); break;
			case 2: edit_title(str_input); print_menu(); break;
			case 3: edit_tags(str_input); print_menu(); break;
			case 4: edit_content(str_input); print_menu(); break;
			case 5: edit_comments(str_input); print_menu(); break;
			case 6: print_menu(); break;
			default: 
					std::cout <<
					"Incorrect input restarting this step.\nPlease try to enter 1-6.\n"; 
					edit_menu(str_input); break;
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
			case 1: view_post(str_input);
					post_manage_system(str_input);
			case 2: edit_menu(str_input); break;
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
					"Incorrect input restarting this step.\nPlease try to enter 1-5.\n"; 
					post_manage_system(str_input); break;
					
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
			 std::cout <<"Incorrect input restarting this step.\nPlease try to enter 1-2."; 
			 comments_menu(str_input);
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

void Menu::view_post(std::string str_input) {
	//TODO
	std::cout << "--------------------------------------------------------------------------------";
	parser.lex("");
	std::cout << "By: " << std::endl;
	std::cout << "Date: " << std::endl;
	std::cout << "Content: " << std::endl;
	std::cout << "Tags: " << std::endl;
	std::cout << "Comment: " << std::endl;
	std::cout << "--------------------------------------------------------------------------------";
}

std::string Menu::make_post() {
	std::string post;
	std::cout << "New post: " << std::endl;
	std::getline(std::cin, post);
	return post;
}

std::string Menu::search_by_author(std::string str_input) {
	std::string author = str_input;
	std::string query = "answer <- select (author == \"" + author +"\") posts;";
	parser.lex(query);
	works = parser.program();
	parser.lex("WRITE answer;");
	works = parser.program();
	parser.lex("SHOW answer;");
	works = parser.program();
	std::cout << "\n";
	parser.lex("INSERT INTO result VALUES FROM RELATION project (title, author, content, tags, comments, date) answer;");
	works = parser.program();
	parser.lex("WRITE result;");
	works = parser.program();
	std::cout << "[" << author << "'s Posts]\n";
	search_options("result.db");
	
	//Search database for posts
	//Store posts in a vector;
	//Select a post by ID, which is vector loc = ID - 1;
	//Then last on to be return to main menu

	// if(ID == vector post.size()) GOTO print_menu()
	//return post_mangage_system(vector post.at(ID-1));
	return "answer";
}

std::string Menu::search_by_title(std::string str_input) {
	std::string query = "answer <- select ( title == \"" + str_input +"\") posts;";
	std::cout << "" << std::endl;
	return str_input;
}

std::string Menu::search_by_tags(std::string str_input) {
	std::string table = "CREATE TABLE tags (tags VARCHAR(50), postid VARCHAR(50)) PRIMARY KEY (tags);";
	std::string query = "answer <- select ( tag == \"" + str_input +"\") posts;";
	std::cout << "" << std::endl;
	return str_input;
}

std::string Menu::search_by_dates(std::string str_input) {
	std::string query = "answer <- select ( date == \"" + str_input +"\") posts;";
	std::cout << "" << std::endl;
	return str_input;
}

void Menu::edit_author(std::string str_input) {	
	std::string author;
	//TODO std::cout << "[Editing"<< relation.title() <<"'s Author]\n\n";
	//TODO std::cout << "Current Author: "<< relation.author() <<"\n\n";
	std::cout << "* Enter new Author: ";
	//std::getline(std::cin, author);
	std::cin >> author;
	std::string query = "UPDATE posts SET author == \"" + author + "\" WHERE (author == \"Kade\");";
	/*std::string query = "UPDATE posts SET author == \"" + author + "\" WHERE (author == author " + 
	str_input + " && title == title " + str_input + " %% tags == tags " +
	str_input + " && date == date" + str_input + ");";*/
	parser.lex(query);
	works = parser.program();
	parser.lex("SHOW posts;");
	works = parser.program();
	//TODO store new author
}

void Menu::edit_title(std::string str_input) {	
	std::string title;
	//TODO std::cout << "[Editing"<< relation.title() <<"'s Title]\n\n";
	//TODO std::cout << "Current Title: " << relation.title() << "\n\n";
	std::cout << "* Enter new Title: ";
	std::getline(std::cin, title);
	std::string query = "posts <- rename ("+title+") (select ( title == \"" + str_input +"\") posts;";
	parser.lex(query);
	works = parser.program();
	parser.lex("SHOW posts;");
	works = parser.program();
	//TODO store new title
}

void Menu::edit_tags(std::string str_input) {	
	//TODO std::cout << "[Editing"<< relation.title() <<"'s Tag(s)]\n\n";
	//IDK how to impletement at all?
	//Are they each an element of a vector?
}

void Menu::edit_content(std::string str_input) {	
	std::string content;
	//TODO std::cout << "[Editing"<< relation.title() <<"'s Content]\n\n";
	//TODO std::cout << "Current Content: "<< relation.content() <<"\n\n";
	std::cout << "* Enter new Content: ";
	std::getline(std::cin, content);
	std::string query = "posts <- rename ("+content+") (select ( content == \"" + str_input +"\") posts;";
	//TODO store new content
}

void Menu::edit_comments(std::string str_input) {	
	std::string comment;
	//TODO std::cout << "[Editing"<< relation.title() <<"'s Comments]\n\n";
	//TODO std::cout << "Current Comments: "<< relation.comments() <<"\n\n";
	//TODO print out comments
	std::cout << "* Enter new Comment: ";
	std::getline(std::cin, comment);
	std::string query = "posts <- rename ("+comment+") (select ( comment == \"" + str_input +"\") posts;";
	// TODO store new comment
}

void Menu::search_options(std::string str_input) {

Table* t = parser.database->get_table(str_input);

  if (t != NULL) {
	  int i;
	  for (i = 0; i < t->get_items().size(); ++i) {
		vector <string> entry = t->get_items()[i];
		std::cout << i+1 << ". " << entry[0] << " " << entry[5] << std::endl;
		}
		std::cout << i+1 << ". Return to Main Menu\n";
		
		int ID;
		std::cout << "* Enter ID: "; 
		std::cin >> ID;
		if(ID == i+1) {
			print_menu();
		}
		/*else {
			int g;
			for (g = 0; g < parser.database->dbms.size(); ++g) {
				if (parser.database->dbms.at(g).get_name().compare(t.getname())==0) {
						i = g;
				}
			}
			Table* choice = t->get_items()[ID-1];
			parser.database->dbms.at(g) = choice;
		}*/
	}
   else {
    cout << "The requested file " << str_input << " is not a relation.\n";
  }

}


