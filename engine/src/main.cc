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
  draw_line();
  std::cout << "Database Engine" << std::endl;
  std::unique_ptr<Engine> db(new Engine);
  draw_line();

  Column<std::string> first_col("Scrooge");
  first_col.primary_key(true);
  first_col.insert_entry("bah");
  first_col.insert_entry("hum");
  first_col.insert_entry("bug");
  first_col.insert_entry("foo");
  first_col.insert_entry("bar");

  Column<std::string> second_col("Money");
  second_col.insert_entry("$10");
  second_col.insert_entry("$100");
  second_col.insert_entry("$1000");
  second_col.insert_entry("$10000");
  second_col.insert_entry("$100000");

  Column<std::string> third_col("Scrooge");
  third_col.primary_key(true);
  third_col.insert_entry("1");
  third_col.insert_entry("2");
  third_col.insert_entry("3");
  third_col.insert_entry("4");
  third_col.insert_entry("5");

  Column<std::string> fourth_col("Money");
  fourth_col.insert_entry("Money1");
  fourth_col.insert_entry("Money2");
  fourth_col.insert_entry("Money3");
  fourth_col.insert_entry("Money4");
  fourth_col.insert_entry("Money5");

  Column<std::string> fifth_col("Scrooge");
  fifth_col.primary_key(true);
  fifth_col.insert_entry("1");
  fifth_col.insert_entry("4");
  fifth_col.insert_entry("5");

  Column<std::string> sixth_col("Money");
  sixth_col.insert_entry("Money1");
  sixth_col.insert_entry("Money2");
  sixth_col.insert_entry("Money5");

  Column<std::string> seventh_col("id");
  seventh_col.primary_key(true);
  seventh_col.insert_entry("1");
  seventh_col.insert_entry("2");
  seventh_col.insert_entry("3");
  seventh_col.insert_entry("4");
  seventh_col.insert_entry("5");

  Column<std::string> eighth_col("Name");
  eighth_col.insert_entry("sam");
  eighth_col.insert_entry("rabia");
  eighth_col.insert_entry("nick");
  eighth_col.insert_entry("kade");
  eighth_col.insert_entry("leonardo");

  std::vector<Column<std::string> > columns0;
  std::vector<Column<std::string> > columns1;
  std::vector<Column<std::string> > columns2;
  std::vector<Column<std::string> > columns3;
  std::vector<Column<std::string> > columns4;

  columns0.push_back(first_col);
  columns0.push_back(second_col);

  columns1.push_back(third_col);
  columns1.push_back(fourth_col);

  columns2.push_back(first_col);
  columns2.push_back(fourth_col);

  columns3.push_back(fifth_col);
  columns3.push_back(sixth_col);

  columns4.push_back(seventh_col);
  columns4.push_back(eighth_col);

  db->createNewTable("Test0", columns0);
  db->createNewTable("Test1", columns1);
  db->createNewTable("Test2", columns2);
  db->createNewTable("Test3", columns3);
  db->createNewTable("Test4", columns4);

  std::cout << "Number of Open Tables: " << db->num_open_tables() << std::endl;

  std::cout << "List of Open Tables: ";
  db->print_list_open_tables();
  std::cout << std::endl;
  draw_line();

  std::cout << "Unknown Table Index(Should be -1): "
            << db->find_table_index("Unknown") << std::endl;
  draw_line();

  std::cout << "Test0 Table Index: " << db->find_table_index("Test0")
            << std::endl;
  std::cout << db->find_relation("Test0");
  std::cout << std::endl;
  draw_line();

  std::cout << "Test1 Table Index: " << db->find_table_index("Test1")
            << std::endl;
  std::cout << db->find_relation("Test1");
  std::cout << std::endl;
  draw_line();

  std::cout << "Test2 Table Index: " << db->find_table_index("Test2")
            << std::endl;
  std::cout << db->find_relation("Test2");
  std::cout << std::endl;
  draw_line();

  std::cout << "Test3 Table Index: " << db->find_table_index("Test3")
            << std::endl;
  std::cout << db->find_relation("Test3");
  std::cout << std::endl;
  draw_line();

  std::cout << "Test4 Table Index: " << db->find_table_index("Test4")
            << std::endl;
  std::cout << db->find_relation("Test4");
  std::cout << std::endl;
  draw_line();

  std::cout << "Select * From Test0" << std::endl;
  std::cout << db->select({}, "Test0") << std::endl;
  draw_line();

  std::cout << "Select Money From Test1 where Money == Money2" << std::endl;
  std::cout << db->select({"Money"}, "Test1", "Money", "Money2") << std::endl;
  draw_line();

  std::cout << "Select Money From Test2 where Scrooge == bar" << std::endl;
  std::cout << db->select({"Money"}, "Test2", "Scrooge", "bar") << std::endl;
  draw_line();

  std::cout << "Project Scrooge From Test0" << std::endl;
  std::cout << db->project({"Scrooge"}, "Test0") << std::endl;
  draw_line();

  std::cout << "Test0 Union Test1" << std::endl;
  std::cout << db->setunion("Test0", "Test1") << std::endl;
  draw_line();

  std::cout << "Test0 Union (Select Money From Test2) (Should be invalid)"
            << std::endl;
  std::cout << db->setunion(db->find_relation("Test0"),
                            db->select({"Money"}, "Test2")) << std::endl;
  draw_line();

  std::cout << "Test0 Difference Test2 (should be same as Test0)" << std::endl;
  std::cout << db->setdifference(db->find_relation("Test0"),
                                 db->find_relation("Test2")) << std::endl;
  draw_line();

  std::cout << "(Select Money From Test1) Difference "
               "(Select Money From Test3)" << std::endl;
  std::cout << db->setdifference(db->select({"Money"}, "Test1"),
                                 db->select({"Money"}, "Test3")) << std::endl;
  draw_line();

  std::cout << "(Select Scrooge From Test0) Cross Product "
               "(Select Money From Test3)" << std::endl;
  std::cout << db->setcrossproduct(db->select({"Scrooge"}, "Test0"),
                                   db->select({"Money"}, "Test3")) << std::endl;
  draw_line();

  std::cout << "(Select Money From Test0 Where Scrooge = hum) Cross Product "
               "(Select Name From Test4)" << std::endl;
  std::cout << db->setcrossproduct(db->select({"Money"}, "Test0", "Scrooge", "hum"),
                                   db->select({"Name"}, "Test4")) << std::endl;
  draw_line();

  std::cout << "Close Database" << std::endl;
  db->exitDatabase();
  draw_line();
  draw_line();

  // const std::string input =
  //    "select id, name, price from books, authors where books.author_id = "
  //    "authors.id;";
  // const std::string input2 =
  //    "project id, name, price from books, authors where books.author_id = "
  //    "authors.id;";

  //// doParse(input, boost::spirit::qi::space);
  //// doParse(input2, boost::spirit::qi::space);

  // auto f(std::begin(input2)), l(std::end(input2));

  // Grammar<decltype(f), boost::spirit::qi::space_type> p;
  // Expression query;

  // using namespace boost::spirit::qi;
  // bool ok = phrase_parse(f, l, p, boost::spirit::qi::space, query);
  // if (ok) {
  //  std::cout << "parse success" <<std::endl;
  //  std::cout << "Expression: " << query << std::endl;
  //  std::cout << "Columns: " << std::endl;
  //  for(std::string column_name : query.columns) {
  //    std::cout << column_name << std::endl;
  //  }
  //  std::cout << "From: " << std::endl;
  //  for(std::string from_name : query.fromtables) {
  //    std::cout << from_name << std::endl;
  //  }
  //  std::cout << "Where: " << std::endl;
  //  for(std::string where_name : query.whereclause) {
  //    std::cout << where_name << std::endl;
  //  }
  //}

  draw_line();

  return 0;
}
