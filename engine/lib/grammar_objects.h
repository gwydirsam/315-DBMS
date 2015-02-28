#ifndef GRAMMAR_OBJECTS_H_
#define GRAMMAR_OBJECTS_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Command {
  Command(std::string c, std::vector<std::string> a)
      : command(c), argument(a){};
  Command(std::string c) : command(c), argument(){};
  Command(std::vector<std::string> a) : command(), argument(a){};
  Command() : command(), argument(){};

  std::string command;
  std::vector<std::string> argument;

  friend std::ostream& operator<<(std::ostream& os, Command const& ss) {
    os << ss.command << "||";
    for (std::string arg : ss.argument) {
      os << arg << "|";
    }
    return os;
  }
};

struct Query {
  Query(std::string rname, std::vector<std::string> expr)
      : relation_name(rname), expression(expr){};
  Query(std::vector<std::string> expr) : relation_name(), expression(expr){};
  Query(std::string rname) : relation_name(rname), expression(){};
  Query() : relation_name(), expression(){};

  std::string relation_name;
  std::vector<std::string> expression;

  friend std::ostream& operator<<(std::ostream& os, Query const& ss) {
    os << ss.relation_name << "||";
    for (std::string expr : ss.expression) {
      os << expr << "|";
    }
    return os;
  }
};

struct Program {
  Program(Query q) : query(q), isquery(true) {};
  Program(Command c) : command(c), isquery(false) {};
  Program() : query(), command(), isquery(false) {};

  Query query;
  Command command;
  bool isquery;  // if true, query, if false, command

  friend std::ostream& operator<<(std::ostream& os, Program const& ss) {
    if (ss.isquery) {
      return os << ss.query;
    } else {
      return os << ss.command;
    }
  }
};

#endif /* GRAMMAR_OBJECTS_H_ */
