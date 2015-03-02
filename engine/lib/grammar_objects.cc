#include "grammar_objects.h"

std::ostream& operator<<(std::ostream& os, SubExpression const& se) {
  boost::apply_visitor(subexpression_printer(os), se);
  return os;
}
