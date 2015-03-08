#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>

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

#include <boost/foreach.hpp>

#include "relation.h"

class Engine;

#include "condition.h"

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
    std::string errstr = "Expression: " + q + " ";
    for (std::string str : args) {
      errstr += str = " ";
    }
    errlog(errstr);
    std::cerr << subexp << std::endl;
  }
  Expression(std::string q, Condition cond, SubExpression subexp)
      : query(q), condition(cond), argument() {
    subexpressions.push_back(subexp);
    std::string errstr = "Expression: " + q;
    errlog(errstr);
    std::cerr << cond << std::endl;
    std::cerr << subexp << std::endl;
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

  friend std::ostream& operator<<(std::ostream& os, Expression const& e);
};

BOOST_FUSION_ADAPT_STRUCT(Expression,
                          (std::string, query)(Condition, condition)(
                              std::vector<std::string>,
                              argument)(std::vector<SubExpression>,
                                        subexpressions))

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
             std::vector<SubExpression> const& subexps) const;
};

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

  void operator()(Expression const& e) const;

  void operator()(std::vector<SubExpression> const& subexps) const {
    BOOST_FOREACH (SubExpression const& sexp, subexps) {
      boost::apply_visitor(*this, sexp);
    }
  }
};

Relation execute_expression(Engine& db, std::string query,
                            std::vector<std::string> condition,
                            std::vector<std::string> args,
                            std::vector<Relation> subexps);

struct subexpression_execute : boost::static_visitor<Relation> {
  subexpression_execute(Engine& db) : db_(db) {}
  Engine& db_;

  Relation operator()(std::string const& q) const;
  Relation operator()(Condition const& c) const;
  Relation operator()(Expression const& e) const;
};

#endif /* EXPRESSION_H_ */
