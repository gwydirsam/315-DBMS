#ifndef PROGRAM_H_
#define PROGRAM_H_

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

#include "utility.h"

#include "engine.h"
#include "condition.h"
#include "command.h"
#include "query.h"

typedef boost::variant<Query, Command> Program;

struct program_accessor : boost::static_visitor<> {
  program_accessor(std::vector<std::vector<std::string>>& args);
  std::vector<std::vector<std::string>>& args_;

  void operator()(Query const& q) const;
  void operator()(Command const& q) const;
};

void execute_program(Engine& db, const Program& p);

struct program_execute : boost::static_visitor<void> {
  program_execute(Engine& db);
  Engine& db_;

  void operator()(Query const& q) const;
  void operator()(Command const& q) const;
};

#endif /* PROGRAM_H_ */
