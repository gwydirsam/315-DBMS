#ifndef GRAMMAR_OBJECTS_H_
#define GRAMMAR_OBJECTS_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Argument {
  Argument(std::string rname, std::vector<std::string> args)
      : relation_name(rname), entries(args){};
  Argument(std::vector<std::string> args) : relation_name(), entries(args){};
  Argument(std::string rname) : relation_name(rname), entries(){};
  Argument() : relation_name(), entries(){};

  std::string relation_name;
  std::vector<std::string> entries;

  friend std::ostream& operator<<(std::ostream& os, Argument const& ss) {
    os << "[" << ss.relation_name;
    if (ss.entries.size() > 0) os << "||";
    for (std::string e : ss.entries) {
      os << e << "|";
    }
    os << "]";
    return os;
  }
};

struct Command {
  Command(std::string c, Argument a) : command(c), argument(a){};
  Command(std::string c) : command(c), argument(){};
  Command(Argument a) : command(), argument(a){};
  Command() : command(), argument(){};

  std::string command;
  Argument argument;

  friend std::ostream& operator<<(std::ostream& os, Command const& ss) {
    os << ss.command << "||";
    os << ss.argument;
    return os;
  }
};

struct Expression {
  Expression(std::string rname, std::vector<std::string> expr)
      : relation_name(rname), expression(expr){};
  Expression(std::vector<std::string> expr)
      : relation_name(), expression(expr){};
  Expression(std::string rname) : relation_name(rname), expression(){};
  Expression() : relation_name(), expression(){};

  std::string relation_name;
  std::vector<std::string> expression;

  friend std::ostream& operator<<(std::ostream& os, Expression const& ss) {
    os << "[" << ss.relation_name;
    if (ss.expression.size() > 0) os << "||";
    for (std::string e : ss.expression) {
      os << e << "|";
    }
    os << "]";
    return os;
  }
};

struct Query {
  Query(std::string rname, Expression expr)
      : relation_name(rname), expression(expr){};
  Query(Expression expr) : relation_name(), expression(expr){};
  Query(std::string rname) : relation_name(rname), expression(){};
  Query() : relation_name(), expression(){};

  std::string relation_name;
  Expression expression;

  friend std::ostream& operator<<(std::ostream& os, Query const& ss) {
    os << ss.relation_name << "<-";
    os << ss.expression;
    return os;
  }
};

struct Program {
  Program(Query q) : query(q), isquery(true){};
  Program(Command c) : command(c), isquery(false){};
  Program() : query(), command(), isquery(false){};

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
