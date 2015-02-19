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

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_as.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>



struct Query;
//struct Select;
struct Command;
struct Program;

// query := relation-name <- expr ;
struct Query {
  Query(std::string rname, std::vector<std::string> expr): relation_name(rname), expression(expr){};
  Query(std::vector<std::string> expr): relation_name(), expression(expr){};
  Query(std::string rname): relation_name(rname), expression(){};
  Query(): relation_name(), expression(){};
  
  std::string relation_name;
  std::vector<std::string> expression;

  friend std::ostream& operator<<(std::ostream& os, Query const& ss) {
    os << ss.relation_name << "||";
    for (std::string expr : ss.expression) {
      os << expr << "|";
    }
    return os;
  }
};

BOOST_FUSION_ADAPT_STRUCT(Query,
                          (std::string, relation_name)
                          (std::vector<std::string>, expression))

// condition := conjunction { || conjunction }
//struct Condition {
//  
//}

// conjunction := comparison { && comparison }
// comparison := operand op operand | ( condition )
// op := == | != | < | > | <= | >=
// operand := attribute-name | literal
// attribute-name := identifier
// literal := intentionally left unspecified (strings, numbers, etc.)
// expr := atomic-expr | selection | projection | renaming | union | difference | product
// atomic-expr := relation-name | ( expr )
// selection := select ( condition ) atomic-expr
//struct Select {
//  std::vector<std::string> condition;
//  std::vector<std::string> atomic_expression;
//
//  // not finished
//  friend std::ostream& operator<<(std::ostream& os, Select const& ss) {
//    os << "SELECT|";
//    os << "("
//    for (std::string cond : ss.condition) {
//      os << cond << "|";
//    }
//    os << ")"
//    return os << "SELECT " << ss.columns.size() << " columns] FROM ["
//              << ss.fromtables.size() << " tables] WHERE ["
//              << ss.whereclause.size() << " clauses]";
//  }
//};
//
//BOOST_FUSION_ADAPT_STRUCT(Select,
//                          (std::vector<std::string>, columns)
//                          (std::vector<std::string>, fromtables)
//                          (std::vector<std::string>, whereclause))

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
  Command(std::string c, std::vector<std::string> a): command(c), argument(a){};
  Command(std::string c): command(c), argument(){};
  Command(std::vector<std::string> a): command(), argument(a){};
  Command(): command(), argument(){};
  
  std::string command;
  std::vector<std::string> argument;

  friend std::ostream& operator<<(std::ostream& os, Command const& ss) {
    os << ss.command << "||";
    for (std::string arg : ss.argument) {
      os << arg << "|";
    }
    return os;
  }
};

BOOST_FUSION_ADAPT_STRUCT(Command,
                          (std::string, command)
                          (std::vector<std::string>, argument))

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

template <typename It, typename Skipper = boost::spirit::qi::space_type>
class Grammar : public boost::spirit::qi::grammar<It, Program(), Skipper> {
 public:
  Grammar() : Grammar::base_type(program) {
    using namespace boost::spirit::qi;
    using boost::spirit::qi::as;
    using boost::spirit::qi::as_string;

    //sqlident = lexeme[alpha >> *alnum];  // table or column name
    //query_type = lexeme[alpha >> *alnum];  // query type
    //columns = (sqlident % ',');
    //tables = no_case["from"] >> (sqlident % ',');
    //whereclause = no_case["where"] >> lexeme[+(char_ - ';')];
    //start = query_type >> columns >> tables >> whereclause >> ';';

    // alpha := a | … | z | A | … | Z | _
    // digit := 0 | … | 9

    // atomic-expr := relation-name | ( expr )
    // condition := conjunction { || conjunction }
    // conjunction := comparison { && comparison }
    // comparison := operand op operand | ( condition )
    // op := == | != | < | > | <= | >=
    // operand := attribute-name | literal
    // attribute-name := identifier
    // literal := intentionally left unspecified (strings, numbers, etc.)


    // command := ( open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd |
    // create-cmd | update-cmd | insert-cmd | delete-cmd ) ;
    cmd_name = lexeme[+(upper)];
    argument = lexeme[as_string[*(char_ - ';')]];
    io_cmd = cmd_name.alias(); // open, close, write and exit

    // show-cmd := SHOW atomic-expr 
    show_cmd = no_case["show"] >> atomic_expression;

	// create-cmd := CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY
    // ( attribute-list )
    create_cmd = no_case["create table"] >>  relation_name >> string("(") 
				>> typed_attribute_list >> string(")") >> no_case["primary key"]
				>> string("(") >> attribute_list >> string(")") >> ';';

    // update-cmd := UPDATE relation-name SET attribute-name = literal { ,
    // attribute-name = literal } WHERE condition
    update_cmd = no_case["update"] >> relation_name >> no_case["set"]
				>> attribute_name >> string("=") >> literal 
				>> *(',' >> space >> attribute_name >> space >> string("=") >> literal) 
				>> no_case["where"] >> condition >> ';';

    // insert-cmd := INSERT INTO relation-name VALUES FROM ( literal { , literal } )
    // |
    //    INSERT INTO relation-name VALUES FROM RELATION expr
    insert_cmd = no_case["insert into"] >> relation_name >> no_case["values from"] 
				>> string("(") >> literal >> *(',' >> space >> literal) >> string(")") >> ';';

    // delete-cmd := DELETE FROM relation-name WHERE condition
    delete_cmd = no_case["delete from"] >> space >> relation_name >> space >> no_case["where"] >> space >> condition >> ';';
	
    command = (hold[io_cmd] >> argument | hold[show_cmd] | hold[create_cmd] |
               hold[update_cmd] | hold[insert_cmd] | delete_cmd) >> ';';
    // command = cmd >> argument >> ';';

    // condition := conjunction { || conjunction }
    condition = conjunction >> *(string("||") >> conjunction);
    // conjunction := comparison { && comparison }
    conjunction = comparison >> *(string("&&") >> comparison);
    // comparison := operand op operand | ( condition )
    comparison = hold[(operand >> op >> operand)] |
                 (string("(") >> condition >> string(")"));

    // op := == | != | < | > | <= | >=
    op = hold[string("==")] | hold[string("!=")] | hold[string("<")] |
         hold[string(">")] | hold[string("<=")] | string(">=");

    // operand := attribute-name | literal
    operand = hold[attribute_name] | literal;

    // attribute-name := identifier
    attribute_name = identifier.alias();

    // literal := intentionally left unspecified (strings, numbers, etc.)
    literal = lexeme[-char_("\"") >> +alnum >> -char_("\"")];
    
    // attribute-list := attribute-name { , attribute-name }
    attribute_list = attribute_name >> *(',' >> space >> attribute_name) - ')';

    // typed-attribute-list := attribute-name type { , attribute-name type } 
    // type := VARCHAR ( integer ) | INTEGER 
    typed_attribute_list = attribute_name >> type >> *(',' attribute_name) >> type);

    type = ( ) | string("")
    

    // atomic-expr := relation-name | ( expr )
    atomic_expression =
        hold[(string("(") >> expression >> string(")"))] | relation_name;

    // selection := select ( condition ) atomic-expr
    selection = string("select") >> string("(") >> condition >> string(")") >>
                atomic_expression;

    // projection := project ( attribute-list ) atomic-expr
    projection = no_case["project"] >> string("(") >> attribute_list >>
                 string(")") >> atomic_expression;
    // renaming := rename ( attribute-list ) atomic-expr
    renaming = no_case["rename"] >> string("(") >> attribute_list >>
               string(")") >> atomic_expression;

    // setunion := atomic-expr + atomic-expr
    setunion = atomic_expression >> char_('+') >> atomic_expression;
    // difference := atomic-expr - atomic-expr
    difference = atomic_expression >> char_('-') >> atomic_expression;
    // product := atomic-expr * atomic-expr
    product = atomic_expression >> char_('*') >> atomic_expression;

    // expr := atomic-expr | selection | projection | renaming | union | difference
    // | product
    expression = hold[selection] | hold[projection] | hold[renaming] |
                 hold[setunion] | hold[difference] | hold[product] |
                 atomic_expression;
    // expression = lexeme[+alnum >> *(space >> +alnum)] - ';';

    // identifier := alpha { ( alpha | digit ) }
    identifier = lexeme[!char_("\"") >> *char_("a-zA-Z_") >> *char_("0-9a-zA-Z_")];

    // relation-name := identifier
    relation_name = identifier.alias();

    // query := relation-name <- expr ;
    query = relation_name >> "<-" >> expression >> ';';
    
    // program := { ( query | command ) }
    program = hold[query] | command;

    BOOST_SPIRIT_DEBUG_NODE(program);
    BOOST_SPIRIT_DEBUG_NODE(command);
    BOOST_SPIRIT_DEBUG_NODE(query);
    BOOST_SPIRIT_DEBUG_NODE(relation_name);
    BOOST_SPIRIT_DEBUG_NODE(expression);
    BOOST_SPIRIT_DEBUG_NODE(cmd_name);
    BOOST_SPIRIT_DEBUG_NODE(cmd);
    BOOST_SPIRIT_DEBUG_NODE(argument);
    BOOST_SPIRIT_DEBUG_NODE(atomic_expression);
    BOOST_SPIRIT_DEBUG_NODE(selection);
    BOOST_SPIRIT_DEBUG_NODE(projection);
    BOOST_SPIRIT_DEBUG_NODE(renaming);
    BOOST_SPIRIT_DEBUG_NODE(setunion);
    BOOST_SPIRIT_DEBUG_NODE(difference);
    BOOST_SPIRIT_DEBUG_NODE(product);
    BOOST_SPIRIT_DEBUG_NODE(identifier);
    BOOST_SPIRIT_DEBUG_NODE(condition);
    BOOST_SPIRIT_DEBUG_NODE(conjunction);
    BOOST_SPIRIT_DEBUG_NODE(comparison);
    BOOST_SPIRIT_DEBUG_NODE(op);
    BOOST_SPIRIT_DEBUG_NODE(operand);
    BOOST_SPIRIT_DEBUG_NODE(attribute_name);
    BOOST_SPIRIT_DEBUG_NODE(attribute_list);
    BOOST_SPIRIT_DEBUG_NODE(literal);
    BOOST_SPIRIT_DEBUG_NODE(io_cmd);
    BOOST_SPIRIT_DEBUG_NODE(show_cmd);
    BOOST_SPIRIT_DEBUG_NODE(create_cmd);
    BOOST_SPIRIT_DEBUG_NODE(update_cmd);
    BOOST_SPIRIT_DEBUG_NODE(insert_cmd);
    BOOST_SPIRIT_DEBUG_NODE(delete_cmd);

  }

 private:
  boost::spirit::qi::rule<It, Command(), Skipper> command;
  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> argument;

  boost::spirit::qi::rule<It, Query(), Skipper> query;
  boost::spirit::qi::rule<It, std::string(), Skipper> relation_name;
  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> expression;

  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> atomic_expression;

  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> cmd;
  boost::spirit::qi::rule<It, std::string(), Skipper> cmd_name;

  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> selection,
      projection, renaming, setunion, difference, product;

  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> condition,
      conjunction, comparison;

  boost::spirit::qi::rule<It, std::string(), Skipper> identifier, op, operand,
      attribute_name, attribute_list, literal;

  boost::spirit::qi::rule<It, std::string(), Skipper> io_cmd;

  boost::spirit::qi::rule<It, std::vector<std::string>(), Skipper> show_cmd,
      create_cmd, update_cmd, insert_cmd, delete_cmd;

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

#endif  // GRAMMAR_H_
