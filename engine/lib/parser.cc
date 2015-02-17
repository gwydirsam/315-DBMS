#include "parser.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <boost/algorithm/string.hpp>

// Receives command and returns a string of that command.
std::string Parser::receive_command(std::string command) {}

// Translate a command to Engine command string.
std::string Parser::translate_command(std::string command) {}

// Sends the engine command to be executed or excutes it here.
void Parser::exec_engine_command(std::string command) {}

// Breaks a string into a vector of strings where each string in the vector is
// one word (space seperated) from the original strings
std::vector<std::string> Parser::tokenize(std::string query) {
  std::vector<std::string> tokens;
  boost::split(tokens, query, boost::is_any_of("\t "));
  return tokens;
}
