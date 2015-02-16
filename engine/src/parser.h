#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <functional>

#include "engine.h"
#include "sqltypes.h"
#include "relation.h"
#include "utility.h"

class Parser {
 public:
  // Constructors
  // Default Constructor
  Parser() { errlog("Parser: Creating New Parser"); }
  ~Parser() {};
  // Receives command and returns a string of that command.
  std::string receive_command(std::string command);
  // Translate a command to Engine command string.
  std::string translate_command(std::string command);
  // Sends the engine command to be executed or excutes it here.
  void exec_engine_command(std:: string command);
  
  
 }