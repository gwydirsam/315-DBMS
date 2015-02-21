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

int main(int argc, char* argv[]) {
  std::string input;
  std::cout << "Welcome to ParserTester" << std::endl;

  std::cout << "Try phrases like:" << std::endl;
  std::cout << "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years "
               "INTEGER) PRIMARY KEY (name, kind);" << std::endl;
  std::cout << "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);"
            << std::endl;
  std::cout << "INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);"
            << std::endl;
  std::cout << "INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);"
            << std::endl;
  std::cout << "INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);"
            << std::endl;
  std::cout << "INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);"
            << std::endl;
  std::cout << "SHOW animals;" << std::endl;
  std::cout << "dogs <- select (kind == \"dog\") animals;" << std::endl;
  std::cout << "old_dogs <- select (age > 10) dogs;" << std::endl;
  std::cout << "cats_or_dogs <- dogs + (select (kind == \"cat\") animals);"
            << std::endl;
  std::cout << "CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);"
            << std::endl;
  std::cout
      << "INSERT INTO species VALUES FROM RELATION project (kind) animals;"
      << std::endl;
  std::cout << "a <- rename (aname, akind) (project (name, kind) animals);"
            << std::endl;
  std::cout << "common_names <- project (name) (select (aname == name && akind "
               "!= kind) (a * animals));" << std::endl;
  std::cout << "answer <- common_names;" << std::endl;
  std::cout << "SHOW answer;" << std::endl;
  std::cout << "WRITE animals;" << std::endl;
  std::cout << "CLOSE animals;" << std::endl;
  std::cout << "EXIT;" << std::endl;

  // loop forever
  while (true) {
    std::cout << "Type a phrase to be parsed:" << std::endl;
    std::getline(std::cin, input);

    // Create Grammar and Output Program
    auto f(std::begin(input)), l(std::end(input));

    Grammar<decltype(f), boost::spirit::qi::space_type> p;
    Program program;

    try {
      using namespace boost::spirit::qi;
      bool ok = phrase_parse(f, l, p, boost::spirit::qi::space, program);
      if (ok) {
        std::cout << "parse success" << std::endl;
        std::cout << "Program: " << program << std::endl;
      } else {
        std::cerr << "parse failed: '" << std::string(f, l) << std::endl;
      }
      if (f != l) {
        std::cerr << "trailing unparsed: '" << std::string(f, l) << std::endl;
      }
    } catch (const boost::spirit::qi::expectation_failure<decltype(f)>& e) {
      std::string frag(e.first, e.last);
      std::cerr << e.what() << "'" << frag << std::endl;
    }
  }

  return 0;
}
