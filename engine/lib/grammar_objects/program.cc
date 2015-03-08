#include "program.h"

#include <boost/fusion/adapted.hpp>

#include "../engine.h"
#include "condition.h"
#include "expression.h"
#include "../relation.h"
#include "../utility.h"

program_accessor::program_accessor(std::vector<std::vector<std::string>>& args) : args_(args) {};
program_execute::program_execute(Engine& db) : db_(db){};

void execute_program(Engine& db, const Program& p) {
  boost::apply_visitor(program_execute(db), p);
}

void program_accessor::operator()(Query const& q) const {
  std::vector<std::string> relationarg;
  relationarg.emplace(std::end(relationarg), q.relation_name);
  std::vector<std::string> queryarg;
  queryarg.emplace(std::end(queryarg), q.expression.query);
  // Condition condition;                        // condition
  // std::string operation;
  std::vector<std::string> condarg;
  condarg.emplace(std::end(condarg), q.expression.condition.operation);
  // std::vector<SubCondition> subconditions;
  BOOST_FOREACH (SubCondition const& subcon,
                 q.expression.condition.subconditions) {
    boost::apply_visitor(subexpression_accessor(condarg), subcon);
  }
  // std::vector<std::string> argument;          // attribute_list
  std::vector<std::string> subarg;
  for (std::string arg : q.expression.argument) {
    subarg.emplace(std::end(subarg), arg);
  }
  // std::vector<SubExpression> subexpressions;  // atomic_expression
  std::vector<std::string> exparg;
  BOOST_FOREACH (SubExpression const& sexp, q.expression.subexpressions) {
    boost::apply_visitor(subexpression_accessor(exparg), sexp);
  }
  args_.emplace(std::begin(args_), relationarg);
  args_.emplace(std::begin(args_), queryarg);
  args_.emplace(std::begin(args_), condarg);
  args_.emplace(std::begin(args_), subarg);
  args_.emplace(std::begin(args_), exparg);
}

void program_accessor::operator()(Command const& q) const {
  std::vector<std::string> comarg;
  // std::string command;  // open_cmd, close_cmd, write_cmd...
  comarg.emplace(std::end(comarg), q.command);
  // std::string relation_name;
  std::vector<std::string> relationarg;
  relationarg.emplace(std::end(relationarg), q.relation_name);

  // Expression expression;  // atomic_expression or expression
  std::vector<std::string> exparg;
  exparg.emplace(std::end(exparg), q.expression.query);
  BOOST_FOREACH (SubExpression const& sexp, q.expression.subexpressions) {
    boost::apply_visitor(subexpression_accessor(exparg), sexp);
  }

  // std::vector<std::string> typed_attribute_list;  // typed-attribute-list
  std::vector<std::string> talarg;
  for (std::string arg : q.typed_attribute_list) {
    talarg.emplace(std::end(talarg), arg);
  }
  // std::vector<std::string> attribute_list;        // attribute-list
  std::vector<std::string> alarg;
  for (std::string arg : q.attribute_list) {
    alarg.emplace(std::end(alarg), arg);
  }
  // std::vector<std::string> attribute_value_list;  // attribute-name =
  std::vector<std::string> avlarg;
  for (std::string arg : q.attribute_value_list) {
    avlarg.emplace(std::end(avlarg), arg);
  }
  // std::vector<std::string> literal_list;  // ( literal { , literal } )
  std::vector<std::string> larg;
  for (std::string arg : q.literal_list) {
    larg.emplace(std::end(larg), arg);
  }
  // Condition condition;
  std::vector<std::string> condarg;
  condarg.emplace(std::end(condarg), q.condition.operation);
  // std::vector<SubCondition> subconditions;
  BOOST_FOREACH (SubCondition const& subcon, q.condition.subconditions) {
    boost::apply_visitor(subexpression_accessor(condarg), subcon);
  }
  args_.emplace(std::begin(args_), comarg);
  args_.emplace(std::begin(args_), relationarg);
  args_.emplace(std::begin(args_), exparg);
  args_.emplace(std::begin(args_), talarg);
  args_.emplace(std::begin(args_), alarg);
  args_.emplace(std::begin(args_), avlarg);
  args_.emplace(std::begin(args_), larg);
  args_.emplace(std::begin(args_), condarg);
}

void program_execute::operator()(Query const& q) const {
  // Condition condition;                        // condition
  // std::string operation;
  std::vector<std::string> conds;
  conds.emplace(std::begin(conds), q.expression.condition.operation);
  // std::vector<SubCondition> subconditions;
  BOOST_FOREACH (SubCondition const& subcon,
                 q.expression.condition.subconditions) {
    boost::apply_visitor(subexpression_accessor(conds), subcon);
  }

  // std::vector<SubExpression> subexpressions;  // atomic_expression
  std::vector<Relation> subexpreturns;
  BOOST_FOREACH (SubExpression const& sexp, q.expression.subexpressions) {
    Relation subexprel = boost::apply_visitor(subexpression_execute(db_), sexp);
    std::string errmsg = "Program Execute: Sub Expression Result: ";
    errmsg += subexprel.title();
    errlog(errmsg);
    subexpreturns.emplace(std::begin(subexpreturns), subexprel);
  }
  std::string errmsg = "Program Execute: Sub Expression Results: ";
  for (Relation r : subexpreturns) {
    errmsg += r.title() + " ";
  }
  errlog(errmsg);

  // execute top expression
  Relation newrelation = execute_expression(
      db_, q.expression.query, conds, q.expression.argument, subexpreturns);

  // set the name
  newrelation.title(q.relation_name);

  errmsg =
      "Grammar Objects: Program Execute: Query: New View: " + q.relation_name;
  errlog(errmsg);
  // add relation to open views
  db_.addView(newrelation);
}

void program_execute::operator()(Command const& q) const {
  // // std::string command;  // open_cmd, close_cmd, write_cmd...
  // args_.emplace(std::begin(args_), q.command);
  // // std::string relation_name;
  // args_.emplace(std::begin(args_), q.relation_name);

  // // Expression expression;  // atomic_expression or expression
  // args_.emplace(std::begin(args_), q.expression.query);
  // BOOST_FOREACH (SubExpression const& sexp, q.expression.subexpressions) {
  //   boost::apply_visitor(subexpression_exec(args_), sexp);
  // }

  // // std::vector<std::string> typed_attribute_list;  //
  // typed-attribute-list
  // for (std::string arg : q.typed_attribute_list) {
  //   args_.emplace(std::begin(args_), arg);
  // }
  // // std::vector<std::string> attribute_list;        // attribute-list
  // for (std::string arg : q.attribute_list) {
  //   args_.emplace(std::begin(args_), arg);
  // }
  // // std::vector<std::string> attribute_value_list;  // attribute-name =
  // for (std::string arg : q.attribute_value_list) {
  //   args_.emplace(std::begin(args_), arg);
  // }
  // // std::vector<std::string> literal_list;  // ( literal { , literal } )
  // for (std::string arg : q.literal_list) {
  //   args_.emplace(std::begin(args_), arg);
  // }
  // // Condition condition;  // not used until Condition is implented,
  // currently
  // args_.emplace(std::begin(args_), q.condition.operation);
  // // std::vector<SubCondition> subconditions;
  // BOOST_FOREACH (SubCondition const& subcon, q.condition.subconditions) {
  //   boost::apply_visitor(subexpression_exec(args_), subcon);
  // }

  // std::string command;  // open_cmd, close_cmd, write_cmd...
  // std::string relation_name;

  // Condition condition;    //  condition
  std::vector<std::string> conds;
  conds.emplace(std::begin(conds), q.condition.operation);
  // std::vector<SubCondition> subconditions;
  BOOST_FOREACH (SubCondition const& subcon, q.condition.subconditions) {
    boost::apply_visitor(subexpression_accessor(conds), subcon);
  }
  std::string errmsg = "Program Execute: Conditions Results: ";
  for (std::string c : conds) {
    errmsg += c + " ";
  }
  errlog(errmsg);

  // std::vector<SubCondition> subconditions;
  std::vector<std::string> subconds;
  if (q.expression.condition.operation.size() > 0) {
    conds.emplace(std::begin(subconds), q.expression.condition.operation);
  }
  BOOST_FOREACH (SubCondition const& subcon,
                 q.expression.condition.subconditions) {
    boost::apply_visitor(subexpression_accessor(subconds), subcon);
  }

  std::vector<Relation> subexpreturns;
  BOOST_FOREACH (SubExpression const& sexp, q.expression.subexpressions) {
    Relation subexprel = boost::apply_visitor(subexpression_execute(db_), sexp);
    std::string errmsg = "Program Execute: Sub Expression Result: ";
    errmsg += subexprel.title();
    errlog(errmsg);
    if (subexprel.title().size() > 0)
      subexpreturns.emplace(std::begin(subexpreturns), subexprel);
  }
  errmsg = "Program Execute: Sub Expression Results: ";
  for (Relation r : subexpreturns) {
    errmsg += r.title() + " ";
  }
  errlog(errmsg);

  // Expression expression;  // atomic_expression or expression
  Relation newview("");
  if (subexpreturns.size() == 1) {
    newview = subexpreturns[0];
  }
  if (q.expression.query.size() > 0) {
    std::string errmsg =
        "Program Execute: Sub Expression Name: " + q.expression.query;
    errlog(errmsg);
    newview = execute_expression(db_, q.expression.query, subconds,
                                 q.expression.argument, subexpreturns);
  }
  errmsg = "Program Execute: Expression Result: " + newview.title();
  errlog(errmsg);

  // std::vector<std::string> typed_attribute_list;  // typed-attribute-list
  // q.typed_attribute_list
  // std::vector<std::string> attribute_list;        // attribute-list
  // q.attribute_list
  // std::vector<std::string> attribute_value_list;  // attribute-name =
  // q.attribute_value_list
  // std::vector<std::string> literal_list;  // ( literal { , literal } )
  // q.literal_list
  execute_command(db_, q.command, q.relation_name, conds, newview,
                  q.typed_attribute_list, q.attribute_list,
                  q.attribute_value_list, q.literal_list);
}
