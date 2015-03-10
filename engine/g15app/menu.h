#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include "../include/Group16DBMS/Parser.h"

class Menu {
public:
	//Global:
	Parser parser;
	std::string str_input;
	int m_selection_input;
	int s_selection_input;
	int search_input;
	bool works;
	//Constructor:
	Menu();
	//Destructor:
	//Getters:
	//Setters:
	//Functions:
	void exit();
	void print_menu();
	void search_menu();
	void edit_menu(std::string str_input);
	void post_manage_system(std::string str_input);
	void comments_menu(std::string str_input);
	
	void comment_on_post(std::string str_input);
	void comment_on_comment(std::string str_input);
	void view_post(std::string str_input);
	std::string make_post();
	
	std::string search_by_author(std::string str_input);
	std::string search_by_title(std::string str_input);
	std::string search_by_tags(std::string str_input);
	std::string search_by_dates(std::string str_input);
	
	void edit_author(std::string str_input);
	void edit_title(std::string str_input);
	void edit_tags(std::string str_input);
	void edit_content(std::string str_input);
	void edit_comments(std::string str_input);
	void search_options(std::string str_input);
};
#endif  // MENU_H_
