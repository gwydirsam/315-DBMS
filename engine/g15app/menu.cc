#include "menu.h"

#include <iostream>
#include <string>
#include <functional>

#include <boost/lexical_cast.hpp>

#include <readline/readline.h>
#include <readline/history.h>

#include "../lib/utility.h"
#include "../lib/engine.h"

void Menu::menu_print() { (this->*current_menu_)(); }

int Menu::menu_exec(std::string string_input) {
  return (this->*current_menu_exec_)(string_input);
}

void Menu::main_menu() {
  // print first menu
  std::cout << "[Main Menu]" << std::endl;
  draw_line(11);
  std::cout << "1) Post to Blog" << std::endl;
  std::cout << "2) Search" << std::endl;
  std::cout << "3) Exit" << std::endl;
  // set current menu function pointer
  errlog("Menu: Setting menu executer to main_menu_exec");
  current_menu_exec_ = &Menu::main_menu_exec;
}

// if int is -1 quit program.
int Menu::main_menu_exec(std::string string_input) {
  try {
    int input = boost::lexical_cast<int>(string_input);
    switch (input) {
      case 1: {
        errlog("Main Menu: Got 1");
        errlog("Menu: Setting menu to new_post_menu");
        // current_menu_ = &Menu::new_post_menu;
        break;
      }
      case 2: {
        errlog("Main Menu: Got 2");
        errlog("Menu: Setting menu to search_menu");
        current_menu_ = &Menu::search_menu;
        break;
      }
      case 3: {
        errlog("Main Menu: Got 3");
        std::string sqlprog = "EXIT;";
        engine.execSQL(sqlprog);
        return -1;
        break;
      }
      default: {
        errlog("Main Menu: Got bad input");
        current_menu_ = &Menu::main_menu;
        break;
      }
    }
  } catch (const boost::bad_lexical_cast &) {
    errlog("Menu: Bad Lexical Cast");
    errlog("Could not interpret input as an integer.", true);
  }
  return 0;
}

void Menu::search_menu() {
  // print first menu
  std::cout << "[Search Menu]" << std::endl;
  draw_line(13);
  std::cout << "Search by:" << std::endl;
  std::cout << "1) Author" << std::endl;
  std::cout << "2) Title" << std::endl;
  std::cout << "3) Tag(s)" << std::endl;
  std::cout << "4) Date" << std::endl;
  std::cout << "5) Return to Main Menu" << std::endl;
  // set current menu function pointer
  errlog("Menu: Setting menu executer to search_menu_exec");
  current_menu_exec_ = &Menu::search_menu_exec;
}

int Menu::search_menu_exec(std::string string_input) {
  try {
    int input = boost::lexical_cast<int>(string_input);
    switch (input) {
      case 1:
        errlog("Search Menu: Got 1");
        errlog("Menu: Setting menu to search_author_menu");
        current_menu_ = &Menu::search_author_menu;
        break;
      case 2:
        errlog("Main Menu: Got 2");
        errlog("Menu: Setting menu to search_title_menu");
        // current_menu_ = &Menu::search_title_menu;
        break;
      case 3:
        errlog("Main Menu: Got 3");
        errlog("Menu: Setting menu to search_tags_menu");
        // current_menu_ = &Menu::search_tags_menu;
        break;
      case 4:
        errlog("Main Menu: Got 4");
        errlog("Menu: Setting menu to search_date_menu");
        // current_menu_ = &Menu::search_date_menu;
        break;
      case 5:
        errlog("Main Menu: Got 5");
        errlog("Menu: Setting menu to main_menu");
        current_menu_ = &Menu::main_menu;
        break;
      default:
        errlog("Main Menu: Got bad input");
        current_menu_ = &Menu::search_menu;
        break;
    }
    return 0;
  } catch (const boost::bad_lexical_cast &) {
    errlog("Menu: Bad Lexical Cast");
    errlog("Could not interpret input as an integer.", true);
  }
  return 0;
}

void Menu::search_author_menu() {
  std::cout << "[Search Author]" << std::endl;
  draw_line(15);
  std::cout << "Search for Name:" << std::endl;
  // set current menu function pointer
  errlog("Menu: Setting menu executer to search_author_exec");
  current_menu_exec_ = &Menu::search_author_exec;
}

int Menu::search_author_exec(std::string string_input) {
  std::string errstr = "Search Author Menu: Input:" + string_input;
  errlog(errstr);
  std::string sqlquery = "search-author <- ";
  std::string sqlproj = "PROJECT (id, title, author, date) ";
  std::string sqlsel = "( SELECT ( author == \"" + string_input + "\" ) posts)";
  std::string sqlprog = sqlquery + sqlproj + sqlsel + ";";
  if (engine.execSQL(sqlprog) != -1) {
    return 0;
  } else {
    std::string errmsg = "Search Author: " + string_input + " Failed!";
    errlog(errmsg, true);

    errlog("Menu: Setting menu to main_menu");
    current_menu_ = &Menu::search_menu;
    return 0;
  }
}
