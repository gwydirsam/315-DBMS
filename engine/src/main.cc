// Rabia Gunonu, Sam Gwydir, Nicolas Juarez, Daniel Koon
// CSCE 315-503
// main.cc

#include <iostream>
#include "engine.h"
#include "column.h"

void draw_line() {
  // Draw 80 line characters
  for(int i = 0; i < 80; ++i) {
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
  std::vector<Column<std::string> > columns;
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
  columns.push_back(first_col);
  columns.push_back(second_col);

  db.createNewTable("Test0", columns);
  db.createNewTable("Test1", columns);
  db.createNewTable("Test2", columns);

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

  std::cout << "Test1 Table Index: " << db.find_table_index("Test1")
            << std::endl;
  db.showTable("Test1");
  std::cout << std::endl;

  std::cout << "Test2 Table Index: " << db.find_table_index("Test2")
            << std::endl;
  db.showTable("Test2");
  std::cout << std::endl;
  draw_line();

  return 0;
}
