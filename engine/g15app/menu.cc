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
        source_rel_ = &engine.find_relation("posts");
        if (new_post() == 0) {
          errlog("New Post: Success");
          print_current_item();
        }
        current_menu_ = &Menu::main_menu;
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
        current_menu_ = &Menu::search_tags_menu;
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
  std::string sqlproj = "PROJECT (id, title, author, date, content) ";
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
  std::string sqlproj = "PROJECT (id, title, author, date, content) ";
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

void Menu::search_tags_menu() {
  std::cout << "[Search Tags]" << std::endl;
  draw_line(15);
  std::cout << "Search for Tag(s):" << std::endl;
  // set current menu function pointer
  errlog("Menu: Setting menu executer to search_tags_exec");
  current_menu_exec_ = &Menu::search_tags_exec;
}

int Menu::search_tags_exec(std::string string_input) {
  std::string errstr = "Search Tags: Input:" + string_input;
  errlog(errstr);
  std::string sqlquery = "search-tags <- ";
  std::string sqlproj = "PROJECT (postid) ";
  std::string sqlsel = "( SELECT ( tagid == \"" + string_input + "\" ) tagmap)";
  std::string sqlprog = sqlquery + sqlproj + sqlsel + ";";

  if (engine.execSQL(sqlprog) != -1) {
    std::vector<int> postrows;
    for (int i = 0; i < engine.find_relation_or_view("search-tags").num_rows();
         ++i) {
      int post_row;
      try {
        post_row = boost::lexical_cast<int>(
            engine.find_relation_or_view("search-tags").get_row(i)[0]);
      } catch (const boost::bad_lexical_cast &) {
        errlog("Menu: Bad Lexical Cast");
        errlog("Could not interpret input as an integer.", true);
      }
      postrows.push_back(post_row);
    }
    std::vector<Column<std::string>> stcolumns;
    for (Column<std::string> col : engine.find_relation("posts").columns()) {
      stcolumns.push_back(
          Column<std::string>(col.title(), col.type(), col.primary_key()));
    }
    Relation search_tags_posts("search-tags-posts", stcolumns);
    for (int i = 0; i < postrows.size(); ++i) {
      search_tags_posts.append_row(
          engine.find_relation("posts").get_row(postrows[i]));
    }
    engine.addView(search_tags_posts);
    Relation &search_rel = engine.find_relation_or_view("search-tags-posts");
    Relation &source_rel = engine.find_relation_or_view("posts");
    source_rel_ = &source_rel;
    current_col_ = 2;
    current_rel_ = &search_rel;
    current_menu_ = &Menu::select_item_menu;
    return 0;
  } else {
    std::string errmsg = "Search Tags: " + string_input + " Failed!";
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
  std::string sqlproj = "PROJECT (id, title, author, date, content) ";
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
    // delete content
    row.erase(row.end() - 1);

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
      engine.dropView(current_rel_->title());
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
  if (current_rel_->title() != "comments") {
    std::cout << "["
              << current_rel_->get_row(
                     current_item_)[current_rel_->find_column_index("title")]
              << "]" << std::endl;
    draw_line(
        (current_rel_->get_row(
             current_item_)[current_rel_->find_column_index("title")]).size() +
        2);
  } else {
    std::cout << "[Comment]" << std::endl;
    draw_line(9);
  }
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
          current_menu_ = &Menu::operate_item_menu;
        }
        errlog("Menu: Setting menu to operate_item_menu");
        current_menu_ = &Menu::operate_item_menu;
        break;
      case 3:
        errlog("Main Menu: Got 3");
        errlog("Menu: Setting menu to delete_menu");
        if (delete_current_item() == 0) {
          errlog("Delete: Succeeded");
          if (engine.find_view_index(current_rel_->title()) != -1) {
            engine.dropView(current_rel_->title());
            current_rel_ = NULL;
            current_item_ = 0;
          }
        }
        current_menu_ = &Menu::main_menu;
        break;
      case 4:
        errlog("Main Menu: Got 4");
        errlog("Menu: Setting menu to comment_menu");
        errlog("Menu: Setting menu to operate_item_menu");
        current_menu_ = &Menu::comment_item_menu;
        break;
      case 5:
        errlog("Main Menu: Got 5");
        errlog("Menu: Setting menu to main_menu");
        errlog("Menu: Setting menu to operate_item_menu");
        if (engine.find_view_index(current_rel_->title()) != -1) {
          engine.dropView(current_rel_->title());
        }
        current_rel_ = NULL;
        current_item_ = 0;
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

void Menu::comment_item_menu() {
  std::cout << "["
            << current_rel_->get_row(
                   current_item_)[current_rel_->find_column_index("title")]
            << "]" << std::endl;
  draw_line(
      (current_rel_->get_row(
           current_item_)[current_rel_->find_column_index("title")]).size() +
      2);
  std::cout << "1) Comment on Post" << std::endl;
  std::cout << "2) Comment on Comment" << std::endl;
  std::cout << "3) Return to Main Menu" << std::endl;

  // set current menu function pointer
  errlog("Menu: Setting menu executer to operate_item_exec");
  current_menu_exec_ = &Menu::comment_item_exec;
}

int Menu::comment_item_exec(std::string string_input) {
  try {
    int input = boost::lexical_cast<int>(string_input);
    switch (input) {
      case 1:
        errlog("Search Menu: Got 1");
        errlog("Menu: Setting menu to operate_item_menu");
        current_item_ = boost::lexical_cast<int>((current_rel_->get_row(
            current_item_)[current_rel_->find_column_index("id")]));
        current_rel_ = &engine.find_relation_or_view("comments");
        source_rel_ = &engine.find_relation_or_view("posts");
        if (comment_current_item() == 0) {
          errlog("Comment: Succeeded");
          source_rel_ = &engine.find_relation_or_view("posts");
        }
        current_menu_ = &Menu::operate_item_menu;
        break;
      case 2:
        errlog("Main Menu: Got 2");
        errlog("Menu: Setting menu to operate_item_menu");
        current_item_ = boost::lexical_cast<int>((current_rel_->get_row(
            current_item_)[current_rel_->find_column_index("id")]));
        current_rel_ = &engine.find_relation_or_view("comments");
        errlog("Menu: Setting menu to operate_item_menu");
        current_menu_ = &Menu::select_item_menu;
        break;
      case 3:
        errlog("Main Menu: Got 3");
        errlog("Menu: Setting menu to main_menu");
        errlog("Menu: Setting menu to operate_item_menu");
        current_rel_ = NULL;
        current_item_ = 0;
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
  if (current_rel_->title() != "comments") {
    std::cout << std::string("")
              << current_rel_->get_row(
                     current_item_)[current_rel_->find_column_index("title")]
              << std::endl;
  }
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
            << current_rel_->get_row(
                   current_item_)[current_rel_->find_column_index("content")]
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

  std::string temp_file = "/tmp/g15tempfile";

  boost::filesystem::path temppath(boost::filesystem::absolute(temp_file));
  if (boost::filesystem::remove(temppath)) {
    errlog("Edit: Old Temp File Deleted");
  } else {
    errlog("Edit: Creating New Temp File");
  }
  std::fstream tfileout(temp_file, std::ios::out);
  tfileout << current_rel_->get_row(
                  current_item_)[current_rel_->find_column_index("title")]
           << "\n";
  tfileout << current_rel_->get_row(
                  current_item_)[current_rel_->find_column_index("author")]
           << "\n";
  tfileout << current_rel_->get_row(
                  current_item_)[current_rel_->find_column_index("date")]
           << "\n";
  tfileout << current_rel_->get_row(
                  current_item_)[current_rel_->find_column_index("content")]
           << "\n";
  tfileout.close();

  // char *my_args[4];
  // pid_t pid;

  // my_args[0] = "vim";
  // my_args[1] = "-f";
  // my_args[2] = temp_file;
  // my_args[3] = NULL;

  errlog("Edit: Forking off editor");
  std::string editorstring;
  if (std::strcmp(pEditor, "vim") == 0) {
    editorstring = std::string(pEditor) + " -f " + temp_file;
  } else {
    editorstring = std::string(pEditor) + temp_file;
  }
  system(editorstring.c_str());

  // read in edit
  std::string title;
  std::string author;
  std::string date;
  std::string content;
  std::fstream tfilein(temp_file, std::ios::in);
  getline(tfilein, title, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  getline(tfilein, author, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  getline(tfilein, date, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  std::string line;
  while (getline(tfilein, line)) {
    content.append(line + "\n");
  }
  tfilein.close();

  int old_id;
  try {
    old_id = boost::lexical_cast<int>(current_rel_->get_row(current_item_)[0]);
  } catch (const boost::bad_lexical_cast &) {
    errlog("Menu: Bad Lexical Cast");
    errlog("Could not interpret input as an integer.", true);
  }
  int new_id = (source_rel_->num_rows());
  std::vector<std::string> editrow{std::to_string(new_id), title, author, date,
                                   content};

  std::vector<std::string> editsourcerow{
      std::to_string(new_id), title, author, date, content,
      (source_rel_->get_row(old_id)[source_rel_->num_cols() - 1])};

  source_rel_->drop_row(old_id);
  source_rel_->append_row(editsourcerow);

  current_rel_->drop_row(current_item_);
  current_rel_->append_row(editrow);
  current_item_ = (current_rel_->num_rows() - 1);

  errlog("End of editor program");
  return 0;
}

int Menu::delete_current_item() {
  int old_id;
  try {
    old_id = boost::lexical_cast<int>(current_rel_->get_row(current_item_)[0]);
  } catch (const boost::bad_lexical_cast &) {
    errlog("Menu: Bad Lexical Cast");
    errlog("Could not interpret input as an integer.", true);
  }

  for (int i = 0; i < source_rel_->num_rows(); ++i) {
    int src_id;
    try {
      src_id = boost::lexical_cast<int>(source_rel_->get_row(i)[0]);
    } catch (const boost::bad_lexical_cast &) {
      errlog("Menu: Bad Lexical Cast");
      errlog("Could not interpret input as an integer.", true);
    }
    if (old_id == src_id) {
      source_rel_->drop_row(i);
    }
  }
  return 0;
}

int Menu::new_post() {
  char *pEditor;
  pEditor = getenv("EDITOR");
  std::string errstr = "Edit: Editor varible: " + std::string(pEditor);
  errlog(errstr);

  std::string temp_file = "/tmp/g15tempfile";

  boost::filesystem::path temppath(boost::filesystem::absolute(temp_file));
  if (boost::filesystem::remove(temppath)) {
    errlog("Edit: Old Temp File Deleted");
  } else {
    errlog("Edit: Creating New Temp File");
  }
  std::fstream tfileout(temp_file, std::ios::out);
  tfileout << "title on this line"
           << "\n";
  tfileout << "author on this line"
           << "\n";
  tfileout << "date on this line (YYYYMMDD)"
           << "\n";
  tfileout << "enable comments on this line (1 or 0)"
           << "\n";
  tfileout << "content is anything on this line or below"
           << "\n";
  tfileout.close();

  errlog("Edit: Forking off editor");
  std::string editorstring;
  if (std::strcmp(pEditor, "vim") == 0) {
    editorstring = std::string(pEditor) + " -f " + temp_file;
  } else {
    editorstring = std::string(pEditor) + temp_file;
  }
  system(editorstring.c_str());

  // read in edit
  std::string title;
  std::string author;
  std::string date;
  std::string comments;
  std::string content;
  std::fstream tfilein(temp_file, std::ios::in);
  getline(tfilein, title, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  getline(tfilein, author, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  getline(tfilein, date, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  getline(tfilein, comments, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  std::string line;
  while (getline(tfilein, line)) {
    content.append(line + "\n");
  }
  tfilein.close();

  int new_id = (source_rel_->num_rows());
  std::vector<std::string> editsourcerow{std::to_string(new_id), title, author,
                                         date, content, comments};

  source_rel_->append_row(editsourcerow);

  current_rel_ = &engine.find_relation("posts");
  current_item_ = (current_rel_->num_rows() - 1);

  errlog("End of editor program");
  return 0;
}

int Menu::comment_current_item() {
  char *pEditor;
  pEditor = getenv("EDITOR");
  std::string errstr = "Edit: Editor varible: " + std::string(pEditor);
  errlog(errstr);

  std::string temp_file = "/tmp/g15tempfile";

  boost::filesystem::path temppath(boost::filesystem::absolute(temp_file));
  if (boost::filesystem::remove(temppath)) {
    errlog("Edit: Old Temp File Deleted");
  } else {
    errlog("Edit: Creating New Temp File");
  }
  std::fstream tfileout(temp_file, std::ios::out);
  tfileout << "author on this line"
           << "\n";
  tfileout << "date on this line (YYYYMMDD)"
           << "\n";
  tfileout << "content is anything on this line or below"
           << "\n";
  tfileout.close();

  errlog("Edit: Forking off editor");
  std::string editorstring;
  if (std::strcmp(pEditor, "vim") == 0) {
    editorstring = std::string(pEditor) + " -f " + temp_file;
  } else {
    editorstring = std::string(pEditor) + temp_file;
  }
  system(editorstring.c_str());

  // read in edit
  std::string author;
  std::string date;
  std::string content;
  std::fstream tfilein(temp_file, std::ios::in);
  getline(tfilein, author, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  getline(tfilein, date, '\n');
  if (tfilein.peek() == '\n') {
    tfilein.ignore(1);
    errlog("Edit: ignored newline");
  }
  std::string line;
  while (getline(tfilein, line)) {
    content.append(line + "\n");
  }
  tfilein.close();

  int new_id = (current_rel_->num_rows());
  std::vector<std::string> editsourcerow{
      std::to_string(new_id), source_rel_->get_row(current_item_)[0], author,
      date, content, source_rel_->get_row(current_item_)[0]};

  current_rel_->append_row(editsourcerow);

  current_rel_ = &engine.find_relation("comments");
  current_item_ = (current_rel_->num_rows() - 1);

  errlog("End of editor program");
  return 0;
}
