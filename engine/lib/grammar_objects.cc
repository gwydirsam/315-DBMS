#include "grammar_objects.h"
#include "relation.h"
#include "engine.h"
#include "utility.h"

std::ostream& operator<<(std::ostream& os, SubCondition const& sc) {
  boost::apply_visitor(subcondition_printer(os), sc);
  return os;
}

std::ostream& operator<<(std::ostream& os, SubExpression const& se) {
  boost::apply_visitor(subexpression_printer(os), se);
  return os;
}

void execute_program(Engine& db, const Program& p) {
  boost::apply_visitor(program_execute(db), p);
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
    relation = db.select(condition, subexps[0]);
  } else if (queryname == "PROJECT") {
    // project
    // projection := project ( attribute-list ) atomic-expr
    relation = db.project(args, subexps[0]);
  } else if (queryname == "RENAME") {
    //     renaming := rename ( attribute-list ) atomic-expr
    // TODO: maybe have change the way rename columns works
    for (int i = 0; i < args.size(); ++i) {
      relation = db.rename_column(subexps[0],
                                  subexps[0].get_column(i).title(), args[i]);
    }
  } else if (queryname == "UNION") {
    // union := atomic-expr + atomic-expr
    relation = db.setunion(subexps[0], subexps[1]);
  } else if (queryname == "DIFFERENCE") {
    // difference := atomic-expr - atomic-expr
    relation = db.setdifference(subexps[0], subexps[1]);
  } else if (queryname == "PRODUCT") {
    // product := atomic-expr * atomic-expr
    relation = db.setcrossproduct(subexps[0], subexps[1]);
  } else {
    relation = db.find_relation_or_view(subexps[0].title());
  }

  return relation;
}
