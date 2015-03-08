#include "query.h"

#include <string>
// #include <boost/algorithm/string.hpp>
// #include <boost/foreach.hpp>
#include <boost/fusion/adapted.hpp>

// #include "engine.h"
#include "expression.h"

Query::Query(std::string rname, Expression expr)
    : relation_name(rname), expression(expr){};
Query::Query(Expression expr) : relation_name(), expression(expr){};
Query::Query(std::string rname) : relation_name(rname), expression(){};
Query::Query() : relation_name(), expression(){};

std::ostream& operator<<(std::ostream& os, Query const& ss) {
  os << ss.relation_name << "<-";
  os << ss.expression;
  return os;
}
