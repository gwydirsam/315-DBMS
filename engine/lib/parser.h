// CSCE 315-503
// parser.h

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>

class Parser {
 public:
  // Constructors
  // Default Constructor
  Parser(){};

  // Destructors
  // Default Destructor
  ~Parser(){};

  // Receives command and returns a string of that command.
  std::string receive_command(std::string command);

  // Translate a command to Engine command string.
  std::string translate_command(std::string command);

  // Sends the engine command to be executed or excutes it here.
  void exec_engine_command(std::string command);

  // Breaks a string into a vector of strings where each string in the vector is
  // one word (space seperated) from the original strings
  std::vector<std::string> tokenize(std::string query);

 private:
};

#endif  // PARSER_H_
