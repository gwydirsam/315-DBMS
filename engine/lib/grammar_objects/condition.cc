#include "condition.h"

#include <boost/foreach.hpp>
#include <boost/fusion/adapted.hpp>

#include "../utility.h"

Condition::Condition(std::string op, SubCondition subcon1, SubCondition subcon2)
    : operation(op), subconditions() {
  errlog("Condition Constructor 1 Called.");
  std::string errstr = "Condition Constructor 1 args: " + op;
  errlog(errstr);
  std::cerr << "Constructor 1: " << subcon1 << std::endl;
  std::cerr << "Constructor 1: " << subcon2 << std::endl;
  subconditions.push_back(subcon1);
  subconditions.push_back(subcon2);
}

Condition::Condition(std::string op, SubCondition subcon1)
    : operation(op), subconditions() {
  errlog("Condition Constructor 1a Called.");
  std::string errstr = "Condition Constructor 1a args: " + op;
  errlog(errstr);
  std::cerr << "Constructor 1a: " << subcon1 << std::endl;
  subconditions.push_back(subcon1);
}

Condition::Condition(std::string op, std::vector<SubCondition> subcons)
    : operation(op), subconditions(subcons) {
  errlog("Condition Constructor 2 Called.");
  std::string errstr = "Condition Constructor 2 args: " + op;
  errlog(errstr);
  for (SubCondition subcon : subcons) {
    std::cerr << "Constructor 2: " << subcon << std::endl;
  }
}

Condition::Condition(std::vector<SubCondition> subcons)
    : operation(), subconditions(subcons) {
  errlog("Condition Constructor 3 Called.");
  for (SubCondition subcon : subconditions) {
    std::cerr << "Constructor 3: " << subcon << std::endl;
  }
}

Condition::Condition(std::string op) : operation(op), subconditions() {
  errlog("Condition Constructor 4 Called.");
  std::string errstr = "Condition Constructor 4 args: " + op;
  errlog(errstr);
}

Condition::Condition() : operation(), subconditions() {
  errlog("Condition Constructor 5 Called.");
}

std::ostream& operator<<(std::ostream& os, Condition const& ss) {
  os << "(" << ss.operation;
  os << " (";
  BOOST_FOREACH (SubCondition const& subcon, ss.subconditions) {
    os << subcon << " ";
  }
  os << ") ";
  os << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, SubCondition const& sc) {
  boost::apply_visitor(subcondition_printer(os), sc);
  return os;
}

void subcondition_printer::print(
    std::string const& operation,
    std::vector<SubCondition> const& subcons) const {
  _os << "(" << operation;
  _os << " (";
  BOOST_FOREACH (SubCondition const& subcon, subcons) {
    boost::apply_visitor(subcondition_printer(_os), subcon);
  }
  _os << ") ";
  _os << ")";
}
