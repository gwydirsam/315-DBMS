// Convienience Functions
#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>

void draw_line(int n);
void draw_line();

namespace color {
const std::string RESET = "\033[0m";               /* Reset */
const std::string BLACK = "\033[30m";              /* Black */
const std::string RED = "\033[31m";                /* Red */
const std::string GREEN = "\033[32m";              /* Green */
const std::string YELLOW = "\033[33m";             /* Yellow */
const std::string BLUE = "\033[34m";               /* Blue */
const std::string MAGENTA = "\033[35m";            /* Magenta */
const std::string CYAN = "\033[36m";               /* Cyan */
const std::string WHITE = "\033[37m";              /* White */
const std::string BOLDBLACK = "\033[1m\033[30m";   /* Bold Black */
const std::string BOLDRED = "\033[1m\033[31m";     /* Bold Red */
const std::string BOLDGREEN = "\033[1m\033[32m";   /* Bold Green */
const std::string BOLDYELLOW = "\033[1m\033[33m";  /* Bold Yellow */
const std::string BOLDBLUE = "\033[1m\033[34m";    /* Bold Blue */
const std::string BOLDMAGENTA = "\033[1m\033[35m"; /* Bold Magenta */
const std::string BOLDCYAN = "\033[1m\033[36m";    /* Bold Cyan */
const std::string BOLDWHITE = "\033[1m\033[37m";   /* Bold White */
}

std::string setcolor(std::string color, std::string text);

const std::string currentDateTime();
void errlog(std::string message, bool show);
void errlog(std::string message);
void endlog();

#endif  // UTILITY_H_
