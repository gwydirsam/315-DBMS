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

struct Query;
struct Select;
struct Command;
struct Program;

// query := relation-name <- expr ;
struct Query {
  std::string relation_name;
  std::string expression;

  friend std::ostream& operator<<(std::ostream& os, Query const& ss) {
    return os << ss.relation_name << "|" << ss.expression << ";";
  }
};

BOOST_FUSION_ADAPT_STRUCT(Query,
                          (std::string, relation_name)
                          (std::string, expression))

// selection := select ( condition ) atomic-expr
struct Select {
  std::vector<std::string> columns;
  std::vector<std::string> fromtables;
  std::vector<std::string> whereclause;

  friend std::ostream& operator<<(std::ostream& os, Select const& ss) {
    return os << "SELECT [" << ss.columns.size() << " columns] FROM ["
              << ss.fromtables.size() << " tables] WHERE ["
              << ss.whereclause.size() << " clauses]";
  }
};

BOOST_FUSION_ADAPT_STRUCT(Select,
                          (std::vector<std::string>, columns)
                          (std::vector<std::string>, fromtables)
                          (std::vector<std::string>, whereclause))

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
struct Command {
  Command(std::string c, std::string a): command(c), argument(a){};
  Command(std::string c): command(c), argument(){};
  //Command(std::string a): command(), argument(a){};
  Command(): command(), argument(){};
  
  std::string command;
  std::string argument;

  friend std::ostream& operator<<(std::ostream& os, Command const& ss) {
    return os << ss.command << "|" << ss.argument << ";";
  }
};

BOOST_FUSION_ADAPT_STRUCT(Command,
                          (std::string, command)
                          (std::string, argument))

// program := { ( query | command ) }
struct Program {
  Program(Query q): query(q), isquery(true){};
  Program(Command c): command(c), isquery(false){};
  Program(): query(), command(){};
  
  
  Query query;
  Command command;
  bool isquery; // if true, query, if false, command

  friend std::ostream& operator<<(std::ostream& os, Program const& ss) {
    if (ss.isquery) {
      return os << ss.query;
    } else {
      return os << ss.command;
    }
  }
};

BOOST_FUSION_ADAPT_STRUCT(Program,
                          (Query, query)
                          (Command, command))

// expr := atomic-expr | selection | projection | renaming | union | difference
// | product

template <typename It, typename Skipper = boost::spirit::qi::space_type>
class Grammar : public boost::spirit::qi::grammar<It, Program(), Skipper> {
 public:
  Grammar() : Grammar::base_type(program) {
    using namespace boost::spirit::qi;

    //sqlident = lexeme[alpha >> *alnum];  // table or column name
    //query_type = lexeme[alpha >> *alnum];  // query type
    //columns = (sqlident % ',');
    //tables = no_case["from"] >> (sqlident % ',');
    //whereclause = no_case["where"] >> lexeme[+(char_ - ';')];
    //start = query_type >> columns >> tables >> whereclause >> ';';

    // atomic-expr := relation-name | ( expr )
    //atomic_expression = relation_name | ( '(' >> expression >> ')');


    // command := ( open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd |
    // create-cmd | update-cmd | insert-cmd | delete-cmd ) ;
    cmd_name = lexeme[+(upper)];
    argument = lexeme[*(char_ - ';')];
    io_cmd = cmd_name; // open, close, write and exit

    //show_cmd =   cmd_name >> atomic_expression;
    show_cmd = no_case["SHOW"];

    //create_cmd = no_case["SHOW"] >> ...;
    create_cmd = no_case["CREATE"] >> ';';
    //update_cmd = no_case["SHOW"] >> ...;
    update_cmd = no_case["UPDATE"] >> ';';
    //insert_cmd = no_case["SHOW"] >> relation_name;
    insert_cmd = no_case["INSERT"] >> ';';
    //delete_cmd = no_case["SHOW"] >> relation_name;
    delete_cmd = no_case["DELETE"] >> ';';
    cmd = io_cmd | show_cmd |
              create_cmd | update_cmd | insert_cmd | delete_cmd;
    command = cmd >> argument >> ';';

    // command = expression >> ';';

    // query := relation-name <- expr ;
    expression = lexeme[+(char_ - ';')];
    relation_name = lexeme[alpha >> *alnum];
    query = relation_name >> "<-" >> expression >> ';';
    
    // program := { ( query | command ) }
    program = query | command;

    BOOST_SPIRIT_DEBUG_NODE(program);
    BOOST_SPIRIT_DEBUG_NODE(query);
    BOOST_SPIRIT_DEBUG_NODE(command);
    BOOST_SPIRIT_DEBUG_NODE(relation_name);
    BOOST_SPIRIT_DEBUG_NODE(expression);
    BOOST_SPIRIT_DEBUG_NODE(cmd);
    BOOST_SPIRIT_DEBUG_NODE(cmd_name);
    BOOST_SPIRIT_DEBUG_NODE(relation_name);
    BOOST_SPIRIT_DEBUG_NODE(argument);
    BOOST_SPIRIT_DEBUG_NODE(io_cmd);
    BOOST_SPIRIT_DEBUG_NODE(show_cmd);
    BOOST_SPIRIT_DEBUG_NODE(create_cmd);
    BOOST_SPIRIT_DEBUG_NODE(update_cmd);
    BOOST_SPIRIT_DEBUG_NODE(insert_cmd);
    BOOST_SPIRIT_DEBUG_NODE(delete_cmd);
  }

 private:
  boost::spirit::qi::rule<It, Command(), Skipper> command;
  boost::spirit::qi::rule<It, Query(), Skipper> query;
  boost::spirit::qi::rule<It, std::string(), Skipper> relation_name, expression,
                                 cmd_name, cmd, argument;
  boost::spirit::qi::rule<It, std::string(), Skipper> io_cmd,
    show_cmd, create_cmd, update_cmd, insert_cmd, delete_cmd;
  boost::spirit::qi::rule<It, Program(), Skipper> program;
};

template <typename C, typename Skipper>
bool doParse(const C& input, const Skipper& skipper) {
  auto f(std::begin(input)), l(std::end(input));

  Grammar<decltype(f), Skipper> p;
  Program program;

  try {
    using namespace boost::spirit::qi;
    bool ok = phrase_parse(f, l, p, skipper, program);
    if (ok) {
      std::cout << "parse success\n";
      std::cout << "Program: " << program << "\n";
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

//// old version
// template <typename It, typename Skipper = boost::spirit::qi::space_type>
// class Grammar : public boost::spirit::qi::grammar<It, Query(), Skipper> {
// public:
//  Grammar() : Grammar::base_type(start) {
//    using namespace boost::spirit::qi;
//
//    sqlident = lexeme[alpha >> *alnum];  // table or column name
//
//    query_type = lexeme[alpha >> *alnum];  // query type
//
//    columns = (sqlident % ',');
//    tables = no_case["from"] >> (sqlident % ',');
//    whereclause = no_case["where"] >> lexeme[+(char_ - ';')];
//
//    start = query_type >> columns >> tables >> whereclause >> ';';
//
//    BOOST_SPIRIT_DEBUG_NODE(start);
//    BOOST_SPIRIT_DEBUG_NODE(sqlident);
//    BOOST_SPIRIT_DEBUG_NODE(query_type);
//    BOOST_SPIRIT_DEBUG_NODE(columns);
//    BOOST_SPIRIT_DEBUG_NODE(tables);
//    BOOST_SPIRIT_DEBUG_NODE(whereclause);
//  }
//
// private:
//  boost::spirit::qi::rule<It, std::string(), Skipper> sqlident;
//  boost::spirit::qi::rule<It, std::string(), Skipper> query_type;
//  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> columns,
//      tables, whereclause;
//  boost::spirit::qi::rule<It, Query(), Skipper> start;
//};
//
// template <typename C, typename Skipper>
// bool doParse(const C& input, const Skipper& skipper) {
//  auto f(std::begin(input)), l(std::end(input));
//
//  Grammar<decltype(f), Skipper> p;
//  Query query;
//
//  try {
//    using namespace boost::spirit::qi;
//    bool ok = phrase_parse(f, l, p, skipper, query);
//    if (ok) {
//      std::cout << "parse success\n";
//      std::cout << "Query: " << query << "\n";
//    } else
//      std::cerr << "parse failed: '" << std::string(f, l) << "'\n";
//
//    if (f != l)
//      std::cerr << "trailing unparsed: '" << std::string(f, l) << "'\n";
//    return ok;
//  } catch (const boost::spirit::qi::expectation_failure<decltype(f)>& e) {
//    std::string frag(e.first, e.last);
//    std::cerr << e.what() << "'" << frag << "'\n";
//  }
//
//  return false;
//}

#endif  // GRAMMAR_H_
