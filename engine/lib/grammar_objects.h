#ifndef GRAMMAR_OBJECTS_H_
#define GRAMMAR_OBJECTS_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <boost/variant.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_as.hpp>

#include <boost/foreach.hpp>

#include "relation.h"
#include "engine.h"
#include "utility.h"

struct Condition;

typedef boost::variant<std::string, boost::recursive_wrapper<Condition>>
    SubCondition;

std::ostream& operator<<(std::ostream& os, SubCondition const& sc);

struct Condition {
  Condition(std::string op, SubCondition subcon1, SubCondition subcon2)
      : operation(op) {
    subconditions.push_back(subcon1);
    subconditions.push_back(subcon2);
  }
  Condition(std::string op, std::vector<SubCondition> subcons)
      : operation(op), subconditions(subcons){};
  Condition(std::vector<SubCondition> subcons)
      : operation(), subconditions(subcons){};
  Condition(std::string op) : operation(op), subconditions(){};
  Condition() : operation(), subconditions(){};

  std::string operation;
  std::vector<SubCondition> subconditions;

  friend std::ostream& operator<<(std::ostream& os, Condition const& ss) {
    os << "(" << ss.operation;
    os << " (";
    BOOST_FOREACH (SubCondition const& subcon, ss.subconditions) {
      os << subcon << " ";
    }
    os << ") ";
    os << ")";
    return os;
  }
};

BOOST_FUSION_ADAPT_STRUCT(Condition,
                          (std::string, operation)(std::vector<SubCondition>,
                                                   subconditions))

struct Expression;

typedef boost::variant<std::string, boost::recursive_wrapper<Expression>>
    SubExpression;

std::ostream& operator<<(std::ostream& os, SubExpression const& se);

struct Expression {
  Expression(SubExpression subexp) : query(), condition(), argument() {
    subexpressions.push_back(subexp);
  }
  Expression(SubExpression subexp1, SubExpression subexp2)
      : query(), condition(), argument() {
    subexpressions.push_back(subexp1);
    subexpressions.push_back(subexp2);
  }
  Expression(std::string q, SubExpression subexp1, SubExpression subexp2)
      : query(q), condition(), argument() {
    subexpressions.push_back(subexp1);
    subexpressions.push_back(subexp2);
  }
  Expression(std::string q, std::vector<std::string> args, SubExpression subexp)
      : query(q), condition(), argument(args) {
    subexpressions.push_back(subexp);
  }
  Expression(std::string q, Condition cond, SubExpression subexp)
      : query(q), condition(cond), argument() {
    subexpressions.push_back(subexp);
  }
  Expression(std::string q, std::vector<std::string> args,
             std::vector<SubExpression> subexps)
      : query(q), condition(), argument(args), subexpressions(subexps){};
  Expression(std::string q, std::vector<SubExpression> subexps)
      : query(q), condition(), argument(), subexpressions(subexps){};
  Expression(std::string q, std::vector<std::string> args)
      : query(q), condition(), argument(args), subexpressions(){};
  Expression(std::string q)
      : query(q), condition(), argument(), subexpressions(){};
  Expression(std::vector<SubExpression> subexps)
      : query(), condition(), argument(), subexpressions(subexps){};
  Expression(std::vector<std::string> args)
      : query(), condition(), argument(args), subexpressions(){};
  Expression() : query(), condition(), argument(), subexpressions(){};

  std::string query;                          // select, project, ...,
  Condition condition;                        // condition
  std::vector<std::string> argument;          // attribute_list
  std::vector<SubExpression> subexpressions;  // atomic_expression

  friend std::ostream& operator<<(std::ostream& os, Expression const& e) {
    os << "{";
    os << e.query;
    os << " ( ";
    for (std::string arg : e.argument) {
      os << arg << " ";
    }
    os << ") ";
    os << " ( ";
    os << e.condition << " ";
    os << ") ";
    os << "[ ";
    BOOST_FOREACH (SubExpression const& sexp, e.subexpressions) {
      os << sexp << " ";
    }
    os << "]";
    os << "}";
    return os;
  }
};

BOOST_FUSION_ADAPT_STRUCT(Expression,
                          (std::string, query)(Condition, condition)(
                              std::vector<std::string>,
                              argument)(std::vector<SubExpression>,
                                        subexpressions))

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

  friend std::ostream& operator<<(std::ostream& os, Command const& ss) {
    os << ss.command << "||";
    os << ss.relation_name;
    os << "( ";
    for (std::string entry : ss.typed_attribute_list) {
      os << entry << " ";
    }
    os << ") ";
    os << "( ";
    for (std::string entry : ss.attribute_list) {
      os << entry << " ";
    }
    os << ") ";
    os << "( ";
    for (std::string entry : ss.attribute_value_list) {
      os << entry << " ";
    }
    os << ") ";
    os << "( ";
    os << ss.condition;
    os << ") ";
    os << "( ";
    for (std::string entry : ss.literal_list) {
      os << entry << " ";
    }
    os << ") ";
    os << ss.expression;
    return os;
  }
};

BOOST_FUSION_ADAPT_STRUCT(
    Command,
    (std::string, command)(Condition, condition)(std::string, relation_name)(
        Expression, expression)(std::vector<std::string>, typed_attribute_list)(
        std::vector<std::string>,
        attribute_list)(std::vector<std::string>,
                        attribute_value_list)(std::vector<std::string>,
                                              literal_list))

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

BOOST_FUSION_ADAPT_STRUCT(Query,
                          (std::string, relation_name)(Expression, expression))

typedef boost::variant<Query, Command> Program;

struct subcondition_printer : boost::static_visitor<void> {
  subcondition_printer(std::ostream& os) : _os(os) {}
  std::ostream& _os;

  void operator()(std::string const& op) const { _os << op << " "; }

  void operator()(Condition const& c) const {
    print(c.operation, c.subconditions);
  }

  void print(std::string const& operation,
             std::vector<SubCondition> const& subcons) const {
    _os << "(" << operation;
    _os << " (";
    BOOST_FOREACH (SubCondition const& subcon, subcons) {
      boost::apply_visitor(subcondition_printer(_os), subcon);
    }
    _os << ") ";
    _os << ")";
  }
};

struct subexpression_printer : boost::static_visitor<void> {
  subexpression_printer(std::ostream& os) : _os(os) {}
  std::ostream& _os;

  void operator()(std::string const& q) const { _os << q << " "; }

  void operator()(Condition const& c) const { _os << c; }

  void operator()(Expression const& e) const {
    print(e.query, e.condition, e.argument, e.subexpressions);
  }

  void print(std::string const& query, Condition const& cond,
             std::vector<std::string> const& args,
             std::vector<SubExpression> const& subexps) const {
    _os << "{";
    _os << query;
    _os << " ( ";
    for (std::string arg : args) {
      _os << arg << " ";
    }
    _os << ") ";
    _os << " ( ";
    _os << cond;
    _os << ") ";
    _os << "[ ";
    BOOST_FOREACH (SubExpression const& sexp, subexps) {
      boost::apply_visitor(subexpression_printer(_os), sexp);
    }
    _os << "]";
    _os << "}";
  }
};

// struct subexpression_printer : boost::static_visitor<void> {
//   subexpression_printer(std::ostream& os) : _os(os) {}
//   std::ostream& _os;

//   void operator()(std::string const& q) const { _os << q << " "; }

//   void operator()(Condition const& c) const { _os << c; }

//   void operator()(Expression const& e) const {
//     print(e.query, e.condition, e.argument, e.subexpressions);
//   }

//   void print(std::string const& query, Condition const& cond,
//              std::vector<std::string> const& args,
//              std::vector<SubExpression> const& subexps) const {
//     _os << "{";
//     _os << "[ ";
//     BOOST_REVERSE_FOREACH (SubExpression const& sexp, subexps) {
//       boost::apply_visitor(subexpression_printer(_os), sexp);
//     }
//     _os << "]";
//     _os << query;
//     _os << " ( ";
//     for (std::string arg : args) {
//       _os << arg << " ";
//     }
//     _os << ") ";
//     _os << " ( ";
//     _os << cond;
//     _os << ") ";
//     _os << "}";
//   }
// };

struct subexpression_accessor : boost::static_visitor<void> {
  subexpression_accessor(std::vector<std::string>& args) : args_(args) {}
  std::vector<std::string>& args_;

  void operator()(std::string const& q) const {
    args_.emplace(std::end(args_), q);
  }

  void operator()(Condition const& c) const {
    args_.emplace(std::end(args_), c.operation);
    BOOST_FOREACH (SubCondition const& subcon, c.subconditions) {
      boost::apply_visitor(*this, subcon);
    }
  }

  // void operator()(std::vector<SubCondition> const& subcons) const {
  //   BOOST_FOREACH (SubCondition const& subcon, subcons) {
  //     boost::apply_visitor(*this, subcon);
  //   }
  // }

  void operator()(Expression const& e) const {
    // print(e.query, e.condition, e.argument, e.subexpressions);
    // std::string query;                          // select, project, ...,
    // Condition condition;                        // condition
    // std::vector<std::string> argument;          // attribute_list
    args_.emplace(std::end(args_), e.query);
    args_.emplace(std::end(args_), e.condition.operation);
    // std::vector<SubCondition> subconditions;
    BOOST_FOREACH (SubCondition const& subcon, e.condition.subconditions) {
      boost::apply_visitor(subexpression_accessor(args_), subcon);
    }
    for (std::string arg : e.argument) {
      args_.emplace(std::end(args_), arg);
    }
    BOOST_FOREACH (SubExpression const& sexp, e.subexpressions) {
      boost::apply_visitor(*this, sexp);
    }
  }

  void operator()(std::vector<SubExpression> const& subexps) const {
    BOOST_FOREACH (SubExpression const& sexp, subexps) {
      boost::apply_visitor(*this, sexp);
    }
  }
};

struct program_accessor : boost::static_visitor<> {
  program_accessor(std::vector<std::vector<std::string>>& args) : args_(args) {}
  std::vector<std::vector<std::string>>& args_;

  void operator()(Query const& q) const {
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

  void operator()(Command const& q) const {
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
};

void execute_program(Engine& db, const Program& p);

Relation execute_expression(Engine& db, std::string query,
                            std::vector<std::string> condition,
                            std::vector<std::string> args,
                            std::vector<Relation> subexps);

void execute_command(Engine& db, std::string command, std::string relation_name,
                     std::vector<std::string> condition, Relation view,
                     std::vector<std::string> typed_attribute_list,
                     std::vector<std::string> attribute_list,
                     std::vector<std::string> attribute_value_list,
                     std::vector<std::string> literal_list);

struct subexpression_execute : boost::static_visitor<Relation> {
  subexpression_execute(Engine& db) : db_(db) {}
  Engine& db_;

  Relation operator()(std::string const& q) const {
    // args_.emplace(std::begin(args_), q);
    return db_.find_relation_or_view(q);
  }

  Relation operator()(Condition const& c) const {
    // args_.emplace(std::begin(args_), c.operation);
    // BOOST_FOREACH (SubCondition const& subcon, c.subconditions) {
    //   boost::apply_visitor(*this, subcon);
    // }
    return Relation("empty");
  }

  Relation operator()(Expression const& e) const {
    // // print(e.query, e.condition, e.argument, e.subexpressions);
    // // std::string query;                          // select, project, ...,
    // // Condition condition;                        // condition
    // // std::vector<std::string> argument;          // attribute_list
    // args_.emplace(std::begin(args_), e.query);
    // args_.emplace(std::begin(args_), e.condition.operation);
    // // std::vector<SubCondition> subconditions;
    // BOOST_FOREACH (SubCondition const& subcon, e.condition.subconditions) {
    //   boost::apply_visitor(subexpression_exec(args_), subcon);
    // }
    // for (std::string arg : e.argument) {
    //   args_.emplace(std::begin(args_), arg);
    // }
    // BOOST_FOREACH (SubExpression const& sexp, e.subexpressions) {
    //   boost::apply_visitor(*this, sexp);
    // }
    std::vector<std::string> conds;
    BOOST_FOREACH (SubCondition const& subcon, e.condition.subconditions) {
      boost::apply_visitor(subexpression_accessor(conds), subcon);
    }
    std::vector<std::string> args;
    for (std::string arg : e.argument) {
      args.emplace(std::begin(args), arg);
    }

    std::vector<Relation> subexps;
    BOOST_FOREACH (SubExpression const& sexp, e.subexpressions) {
      Relation r = (boost::apply_visitor(subexpression_execute(db_), sexp));
      if (r.title() != "empty") {
        subexps.emplace_back(r);
      }
    }
    std::string errmsg = "SubExpression Execute: " + e.query + " ";
    for (std::string cond : conds) {
      errmsg += cond + " ";
    }
    errmsg += "|";
    for (std::string arg : args) {
      errmsg += arg + " ";
    }
    errmsg += "|";
    for (Relation r : subexps) {
      errmsg += r.title() + " ";
    }
    errmsg += "|";
    errlog(errmsg);

    return execute_expression(db_, e.query, conds, args, subexps);
  }

  // void operator()(std::vector<SubExpression> const& subexps) const {
  //   BOOST_FOREACH (SubExpression const& sexp, subexps) {
  //     boost::apply_visitor(*this, sexp);
  //   }
  // }
};

struct program_execute : boost::static_visitor<void> {
  program_execute(Engine& db) : db_(db) {}
  Engine& db_;

  void operator()(Query const& q) const {
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
      Relation subexprel =
          boost::apply_visitor(subexpression_execute(db_), sexp);
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

    // add relation to open views
    db_.addView(newrelation);
  }

  void operator()(Command const& q) const {
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
    std::vector<std::string> subconds;
    if (q.expression.condition.operation.size() > 0) {
      conds.emplace(std::begin(subconds), q.expression.condition.operation);
    }
    // std::vector<SubCondition> subconditions;
    BOOST_FOREACH (SubCondition const& subcon,
                   q.expression.condition.subconditions) {
      boost::apply_visitor(subexpression_accessor(subconds), subcon);
    }

    std::vector<Relation> subexpreturns;
    BOOST_FOREACH (SubExpression const& sexp, q.expression.subexpressions) {
      Relation subexprel =
          boost::apply_visitor(subexpression_execute(db_), sexp);
      std::string errmsg = "Program Execute: Sub Expression Result: ";
      errmsg += subexprel.title();
      errlog(errmsg);
      if (subexprel.title().size() > 0)
        subexpreturns.emplace(std::begin(subexpreturns), subexprel);
    }
    std::string errmsg = "Program Execute: Sub Expression Results: ";
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
      std::string errmsg = "Program Execute: Sub Expression Name: " + q.expression.query;
      errlog(errmsg);
      Relation newview = execute_expression(db_, q.expression.query, subconds,
                                   q.expression.argument, subexpreturns);
    }

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
};

#endif /* GRAMMAR_OBJECTS_H_ */
