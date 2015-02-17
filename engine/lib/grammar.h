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

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/algorithm/string.hpp>

// Grammar
// program := { ( query | command ) }
struct ProgramStatement {
  std::string statement;
};

BOOST_FUSION_ADAPT_STRUCT(ProgramStatement, (std::string, statement))

// query := relation-name <- expr ;
struct QueryStatement {
  std::string relation_name;
  std::string expresion;
};

BOOST_FUSION_ADAPT_STRUCT(QueryStatement,
                          (std::string, relation_name)(std::string, expression))

// command := ( open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd |
// create-cmd | update-cmd | insert-cmd | delete-cmd ) ;
struct CommandStatement {
  std::string command;
};

// selection := select ( condition ) atomic-expr
// expr := atomic-expr | selection | projection | renaming | union | difference
// | product
struct Expression {
  std::string query_type;  // select, union, etc.
  std::vector<std::string> columns;
  std::vector<std::string> fromtables;
  std::vector<std::string> whereclause;

  friend std::ostream& operator<<(std::ostream& os, Expression const& ss) {
    std::string query_type_upper = ss.query_type;
    boost::to_upper(query_type_upper);  // uppercase query name
    return os << query_type_upper << " [" << ss.columns.size()
              << " columns] FROM [" << ss.fromtables.size()
              << " tables] WHERE [" << ss.whereclause.size() << " clauses]";
  }
};

BOOST_FUSION_ADAPT_STRUCT(
    Expression, (std::string, query_type)(std::vector<std::string>, columns)(
                    std::vector<std::string>,
                    fromtables)(std::vector<std::string>, whereclause))

// relation-name := identifier

// identifier := alpha { ( alpha | digit ) }
// alpha := a | … | z | A | … | Z | _
// digit := 0 | … | 9
// atomic-expr := relation-name | ( expr )
// selection := select ( condition ) atomic-expr
// condition := conjunction { || conjunction }
// conjunction := comparison { && comparison }
// comparison := operand op operand | ( condition )
// op := == | != | < | > | <= | >=
// operand := attribute-name | literal
// attribute-name := identifier
// literal := intentionally left unspecified (strings, numbers, etc.)
// projection := project ( attribute-list ) atomic-expr
// attribute-list := attribute-name { , attribute-name }
// renaming := rename ( attribute-list ) atomic-expr
// union := atomic-expr + atomic-expr
// difference := atomic-expr - atomic-expr
// product := atomic-expr * atomic-expr
//
// DML
//
// command := ( open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd |
// create-cmd | update-cmd | insert-cmd | delete-cmd ) ;
// open-cmd := OPEN relation-name
// close-cmd := CLOSE relation-name
// write-cmd := WRITE relation-name
// exit-cmd := EXIT
// show-cmd := SHOW atomic-expr
// create-cmd := CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY
// ( attribute-list )
//
// update-cmd := UPDATE relation-name SET attribute-name = literal { ,
// attribute-name = literal } WHERE condition
//
// insert-cmd := INSERT INTO relation-name VALUES FROM ( literal { , literal } )
// |
//    INSERT INTO relation-name VALUES FROM RELATION expr
//
// delete-cmd := DELETE FROM relation-name WHERE condition
// typed-attribute-list := attribute-name type { , attribute-name type }
// type := VARCHAR ( integer ) | INTEGER
// integer := digit { digit }
//
// A program in our data manipulation language (DML) is then defined as:
//
// program := { ( query | command ) }

template <typename It, typename Skipper = boost::spirit::qi::space_type>
class Grammar : public boost::spirit::qi::grammar<It, Expression(), Skipper> {
 public:
  Grammar() : Grammar::base_type(start) {
    using namespace boost::spirit::qi;

    sqlident = lexeme[alpha >> *alnum];  // table or column name

    query_type = lexeme[alpha >> *alnum];  // query type

    columns = (sqlident % ',');
    tables = no_case["from"] >> (sqlident % ',');
    whereclause = no_case["where"] >> lexeme[+(char_ - ';')];

    start = query_type >> columns >> tables >> whereclause >> ';';

    BOOST_SPIRIT_DEBUG_NODE(start);
    BOOST_SPIRIT_DEBUG_NODE(sqlident);
    BOOST_SPIRIT_DEBUG_NODE(query_type);
    BOOST_SPIRIT_DEBUG_NODE(columns);
    BOOST_SPIRIT_DEBUG_NODE(tables);
    BOOST_SPIRIT_DEBUG_NODE(whereclause);
  }

 private:
  boost::spirit::qi::rule<It, std::string(), Skipper> sqlident;
  boost::spirit::qi::rule<It, std::string(), Skipper> query_type;
  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> columns,
      tables, whereclause;
  boost::spirit::qi::rule<It, Expression(), Skipper> start;
};

template <typename C, typename Skipper>
bool doParse(const C& input, const Skipper& skipper) {
  auto f(std::begin(input)), l(std::end(input));

  Grammar<decltype(f), Skipper> p;
  Expression query;

  try {
    using namespace boost::spirit::qi;
    bool ok = phrase_parse(f, l, p, skipper, query);
    if (ok) {
      std::cout << "parse success\n";
      std::cout << "Expression: " << query << "\n";
    } else
      std::cerr << "parse failed: '" << std::string(f, l) << "'\n";

    if (f != l)
      std::cerr << "trailing unparsed: '" << std::string(f, l) << "'\n";
    return ok;
  } catch (const boost::spirit::qi::expectation_failure<decltype(f)>& e) {
    std::string frag(e.first, e.last);
    std::cerr << e.what() << "'" << frag << "'\n";
  }

  return false;
}

#endif  // GRAMMAR_H_
