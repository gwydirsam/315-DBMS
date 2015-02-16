#include "utility.h"

#include <iostream>
#include <fstream>
#include <ctime>

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

const std::string currentDateTime() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}

// TODO: extend for more aguments
// ifdef DEBUG output message and log to file. Otherwise just log.
void errlog(std::string message) {
#ifdef DEBUG
  std::cerr << color(RED, message) << std::endl;
#endif
  std::ofstream logfile("logfile", std::ios::app);
  logfile << currentDateTime() << std::endl;
  logfile << "\t" << message << std::endl;
  logfile.close();
}

void endlog() {
  std::ofstream logfile("logfile", std::ios::app);
  logfile << "─────────────────────────────────────────────────────────────────"
             "───────────────" << std::endl;
  logfile.close();
}
