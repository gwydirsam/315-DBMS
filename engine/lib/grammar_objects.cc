#include "grammar_objects.h"

std::ostream& operator<<(std::ostream& os, SubCondition const& sc) {
  boost::apply_visitor(subcondition_printer(os), sc);
  return os;
}

std::ostream& operator<<(std::ostream& os, SubExpression const& se) {
  boost::apply_visitor(subexpression_printer(os), se);
  return os;
}
