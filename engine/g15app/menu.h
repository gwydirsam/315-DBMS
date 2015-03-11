#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>

#include "../lib/engine.h"
#include "../lib/column.h"
#include "../lib/relation.h"
#include "../lib/utility.h"
#include "../lib/grammar.h"

class Menu {
 public:
  Menu(Engine& db)
      : engine(db),
        current_rel_(NULL),
        source_rel_(NULL),
        current_item_(0),
        current_col_(0),
        current_menu_(&Menu::main_menu),
        current_menu_exec_(NULL) {}

  void menu_print();
  int menu_exec(std::string string_input);

  void main_menu();
  // if int is -1 quit program.
  int main_menu_exec(std::string string_input);

  void search_menu();
  int search_menu_exec(std::string string_input);

  void search_author_menu();
  int search_author_exec(std::string string_input);

  void search_title_menu();
  int search_title_exec(std::string string_input);

  // void search_tags_menu();
  // int search_tags_exec(std::string string_input);

  void search_date_menu();
  int search_date_exec(std::string string_input);

  void select_item_menu();
  int select_item_exec(std::string string_input);

  void operate_item_menu();
  int operate_item_exec(std::string string_input);

  void print_current_item();
  int edit_current_item();

 private:
  Engine& engine;
  int current_col_;
  int current_item_;
  Relation* current_rel_;
  Relation* source_rel_;
  void (Menu::*current_menu_)();
  int (Menu::*current_menu_exec_)(std::string string_input);
};

#endif  // MENU_H_
