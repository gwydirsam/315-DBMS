// Rabia Gunonu, Sam Gwydir, Nicolas Juarez, Daniel Koon
// CSCE 315-503
// main.cc

#include <iostream>
#include "engine.h"
#include "column.h"

int main(int argc, char *argv[]) {
  std::cout << "This is the Database Engine" << std::endl;
  Engine db;
  // Column<std::string> column("ID");
  std::vector<Column<std::string> > columns;
  columns.push_back(Column<std::string>("ID"));
  db.createNewTable("Test", columns);
  std::cout << "Number of Open Tables: " << db.num_open_tables() << std::endl;
  std::cout << "Test Table Index: " << db.find_table_index("Test") << std::endl;
  std::cout << "Unknown Table Index(Should be -1): "
            << db.find_table_index("Unknown") << std::endl;

  return 0;
}
