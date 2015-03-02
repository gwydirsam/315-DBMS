// CSCE 315-503
// parser.h

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <functional>

#include "utility.h"
#include "relation.h"

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

  // Sends the engine command to be executed or executes it here.
  int execSQL(std::string input_string);

  // Breaks a string into a vector of strings where each string in the vector is
  // one word (space seperated) from the original strings
  std::vector<std::string> tokenize(std::string query);
  
  Relation& find_relation(std::string TableName);
  
  std::vector<Relation>::iterator find_view(std::string TableName);
  
  int find_view_index(std::string TableName);

 private:
 std::vector<Relation> views_;
};

#endif  // PARSER_H_
