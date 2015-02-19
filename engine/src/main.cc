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
  // test spaces everywhere
  const std::string input1 = " posts  <-   select (aname == name && akind != kind) (a * animals)  ;";
  std::cout << input1 << std::endl;
  doParse(input1, boost::spirit::qi::space);
  draw_line();

  const std::string input1a = "dogs <- select (kind == \"dog\") animals;";
  std::cout << input1a << std::endl;
  doParse(input1a, boost::spirit::qi::space);
  draw_line();

  const std::string input1b = "old_dogs <- select (age > 10) dogs;";
  std::cout << input1b << std::endl;
  doParse(input1b, boost::spirit::qi::space);
  draw_line();

  const std::string input1c = "cats_or_dogs <- dogs + (select (kind == \"cat\") animals);";
  std::cout << input1c << std::endl;
  doParse(input1c, boost::spirit::qi::space);
  draw_line();

  const std::string input2 = "OPEN table;";
  std::cout << input2 << std::endl;
  doParse(input2, boost::spirit::qi::space);
  draw_line();

  const std::string input4 = "CLOSE table;";
  std::cout << input4 << std::endl;
  doParse(input4, boost::spirit::qi::space);
  draw_line();

  const std::string input5 = "WRITE table;";
  std::cout << input5 << std::endl;
  doParse(input5, boost::spirit::qi::space);
  draw_line();

  const std::string input3 = "EXIT;";
  std::cout << input3 << std::endl;
  doParse(input3, boost::spirit::qi::space);
  draw_line();

  // create-cmd := CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY
  // KEY ( attribute-list )
  const std::string input6 =
      "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
  std::cout << input6 << std::endl;
  doParse(input6, boost::spirit::qi::space);
  draw_line();

  const std::string input7 = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);";
  std::cout << input7 << std::endl;
  doParse(input7, boost::spirit::qi::space);
  draw_line();

  const std::string input8 = "SHOW animals;";
  std::cout << input8 << std::endl;
  doParse(input8, boost::spirit::qi::space);
  draw_line();

  const std::string input9 = "a <- rename (aname, akind) (project (name, kind) animals);";
  std::cout << input9 << std::endl;
  doParse(input9, boost::spirit::qi::space);
  draw_line();

  const std::string input10 = "common_names <- project (name) (select (aname == name && akind != kind) (a * animals));";
  std::cout << input10 << std::endl;
  doParse(input10, boost::spirit::qi::space);
  draw_line();

  const std::string input11 = "answer <- common_names;";
  std::cout << input11 << std::endl;
  doParse(input11, boost::spirit::qi::space);
  draw_line();

  const std::string input12 = "INSERT INTO species VALUES FROM RELATION project (kind) animals;";
  std::cout << input12 << std::endl;
  doParse(input12, boost::spirit::qi::space);
  draw_line();


  const std::string input13 = "CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);";
  std::cout << input13 << std::endl;
  doParse(input13, boost::spirit::qi::space);
  draw_line();

  const std::string input14 = "UPDATE species SET name = \"Sam\" WHERE ID == 11;";
  std::cout << input14 << std::endl;
  doParse(input14, boost::spirit::qi::space);
  draw_line();

  const std::string input15 = "DELETE FROM animals WHERE extinct == \"false\";";
  std::cout << input15 << std::endl;
  doParse(input15, boost::spirit::qi::space);
  draw_line();

  const std::string input16 = "animals <- species * animals;";
  std::cout << input16 << std::endl;
  doParse(input16, boost::spirit::qi::space);
  draw_line();

  // doParse(input2, boost::spirit::qi::space);

  // auto f(std::begin(input)), l(std::end(input));

  // Grammar<decltype(f), boost::spirit::qi::space_type> p;
  // Program program;

  // using namespace boost::spirit::qi;
  // bool ok = phrase_parse(f, l, p, boost::spirit::qi::space, program);
  // if (ok) {
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

  // auto f2(std::begin(input2)), l2(std::end(input2));

  // Grammar<decltype(f2), boost::spirit::qi::space_type> p2;
  // Program program2;

  // using namespace boost::spirit::qi;
  // bool ok2 = phrase_parse(f2, l2, p2, boost::spirit::qi::space, program2);
  // if (ok2) {
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
