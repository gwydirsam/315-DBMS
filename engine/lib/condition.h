#ifndef CONDITION_H_
#define CONDITION_H_

#include <vector>
#include <string>
#include <iostream>

#include <boost/fusion/adapted.hpp>
#include <boost/variant.hpp>

struct Condition;

typedef boost::variant<std::string, boost::recursive_wrapper<Condition>>
    SubCondition;

std::ostream& operator<<(std::ostream& os, SubCondition const& sc);

struct Condition {
  Condition(std::string op, SubCondition subcon1, SubCondition subcon2);
  Condition(std::string op, SubCondition subcon1);
  Condition(std::string op, std::vector<SubCondition> subcons);
  Condition(std::vector<SubCondition> subcons);
  Condition(std::string op);
  Condition();

  std::string operation;
  std::vector<SubCondition> subconditions;

  friend std::ostream& operator<<(std::ostream& os, Condition const& ss);
};

BOOST_FUSION_ADAPT_STRUCT(Condition,
                          (std::string, operation)(std::vector<SubCondition>,
                                                   subconditions))

struct subcondition_printer : boost::static_visitor<void> {
  subcondition_printer(std::ostream& os) : _os(os) {}
  std::ostream& _os;

  void operator()(std::string const& op) const { _os << op << " "; }

  void operator()(Condition const& c) const {
    print(c.operation, c.subconditions);
  }

  void print(std::string const& operation,
             std::vector<SubCondition> const& subcons) const;
};

#endif /* CONDITION_H_ */
