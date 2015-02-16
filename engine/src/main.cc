// Rabia Gunonu, Sam Gwydir, Nicolas Juarez, Daniel Koon
// CSCE 315-503
// main.cc

#include <iostream>
#include "engine.h"
#include "column.h"
#include "relation.h"

void draw_line() {
  // Draw 80 line characters
  for (int i = 0; i < 80; ++i) {
    std::cout << "─";
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  draw_line();
  std::cout << "Database Engine" << std::endl;
  draw_line();
  Engine db;

  // Column<std::string> column("Name");
  std::vector<Column<std::string> > columns0;
  std::vector<Column<std::string> > columns1;
  std::vector<Column<std::string> > columns2;

  Column<std::string> first_col("Scrooge");
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

  columns0.push_back(first_col);
  columns0.push_back(second_col);

  columns1.push_back(third_col);
  columns1.push_back(fourth_col);

  columns2.push_back(first_col);
  columns2.push_back(fourth_col);

  db.createNewTable("Test0", columns0);
  db.createNewTable("Test1", columns1);
  db.createNewTable("Test2", columns2);

  std::cout << "Number of Open Tables: " << db.num_open_tables() << std::endl;

  std::cout << "List of Open Tables: ";
  db.print_list_open_tables();
  std::cout << std::endl;
  draw_line();

  std::cout << "Unknown Table Index(Should be -1): "
            << db.find_table_index("Unknown") << std::endl;
  draw_line();

  std::cout << "Test0 Table Index: " << db.find_table_index("Test0")
            << std::endl;
  db.showTable("Test0");
  std::cout << std::endl;
  draw_line();

  std::cout << "Test1 Table Index: " << db.find_table_index("Test1")
            << std::endl;
  db.showTable("Test1");
  std::cout << std::endl;
  draw_line();

  std::cout << "Test2 Table Index: " << db.find_table_index("Test2")
            << std::endl;
  db.showTable("Test2");
  std::cout << std::endl;
  draw_line();

  std::cout << "Select * From Test0" << std::endl;
  std::cout << db.select({}, "Test0") << std::endl;
  draw_line();

  std::cout << "Select Money From Test1 where Money == Money2" << std::endl;
  std::cout << db.select({"Money"}, "Test1", "Money", "Money2") << std::endl;
  draw_line();

  std::cout << "Select Money From Test2 where Scrooge == bar" << std::endl;
  std::cout << db.select({"Money"}, "Test2", "Scrooge", "bar") << std::endl;
  draw_line();

  std::cout << "Project Scrooge From Test0" << std::endl;
  std::cout << db.project({"Scrooge"}, "Test0") << std::endl;
  draw_line();

  std::cout << "Test0 Union Test1" << std::endl;
  std::cout << db.setunion("Test0", "Test1") << std::endl;
  draw_line();

  // std::cout << "Test0 Union Test2" << std::endl;
  // draw_line();

  // std::cout << "Test1 Union Test0" << std::endl;
  // draw_line();

  // std::cout << "Test1 Union Test2" << std::endl;
  // draw_line();

  // std::cout << "Test2 Union Test0" << std::endl;
  // draw_line();

  // std::cout << "Test2 Union Test1" << std::endl;
  // draw_line();

  return 0;
}
