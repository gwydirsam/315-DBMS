#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>

#include "../lib/engine.h"

class Menu {
 public:
  Menu(Engine& db)
      : engine(db), current_menu_(&Menu::main_menu), current_menu_exec_(NULL) {}

  void menu_print();
  int menu_exec(std::string string_input);

  void main_menu();
  // if int is -1 quit program.
  int main_menu_exec(std::string string_input);

  void search_menu();
  int search_menu_exec(std::string string_input);

  void search_author_menu();
  int search_author_exec(std::string string_input);

 private:
  Engine& engine;
  void (Menu::*current_menu_)();
  int (Menu::*current_menu_exec_)(std::string string_input);
};

#endif  // MENU_H_
