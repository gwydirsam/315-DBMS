#include "utility.h"

#include <iostream>

void draw_line() {
  // Draw 80 line characters
  for (int i = 0; i < 80; ++i) {
    std::cout << "─";
  }
  std::cout << std::endl;
}

// color must be a valid color from utility.h
std::string color(std::string color, std::string text) {
  return (color + text + RESET);
}

//TODO: extend for more aguments
void errlog(std::string message) {
  std::cerr << color(RED, message) << std::endl;
}

