#ifndef COMMAND_H_
#define COMMAND_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <boost/variant.hpp>

// #include <boost/algorithm/string.hpp>
#include <boost/fusion/adapted.hpp>
// #include <boost/fusion/adapted/std_pair.hpp>
// #include <boost/fusion/include/std_pair.hpp>
// #include <boost/fusion/adapted/boost_tuple.hpp>
// #include <boost/fusion/include/boost_tuple.hpp>
// #include <boost/fusion/sequence/intrinsic/at_c.hpp>
// #include <boost/fusion/include/at_c.hpp>

// #include <boost/spirit/include/phoenix_core.hpp>
// #include <boost/spirit/include/phoenix_stl.hpp>
// #include <boost/spirit/include/phoenix_operator.hpp>
// #include <boost/spirit/include/phoenix_fusion.hpp>
// #include <boost/spirit/include/phoenix_object.hpp>

// #include <boost/spirit/include/qi.hpp>
// #include <boost/spirit/include/qi_as.hpp>

// #include <boost/foreach.hpp>

#include "relation.h"
#include "utility.h"

class Engine;

#include "condition.h"
#include "expression.h"

struct Command {
  Command(std::string c, std::string r_name)
      : command(c),
        relation_name(r_name),
        condition(),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c, std::string r_name,
          std::vector<std::string> t_att_list,
          std::vector<std::string> att_list)
      : command(c),
        relation_name(r_name),
        condition(),
        expression(),
        typed_attribute_list(t_att_list),
        attribute_list(att_list),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c, std::string r_name,
          std::vector<std::string> att_v_list, Condition cond)
      : command(c),
        relation_name(r_name),
        condition(cond),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(att_v_list),
        literal_list(){};
  Command(std::string c, std::string r_name, std::vector<std::string> lit_list)
      : command(c),
        relation_name(r_name),
        condition(),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(lit_list){};
  Command(std::string c, std::string r_name, Expression exp)
      : command(c),
        relation_name(r_name),
        condition(),
        expression(exp),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c, std::string r_name, Condition cond)
      : command(c),
        relation_name(r_name),
        condition(cond),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c, SubExpression exp)
      : command(c),
        relation_name(),
        condition(),
        expression(exp),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c)
      : command(c),
        relation_name(),
        condition(),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command()
      : command(),
        relation_name(),
        condition(),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};

  std::string command;  // open_cmd, close_cmd, write_cmd...
  std::string relation_name;

  Condition condition;    //  condition
  Expression expression;  // atomic_expression or expression
  std::vector<std::string> typed_attribute_list;  // typed-attribute-list
  std::vector<std::string> attribute_list;        // attribute-list
  std::vector<std::string> attribute_value_list;  // attribute-name = literal {
                                                  // , attribute-name = literal
                                                  // }
  // put in argument
  std::vector<std::string> literal_list;  // ( literal { , literal } )

  friend std::ostream& operator<<(std::ostream& os, Command const& ss);
};

BOOST_FUSION_ADAPT_STRUCT(
    Command,
    (std::string, command)(Condition, condition)(std::string, relation_name)(
        Expression, expression)(std::vector<std::string>, typed_attribute_list)(
        std::vector<std::string>,
        attribute_list)(std::vector<std::string>,
                        attribute_value_list)(std::vector<std::string>,
                                              literal_list))

void execute_command(Engine& db, std::string command, std::string relation_name,
                     std::vector<std::string> condition, Relation view,
                     std::vector<std::string> typed_attribute_list,
                     std::vector<std::string> attribute_list,
                     std::vector<std::string> attribute_value_list,
                     std::vector<std::string> literal_list);

#endif /* COMMAND_H_ */
