// CSCE 315-503
// grammar.h

#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#ifdef DEBUG
#define BOOST_SPIRIT_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <iterator>

#include <boost/algorithm/string.hpp>

#include <boost/variant.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_as.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "grammar_objects.h"

template <typename It = std::string::const_iterator,
          typename Skipper = boost::spirit::qi::space_type>
class Grammar : public boost::spirit::qi::grammar<It, Program(), Skipper> {
 public:
  Grammar();

 private:
  boost::spirit::qi::rule<It, Command(), Skipper> command;
  boost::spirit::qi::rule<It, Command(), Skipper> io_cmd, exit_cmd, show_cmd,
      create_cmd, update_cmd, insert_cmd, delete_cmd;

  boost::spirit::qi::rule<It, Query(), Skipper> query;
  boost::spirit::qi::rule<It, std::string(), Skipper> relation_name;

  boost::spirit::qi::rule<It, Expression(), Skipper> expressions;

  boost::spirit::qi::rule<It, SubExpression(), Skipper> atomic_expressions;

  boost::spirit::qi::rule<It, Expression(), Skipper> selection, projection,
      renaming, setunion, difference, product;

  boost::spirit::qi::rule<It, Condition(), Skipper> conditions;
  boost::spirit::qi::rule<It, SubCondition(), Skipper> conjunctions,
      comparisons;

  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper>
      attribute_list, typed_attribute_list;

  boost::spirit::qi::rule<It, std::string(), Skipper> identifier, op, operand,
      attribute_name, type, literal;

  boost::spirit::qi::rule<It, Program(), Skipper> program;
};

template <typename C>
Program parse_string(const C& input) {
  auto f(std::begin(input)), l(std::end(input));

  Grammar<decltype(f), boost::spirit::qi::space_type> p;
  Program program;

  try {
    using namespace boost::spirit::qi;
    bool ok = phrase_parse(f, l, p, boost::spirit::qi::space, program);
    if (ok) {
      return program;
    } else {
      std::string errstr = "Grammar: parse failed: " + std::string(f, l);
      errlog(errstr);
      return program;
    }

    if (f != l) {
      std::string errstr =
          "Grammar: parse failed: trailing unparsed: " + std::string(f, l);
      errlog(errstr);
    }
  } catch (const boost::spirit::qi::expectation_failure<decltype(f)>& e) {
    std::string frag(e.first, e.last);
    std::cerr << e.what() << "'" << frag << std::endl;
  }

  return program;
}

#endif  // GRAMMAR_H_
