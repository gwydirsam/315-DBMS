#ifndef QUERY_H_
#define QUERY_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <boost/variant.hpp>

// #include <boost/algorithm/string.hpp>
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

// #include <boost/foreach.hpp>

#include "utility.h"

#include "expression.h"

struct Query {
  Query(std::string rname, Expression expr);
  Query(Expression expr);
  Query(std::string rname);
  Query();

  std::string relation_name;
  Expression expression;

  friend std::ostream& operator<<(std::ostream& os, Query const& ss);
};

BOOST_FUSION_ADAPT_STRUCT(Query,
                          (std::string, relation_name)(Expression, expression))

#endif /* QUERY_H_ */
