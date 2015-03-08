#include "expression.h"

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/adapted.hpp>

#include "engine.h"

#include "utility.h"

std::ostream& operator<<(std::ostream& os, Expression const& e) {
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

std::ostream& operator<<(std::ostream& os, SubExpression const& se) {
  boost::apply_visitor(subexpression_printer(os), se);
  return os;
}

Relation execute_expression(Engine& db, std::string query,
                            std::vector<std::string> condition,
                            std::vector<std::string> args,
                            std::vector<Relation> subexps) {
  Relation relation;
  std::string queryname = query;
  boost::algorithm::to_upper(queryname);

  std::string errmsg = "Grammar: Execute Expression: " + queryname + " ";
  for (std::string cond : condition) {
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

  // Condition condition;                        // condition
  // std::vector<std::string> argument;          // attribute_list
  // std::vector<SubExpression> subexpressions;  // atomic_expression
  if (queryname == "SELECT") {
    // selection := select ( condition ) atomic-expr
    // select (condition) from subexps[0](should be a relation/view/table)

    // won't work yet
    // std::vector<std::string> columnnames;
    // columnnames.emplace_back(condition[3]);
    relation = db.select(condition, subexps[0]);
  } else if (queryname == "PROJECT") {
    // project
    // projection := project ( attribute-list ) atomic-expr
    relation = db.project(args, subexps[0]);
  } else if (queryname == "RENAME") {
    //     renaming := rename ( attribute-list ) atomic-expr
    // TODO: maybe have change the way rename columns works
    if (args.size() != subexps[0].num_cols()) {
      std::string errstr = "Execute Expression: Rename: # of attributes, " +
                           std::to_string(args.size()) +
                           " does not match # of columns in " +
                           subexps[0].title() + ", (" +
                           std::to_string(subexps[0].num_cols()) + ")";
      errlog(errstr);
    }
    for (unsigned int i = 0; i < args.size(); ++i) {
      relation = db.rename_column(subexps[0], subexps[0].get_column(i).title(),
                                  args[i]);
    }
  } else if (queryname == "UNION") {
    // note: order of expressions is reversed when you get here
    // union := atomic-expr + atomic-expr
    relation = db.setunion(subexps[1], subexps[0]);
  } else if (queryname == "DIFFERENCE") {
    // note: order of expressions is reversed when you get here
    // difference := atomic-expr - atomic-expr
    relation = db.setdifference(subexps[1], subexps[0]);
  } else if (queryname == "PRODUCT") {
    // note: order of expressions is reversed when you get here
    // product := atomic-expr * atomic-expr
    relation = db.setcrossproduct(subexps[1], subexps[0]);
  } else {
    relation = db.find_relation_or_view(subexps[0].title());
  }

  return relation;
}

void subexpression_accessor::operator()(Expression const& e) const {
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

void subexpression_printer::print(
    std::string const& query, Condition const& cond,
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

Relation subexpression_execute::operator()(std::string const& q) const {
  // args_.emplace(std::begin(args_), q);
  return db_.find_relation_or_view(q);
}

Relation subexpression_execute::operator()(Condition const& c) const {
  // args_.emplace(std::begin(args_), c.operation);
  // BOOST_FOREACH (SubCondition const& subcon, c.subconditions) {
  //   boost::apply_visitor(*this, subcon);
  // }
  return Relation("empty");
}

Relation subexpression_execute::operator()(Expression const& e) const {
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
