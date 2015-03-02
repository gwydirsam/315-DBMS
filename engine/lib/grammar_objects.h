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

// struct Condition;

// typedef boost::variant<
//   std::string,
//   boost::recursive_wrapper<Condition>,
//   boost::recursive_wrapper<Condition>
//   > SubCondition;

// struct Condition {
//   Condition(std::string op, SubCondition l, SubCondition r)
//     : operation(op), lhs(l), rhs(r){};
//   Condition(std::string op) : operation(op), lhs(), rhs(){};
//   Condition() : operation(), lhs(), rhs(){};

//   std::string operation;
//   SubCondition lhs;
//   SubCondition rhs;

//   friend std::ostream& operator<<(std::ostream& os, Condition const& ss) {
//     os << "(" << ss.lhs << ss.operation << ss.rhs << ")";
//     return os;
//   }
// };

// BOOST_FUSION_ADAPT_STRUCT(Condition,
//                           (std::string, operation)
//                           (SubCondition, lhs)
//                           (SubCondition, rhs))

// struct Argument {
//   Argument(std::string rname, std::vector<std::string> args)
//       : relation_name(rname), entries(args){};
//   Argument(std::vector<std::string> args) : relation_name(), entries(args){};
//   Argument(std::string rname) : relation_name(rname), entries(){};
//   Argument() : relation_name(), entries(){};

//   std::string relation_name;
//   std::vector<std::string> entries;

//   friend std::ostream& operator<<(std::ostream& os, Argument const& ss) {
//     os << "[" << ss.relation_name;
//     if (ss.entries.size() > 0) os << "||";
//     for (std::string e : ss.entries) {
//       os << e << "|";
//     }
//     os << "]";
//     return os;
//   }
// };

// BOOST_FUSION_ADAPT_STRUCT(Argument,
//                           (std::string,
//                           relation_name)(std::vector<std::string>,
//                                                        entries))

// struct Expression;

// typedef boost::variant<
//   std::string,
//   boost::recursive_wrapper<Expression>
//   > SubExpression;

// struct Expression {
//   Expression(std::string q, std::vector<SubExpression> subexps)
//     : query(q), subexpressions(subexps){};
//   Expression(std::string q) : query(q), subexpressions(){};
//   Expression() : query(), subexpressions(){};

//   std::string query;
//   std::vector<SubExpression> subexpressions;

//   friend std::ostream& operator<<(std::ostream& os, Expression const& ss) {
//     os << "(" << ss.query << " ";
//     for (SubExpression subexp : ss.subexpressions) {
//       os << subexp << " ";
//     }
//     return os;
//   }
// };

// BOOST_FUSION_ADAPT_STRUCT(Expression,
//                           (std::string, query)
//                           (std::vector<SubCondition>, subexpressions))

// struct Command {
//   Command(std::string c, Argument a) : command(c), argument(a){};
//   Command(std::string c) : command(c), argument(){};
//   Command(Argument a) : command(), argument(a){};
//   Command() : command(), argument(){};

//   std::string command;
//   std::string relation_name;
//   Expression atomic_expression;
//   std::vector<std::string> typed_attribute_list;
//   std::vector<std::string> attribute_list;
//   std::vector<std::pair<std::string,std::string> > update_list;
//   std::vector<std::string> literal_list;
//   Condition condition;
//   Expression expression;
//   Argument argument;

//   friend std::ostream& operator<<(std::ostream& os, Command const& ss) {
//     os << ss.command << "||";
//     os << ss.argument;
//     return os;
//   }
// };

// BOOST_FUSION_ADAPT_STRUCT(Command, (std::string, command)(Argument,
// argument))

// struct Query {
//   Query(std::string rname, Expression expr)
//       : relation_name(rname), expression(expr){};
//   Query(Expression expr) : relation_name(), expression(expr){};
//   Query(std::string rname) : relation_name(rname), expression(){};
//   Query() : relation_name(), expression(){};

//   std::string relation_name;
//   Expression expression;

//   friend std::ostream& operator<<(std::ostream& os, Query const& ss) {
//     os << ss.relation_name << "<-";
//     os << ss.expression;
//     return os;
//   }
// };

// BOOST_FUSION_ADAPT_STRUCT(Query,
//                           (std::string, relation_name)(Expression,
//                           expression))

// typedef boost::variant<Query, Command> Program;

// struct Program {
//   Program(Query q) : query_name(q), isquery(true){};
//   Program(Command c) : command(c), isquery(false){};
//   Program() : query_name(), command(), isquery(false){};

//   Query query_name;
//   Command command;
//   bool isquery;  // if true, query_name, if false, command

//   friend std::ostream& operator<<(std::ostream& os, Program const& ss) {
//     if (ss.isquery) {
//       return os << ss.query_name;
//     } else {
//       return os << ss.command;
//     }
//   }
// };

// BOOST_FUSION_ADAPT_STRUCT(Program, (Query, query_name)(Command, command))

//-------
// struct Expression {
//   Expression(std::string rname, std::vector<std::string> expr)
//       : expression_name(rname), expression(expr){};
//   Expression(std::vector<std::string> expr)
//       : expression_name(), expression(expr){};
//   Expression(std::string rname) : expression_name(rname), expression(){};
//   Expression() : expression_name(), expression(){};

//   std::string expression_name;  // select, project, atomic_expression(would
//   put
//                                 // relation_name name here or keep recursing)
//   std::vector<std::string> expression;

//   friend std::ostream& operator<<(std::ostream& os, Expression const& ss) {
//     os << "{" << ss.expression_name;
//     if (ss.expression.size() > 0) os << "||";
//     for (std::string e : ss.expression) {
//       os << e << "|";
//     }
//     os << "}";
//     return os;
//   }
// };

// BOOST_FUSION_ADAPT_STRUCT(Expression,
//                           (std::string,
//                           expression_name)(std::vector<std::string>,
//                                                        expression))

// struct Condition;

// typedef boost::variant<std::string, std::vector<std::string>,
//                        boost::recursive_wrapper<Expression>> SubCondition;

struct Expression;

typedef boost::variant<std::string, std::vector<std::string>,
                       boost::recursive_wrapper<Expression>> SubExpression;

struct subexpression_printer;
struct expression_printer;
std::ostream& operator<<(std::ostream& os, SubExpression const& se);

struct Expression {
  // Expression(std::string oper1, std::string oper2)
  //   : query(), subexpressions(){
  //   argument.push_back(subexp1);
  //   argument.push_back(subexp2);
  // }
  // Expression(std::string q, SubExpression subexp1, SubExpression subexp2)
  //   : query(q), subexpressions(){
  //   subexpressions.push_back(subexp1);
  //   subexpressions.push_back(subexp2);
  // }
  Expression(SubExpression subexp) : query(), argument() {
    subexpressions.push_back(subexp);
  }
  Expression(SubExpression subexp1, SubExpression subexp2)
      : query(), argument() {
    subexpressions.push_back(subexp1);
    subexpressions.push_back(subexp2);
  }
  Expression(std::string q, SubExpression subexp1, SubExpression subexp2)
      : query(q), argument() {
    subexpressions.push_back(subexp1);
    subexpressions.push_back(subexp2);
  }
  Expression(std::string q, std::vector<std::string> args, SubExpression subexp)
      : query(q), argument(args) {
    subexpressions.push_back(subexp);
  }
  Expression(std::string q, std::vector<std::string> args,
             std::vector<SubExpression> subexps)
      : query(q), argument(args), subexpressions(subexps){};
  Expression(std::string q, std::vector<SubExpression> subexps)
      : query(q), argument(), subexpressions(subexps){};
  Expression(std::string q, std::vector<std::string> args)
      : query(q), argument(args), subexpressions(){};
  Expression(std::string q) : query(q), argument(), subexpressions(){};
  Expression(std::vector<SubExpression> subexps)
      : query(), argument(), subexpressions(subexps){};
  Expression(std::vector<std::string> args)
      : query(), argument(args), subexpressions(){};
  Expression() : query(), argument(), subexpressions(){};

  std::string query;                          // select, project, ...,
  std::vector<std::string> argument;          // attribute_list condition
  std::vector<SubExpression> subexpressions;  // atomic_expression

  friend std::ostream& operator<<(std::ostream& os, Expression const& e) {
    os << "{";
    os << e.query;
    os << " ( ";
    for (std::string arg : e.argument) {
      os << arg << " ";
    }
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
                          (std::string,
                           query)(std::vector<std::string>,
                                  argument)(std::vector<SubExpression>,
                                            subexpressions))

struct subexpression_printer : boost::static_visitor<void> {
  subexpression_printer(std::ostream& os) : _os(os) {}
  std::ostream& _os;

  void operator()(std::string const& q) const { _os << q << " "; }

  void operator()(Expression const& e) const {
    print(e.query, e.argument, e.subexpressions);
  }

  void print(std::string const& query, std::vector<std::string> const& args,
             std::vector<SubExpression> const& subexps) const {
    _os << "{";
    _os << query;
    _os << " ( ";
    for (std::string arg : args) {
      _os << arg << " ";
    }
    _os << ") ";
    _os << "[ ";
    BOOST_FOREACH (SubExpression const& sexp, subexps) {
      boost::apply_visitor(subexpression_printer(_os), sexp);
    }
    _os << "]";
    _os << "}";
  }
};

std::ostream& operator<<(std::ostream& os, SubExpression const& se) {
  boost::apply_visitor(subexpression_printer(os), se);
  return os;
}

struct Argument {
  Argument(Expression exp);
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

BOOST_FUSION_ADAPT_STRUCT(Argument,
                          (std::string, relation_name)(std::vector<std::string>,
                                                       entries))

// struct Command {
//   Command(std::string c, Argument a) : command(c), argument(a){};
//   Command(std::string c) : command(c), argument(){};
//   Command(Argument a) : command(), argument(a){};
//   Command() : command(), argument(){};

//   std::string command; // open_cmd, close_cmd, write_cmd...
//   std::string relation_name;
//   Argument argument; /// won't be used after conversion

//   Expression expression; // atomic_expression or expression
//   std::vector<std::string> typed_attribute_list; // typed-attribute-list
//   std::vector<std::string> attribute_list; // attribute-list
//   std::vector<std::string> attribute_value_list;  // attribute-name = literal
//   {
//                                                   // , attribute-name =
//                                                   literal
//                                                   // }
//   //Condition condition; // not used until Condition is implented, currently
//   put in argument
//   std::vector<std::string> literal_list;  // ( literal { , literal } )

//   friend std::ostream& operator<<(std::ostream& os, Command const& ss) {
//     os << ss.command << "||";
//     os << ss.argument;
//     return os;
//   }
// };

// BOOST_FUSION_ADAPT_STRUCT(Command,
//                           (std::string, command)
//                           (Argument, argument)
//                           (std::string, relation_name)
//                           (Expression, expression)
//                           (std::vector<std::string>, typed_attribute_list)
//                           (std::vector<std::string>, attribute_list)
//                           (std::vector<std::string>, attribute_value_list)
//                           (std::vector<std::string>, literal_list))

struct Command {
  Command(std::string c, std::string r_name)
      : command(c),
        relation_name(r_name),
        argument(),
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
        argument(),
        expression(),
        typed_attribute_list(t_att_list),
        attribute_list(att_list),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c, std::string r_name,
          std::vector<std::string> att_v_list,
          Argument cond)  // replace with condition later
      : command(c),
        relation_name(r_name),
        argument(cond),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(att_v_list),
        literal_list(){};
  Command(std::string c, std::string r_name, std::vector<std::string> lit_list)
      : command(c),
        relation_name(r_name),
        argument(),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(lit_list){};
  Command(std::string c, std::string r_name, Expression exp)
      : command(c),
        relation_name(r_name),
        argument(),
        expression(exp),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c, std::string r_name,
          Argument cond)  // replace with condition later
      : command(c),
        relation_name(r_name),
        argument(cond),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c, SubExpression exp)
      : command(c),
        relation_name(),
        argument(),
        expression(exp),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command(std::string c)
      : command(c),
        relation_name(),
        argument(),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};
  Command()
      : command(),
        relation_name(),
        argument(),
        expression(),
        typed_attribute_list(),
        attribute_list(),
        attribute_value_list(),
        literal_list(){};

  std::string command;  // open_cmd, close_cmd, write_cmd...
  std::string relation_name;

  Argument argument;      /// won't be used after conversion
  Expression expression;  // atomic_expression or expression
  std::vector<std::string> typed_attribute_list;  // typed-attribute-list
  std::vector<std::string> attribute_list;        // attribute-list
  std::vector<std::string> attribute_value_list;  // attribute-name = literal {
                                                  // , attribute-name = literal
                                                  // }
  // Condition condition; // not used until Condition is implented, currently
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
    os << ss.argument;
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
    (std::string, command)(Argument, argument)(std::string, relation_name)(
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

#endif /* GRAMMAR_OBJECTS_H_ */
