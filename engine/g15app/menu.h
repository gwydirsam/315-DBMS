#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "../lib/utility.h"
#include "../lib/engine.h"

class Menu {
 public:
  void main_menu(void) {
    // print first menu
    std::cout << "[Main Menu]" << std::endl;
    draw_line(11);
    std::cout << "1) Post to Blog" << std::endl;
    std::cout << "2) Search" << std::endl;
    std::cout << "3) Exit" << std::endl;
  }
  void main_menu(std::string string_input) {
    try {
      int input = boost::lexical_cast<int>(string_input);
      switch (input) {
        case 1:
          errlog("Main Menu: Got 1");
          break;
        case 2:
          errlog("Main Menu: Got 2");
          break;
        case 3:
          errlog("Main Menu: Got 3");
          break;
        default:
          errlog("Main Menu: Got bad input");
          break;
      }
    } catch (const boost::bad_lexical_cast &) {
      errlog("Main Menu: Bad Lexical Cast");
      errlog("Could not interpret input as an integer.", true);
    }
  }
};

#endif  // MENU_H_
