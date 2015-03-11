#include "menu.h"

#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <functional>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include <readline/readline.h>
#include <readline/history.h>

#include "../lib/engine.h"
#include "../lib/column.h"
#include "../lib/relation.h"
#include "../lib/utility.h"
#include "../lib/grammar.h"

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
        current_menu_ = &Menu::search_title_menu;
        break;
      case 3:
        errlog("Main Menu: Got 3");
        errlog("Menu: Setting menu to search_tags_menu");
        // current_menu_ = &Menu::search_tags_menu;
        break;
      case 4:
        errlog("Main Menu: Got 4");
        errlog("Menu: Setting menu to search_date_menu");
        current_menu_ = &Menu::search_date_menu;
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
  // drop later
  // engine.dropTable(search_rel.title());

  if (engine.execSQL(sqlprog) != -1) {
    Relation &search_rel = engine.find_relation_or_view("search-author");
    Relation &source_rel = engine.find_relation_or_view("posts");
    source_rel_ = &source_rel;
    current_col_ = 2;
    current_rel_ = &search_rel;
    current_menu_ = &Menu::select_item_menu;

    return 0;
  } else {
    std::string errmsg = "Search Author: " + string_input + " Failed!";
    errlog(errmsg, true);

    errlog("Menu: Setting menu to main_menu");
    current_menu_ = &Menu::search_menu;
    return 0;
  }
}

void Menu::search_title_menu() {
  std::cout << "[Search Title]" << std::endl;
  draw_line(15);
  std::cout << "Search for Title:" << std::endl;
  // set current menu function pointer
  errlog("Menu: Setting menu executer to search_title_exec");
  current_menu_exec_ = &Menu::search_title_exec;
}

int Menu::search_title_exec(std::string string_input) {
  std::string errstr = "Search Title Menu: Input:" + string_input;
  errlog(errstr);
  std::string sqlquery = "search-title <- ";
  std::string sqlproj = "PROJECT (id, title, author, date) ";
  std::string sqlsel = "( SELECT ( title == \"" + string_input + "\" ) posts)";
  std::string sqlprog = sqlquery + sqlproj + sqlsel + ";";
  // drop later
  // engine.dropTable(search_rel.title());

  if (engine.execSQL(sqlprog) != -1) {
    Relation &search_rel = engine.find_relation_or_view("search-title");
    Relation &source_rel = engine.find_relation_or_view("posts");
    source_rel_ = &source_rel;
    current_col_ = 1;
    current_rel_ = &search_rel;
    current_menu_ = &Menu::select_item_menu;
    return 0;
  } else {
    std::string errmsg = "Search Title: " + string_input + " Failed!";
    errlog(errmsg, true);

    errlog("Menu: Setting menu to main_menu");
    current_menu_ = &Menu::search_menu;
    return 0;
  }
}

void Menu::search_date_menu() {
  std::cout << "[Search Date]" << std::endl;
  draw_line(15);
  std::cout << "Search for Date:" << std::endl;
  // set current menu function pointer
  errlog("Menu: Setting menu executer to search_date_exec");
  current_menu_exec_ = &Menu::search_date_exec;
}

int Menu::search_date_exec(std::string string_input) {
  std::string errstr = "Search Date Menu: Input:" + string_input;
  errlog(errstr);
  std::string sqlquery = "search-date <- ";
  std::string sqlproj = "PROJECT (id, title, author, date) ";
  std::string sqlsel = "( SELECT ( date == \"" + string_input + "\" ) posts)";
  std::string sqlprog = sqlquery + sqlproj + sqlsel + ";";
  // drop later
  // engine.dropTable(search_rel.title());

  if (engine.execSQL(sqlprog) != -1) {
    Relation &search_rel = engine.find_relation_or_view("search-date");
    Relation &source_rel = engine.find_relation_or_view("posts");
    source_rel_ = &source_rel;
    current_col_ = 3;
    current_rel_ = &search_rel;
    current_menu_ = &Menu::select_item_menu;

    return 0;
  } else {
    std::string errmsg = "Search Date: " + string_input + " Failed!";
    errlog(errmsg, true);

    errlog("Menu: Setting menu to main_menu");
    current_menu_ = &Menu::search_menu;
    return 0;
  }
}

void Menu::select_item_menu() {
  std::cout << "[Select Item]" << std::endl;
  draw_line(13);
  for (int i = 0; i < current_rel_->num_rows(); ++i) {
    std::vector<std::string> row = current_rel_->get_row(i);
    // delete id
    row.erase(row.begin());

    std::cout << i << ")\t";
    for (std::string entry : row) {
      std::cout << entry << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << "-1) Return to Main Menu" << std::endl;
  std::cout << "Select Item:" << std::endl;
  // set current menu function pointer
  errlog("Menu: Setting menu executer to search_author_exec");
  current_menu_exec_ = &Menu::select_item_exec;
}

int Menu::select_item_exec(std::string string_input) {
  try {
    int input = boost::lexical_cast<int>(string_input);
    if (input == -1) {
      current_menu_ = &Menu::main_menu;
    } else if (input <= current_rel_->num_rows()) {
      current_item_ = input;
      current_menu_ = &Menu::operate_item_menu;
    } else {
      errlog("Invalid Input", false);
    }
    return 0;
  } catch (const boost::bad_lexical_cast &) {
    errlog("Menu: Bad Lexical Cast");
    errlog("Could not interpret input as an integer.", true);
  }
  return 0;
}

void Menu::operate_item_menu() {
  std::cout << "["
            << current_rel_->get_row(
                   current_item_)[current_rel_->find_column_index("title")]
            << "]" << std::endl;
  draw_line(
      (current_rel_->get_row(
           current_item_)[current_rel_->find_column_index("title")]).size() +
      2);
  std::cout << "1) View" << std::endl;
  std::cout << "2) Edit" << std::endl;
  std::cout << "3) Delete" << std::endl;
  std::cout << "4) Comment" << std::endl;
  std::cout << "5) Return to Main Menu" << std::endl;

  // set current menu function pointer
  errlog("Menu: Setting menu executer to operat_item_exec");
  current_menu_exec_ = &Menu::operate_item_exec;
}

int Menu::operate_item_exec(std::string string_input) {
  try {
    int input = boost::lexical_cast<int>(string_input);
    switch (input) {
      case 1:
        errlog("Search Menu: Got 1");
        errlog("Menu: Setting menu to operate_item_menu");
        print_current_item();
        current_menu_ = &Menu::operate_item_menu;
        break;
      case 2:
        errlog("Main Menu: Got 2");
        if (edit_current_item() == 0) {
          errlog("Edit: Succeeded, file in /tmp/g15tempfile");
        }
        errlog("Menu: Setting menu to operate_item_menu");
        current_menu_ = &Menu::operate_item_menu;
        break;
      case 3:
        errlog("Main Menu: Got 3");
        errlog("Menu: Setting menu to delete_menu");
        errlog("Menu: Setting menu to operate_item_menu");
        current_menu_ = &Menu::operate_item_menu;
        break;
      case 4:
        errlog("Main Menu: Got 4");
        errlog("Menu: Setting menu to comment_menu");
        errlog("Menu: Setting menu to operate_item_menu");
        current_menu_ = &Menu::operate_item_menu;
        break;
      case 5:
        errlog("Main Menu: Got 5");
        errlog("Menu: Setting menu to main_menu");
        errlog("Menu: Setting menu to operate_item_menu");
        current_menu_ = &Menu::main_menu;
        break;
      default:
        errlog("Main Menu: Got bad input");
        errlog("Menu: Setting menu to search_menu");
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

void Menu::print_current_item() {
  // std::cout << "App CLI Arguments" << std::endl;
  // draw_line(76);
  // std::cout << std::left << std::setw(20) << std::setfill(' ') << "< (file)";
  // std::cout << std::left << std::setw(20) << std::setfill(' ')
  //           << "Run app script and quit (example in engine/share)" <<
  //           std::endl;
  std::cout << std::endl;
  std::cout << std::string("")
            << current_rel_->get_row(
                   current_item_)[current_rel_->find_column_index("title")]
            << std::endl;
  std::cout << std::string("")
            << current_rel_->get_row(
                   current_item_)[current_rel_->find_column_index("author")]
            << std::endl;
  std::cout << std::string("")
            << current_rel_->get_row(
                   current_item_)[current_rel_->find_column_index("date")]
            << std::endl;
  // TODO: Tags
  draw_line();
  std::cout << std::endl;
  std::cout << std::string("")
            << source_rel_->get_row(current_rel_->find_column_index(
                   "id"))[source_rel_->find_column_index("content")]
            << std::endl;
  std::cout << std::endl;
  draw_line();
  std::cout << std::endl;
}

int Menu::edit_current_item() {
  char *pEditor;
  pEditor = getenv("EDITOR");
  std::string errstr = "Edit: Editor varible: " + std::string(pEditor);
  errlog(errstr);

  char *temp_file = "/tmp/g15tempfile";

  boost::filesystem::path temppath(boost::filesystem::absolute(temp_file));
  if (boost::filesystem::remove(temppath)) {
    errlog("Edit: Old Temp File Deleted");
  } else {
    errlog("Edit: Creating New Temp File");
    std::fstream tfile(temp_file, std::ios::out);
    tfile << current_rel_->get_row(
                 current_item_)[current_rel_->find_column_index("title")]
          << std::endl;
    tfile << current_rel_->get_row(
                 current_item_)[current_rel_->find_column_index("author")]
          << std::endl;
    tfile << current_rel_->get_row(
                 current_item_)[current_rel_->find_column_index("date")]
          << std::endl;
    tfile << source_rel_->get_row(current_rel_->find_column_index(
                 "id"))[source_rel_->find_column_index("content")] << std::endl;
    tfile << std::endl;
    tfile.close();
  }

  char *my_args[4];
  pid_t pid;

  my_args[0] = "vim";
  my_args[1] = "-f";
  my_args[2] = temp_file;
  my_args[3] = NULL;

  errlog("Edit: Forking off editor");

  switch ((pid = fork())) {
    case -1:
      /* Fork() has failed */
      perror("fork");
      break;
    case 0:
      /* This is processed by the child */
      execvp("vim", my_args);
      errlog("If this prints, execv() must have failed");
      exit(EXIT_FAILURE);
      break;
    default:
      /* This is processed by the parent */
      errlog("This is a message from the parent");
      break;
  }

  // read in edit

  errlog("End of parent program");
  return 0;
}
