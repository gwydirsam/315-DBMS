// Rabia Gunonu, Sam Gwydir, Nicolas Juarez, Daniel Koon
// CSCE 315-503
// main.cc

#include <iostream>
#include <memory>

#include "../lib/engine.h"
#include "../lib/column.h"
#include "../lib/relation.h"
#include "../lib/utility.h"
#include "../lib/grammar.h"

int main(int argc, char *argv[]) {
  //const std::string input =
  //    "select id, name, price from books, authors where books.author_id = "
  //    "authors.id;";
  const std::string input1 = "posts  <-   select entry from table0  ;";
  std::cout << input1 << std::endl;
  doParse(input1, boost::spirit::qi::space);

  const std::string input2 = "OPEN table;";
  std::cout << input2 << std::endl;
  doParse(input2, boost::spirit::qi::space);

  const std::string input3 = "EXIT;";
  std::cout << input3 << std::endl;
  doParse(input3, boost::spirit::qi::space);

  const std::string input4 = "CLOSE table;";
  std::cout << input4 << std::endl;
  doParse(input4, boost::spirit::qi::space);

  const std::string input5 = "WRITE table;";
  std::cout << input5 << std::endl;
  doParse(input5, boost::spirit::qi::space);

  // doParse(input2, boost::spirit::qi::space);

  //auto f(std::begin(input)), l(std::end(input));

  //Grammar<decltype(f), boost::spirit::qi::space_type> p;
  //Program program;

  //using namespace boost::spirit::qi;
  //bool ok = phrase_parse(f, l, p, boost::spirit::qi::space, program);
  //if (ok) {
  //  std::cout << "parse success" << std::endl;
  //  std::cout << "Program: " << program << std::endl;
  //  // std::cout << "Columns: " << std::endl;
  //  // for (std::string column_name : program.columns) {
  //  //   std::cout << column_name << std::endl;
  //  // }
  //  // std::cout << "From: " << std::endl;
  //  // for (std::string from_name : program.fromtables) {
  //  //   std::cout << from_name << std::endl;
  //  // }
  //  // std::cout << "Where: " << std::endl;
  //  // for (std::string where_name : program.whereclause) {
  //  //   std::cout << where_name << std::endl;
  //  // }
  //}

  //auto f2(std::begin(input2)), l2(std::end(input2));

  //Grammar<decltype(f2), boost::spirit::qi::space_type> p2;
  //Program program2;

  //using namespace boost::spirit::qi;
  //bool ok2 = phrase_parse(f2, l2, p2, boost::spirit::qi::space, program2);
  //if (ok2) {
  //  std::cout << "parse success" << std::endl;
  //  std::cout << "Program: " << program2 << std::endl;
  //  std::cout << "Columns: " << std::endl;
  //  for (std::string column_name : program2.columns) {
  //    std::cout << column_name << std::endl;
  //  }
  //  std::cout << "From: " << std::endl;
  //  for (std::string from_name : program2.fromtables) {
  //    std::cout << from_name << std::endl;
  //  }
  //  std::cout << "Where: " << std::endl;
  //  for (std::string where_name : program2.whereclause) {
  //    std::cout << where_name << std::endl;
  //  }
  //}

  return 0;
}
