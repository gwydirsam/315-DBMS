#include "engine.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "column.h"
#include "relation.h"

/* **********************************************************
   **********************************************************
   ******************** What's not done *********************

   //could do if i knew what format we were going to read in / write out
   int writeTable(std::string TableName);
   int closeTable(std::string TableName);

   **********************************************************
   **********************************************************
   ********************* IDK what to do *********************

   // Setters
   // Set Tuple
   //anything dealing with tuples is throwing me cause IDK what they are being
   used for at the moment.

   std::tuple table(std::string TableName, int id);
   int execDML(std::string DML);
   int exitDatabase();
   std::vector<std::tuple> select(std::string TableName,
   std::function<bool(std::Tuple)> function);
   std::vector<std::tuple> project(std::string TableName, std::vector<Attribute>
   attributes);
   std::vector<std::tuple> setunion(std::string TableName1, std::string
   TableName2);
   std::vector<std::tuple> setdifference(std::string TableName1, std::string
   TableName2);
   std::vector<std::tuple> setcrossproduct(std::string TableName1, std::string
   TableName2);

   **********************************************************
   **********************************************************
   **********************************************************
*/

// Returns std::end if NOTHING found
// Probably should throw an exception
std::vector<Relation>::iterator Engine::find_table(std::string TableName) {
  return std::find_if(std::begin(open_tables_), std::end(open_tables_),
                      [TableName](Relation relation)
                          -> bool { return relation.title() == TableName; });
}

int Engine::find_table_index(std::string TableName) {
  return std::distance(std::begin(open_tables_), find_table(TableName));
}

Relation Engine::get_table(std::string TableName) {
  return open_tables_.at(find_table_index(TableName));
}

void Engine::Table(std::string TableName, Relation Table) {
  open_tables_.at(find_table_index(TableName)) = Table;
}

int Engine::num_open_tables() { return (open_tables_.size() - 1); }

int Engine::openTable(std::string TableName) {
  std::string line;
  std::ifstream dbfile;
  dbfile.open(TableName.append(".db"));
  // Read into relation
  dbfile >> line;
  //
  Relation table;
  open_tables_.push_back(table);
  return (num_open_tables());
}

int Engine::showTable(std::string TableName) {
  int i = find_table_index(TableName);
  if (i != -1) {
    int num_com = open_tables_.at(i).columns().size();
    int num_entries = open_tables_.at(i).columns().at(0).entries().size();
    std::cout << "Contents of Table " << TableName << "\n";
    // Prints out columns
    for (int c = 0; c < num_com; c++) {
      std::cout << open_tables_.at(i).columns().at(c) << "\t";
    }
    std::cout << "\n";
    // Iterates through rows
    for (int r = 0; r < num_entries; r++) {
      // Iterates through columns to print row r.
      for (int c = 0; c < num_com; c++) {
        std::cout << open_tables_.at(i).columns().at(c).entries().at(r) << "\t";
      }
      std::cout << "\n";
    }
    // Success
    return 0;
  }
  // Couldn't find table
  return -1;
}

int Engine::showTable(Relation Table) { return showTable(Table.title()); }

Relation Engine::createNewTable(std::string TableName,
                                std::vector<Column<std::string> > columns) {
  Relation table(TableName, columns);
  writeTable(table);
  openTable(TableName);
  return table;
}

int Engine::insertTuple(std::string TableName, std::vector<std::string> tuple) {
  int i = find_table_index(TableName);
  if (i != -1) {
    if (open_tables_.at(i).columns().size() < tuple.size()) {
      // Error -3 tuple row is larger than number of columns
      return -3;
    } else if (open_tables_.at(i).columns().size() > tuple.size()) {
      // Error -4 tuple row is smaller than number of columns
      // This may be changed later where it adds the default value to the
      // columns with no value.
      return -4;
    } else {
      for (int c = 0; c < tuple.size(); c++) {
        open_tables_.at(i).columns().at(c).entries().push_back(tuple.at(c));
      }
      // Success
      return 0;
    }
  }
  // Couldn't find Table
  return -1;
}

// Fix for iterators
int Engine::dropTable(std::string TableName) {
  auto i = find_table(TableName);
  open_tables_.erase(i);
  // Success
  return 0;
}
int Engine::dropTable(Relation Table) { return dropTable(Table.title()); }

// TODO: Needs rewriting with OOP...this is too complex for what it is
int Engine::dropTuple(std::string TableName, std::vector<std::string> tuple) {
  int i = find_table_index(TableName);
  bool equal = false;

  int num_entries = open_tables_.at(i).num_rows();
  int num_com = open_tables_.at(i).num_cols();
  int r = 0;
  // iterates through rows
  while (r < num_entries) {
    int c = 0;
    // iterates through columns
    while (c < num_com) {
      if (tuple.at(c)
              .compare(open_tables_.at(i).columns().at(c).entries().at(r))) {
        c++;
        equal = true;
      } else {
        c = num_com;
        equal = false;
      }
    }
    if (equal) {
      int d = 0;
      // iterates through columns to delete entries in row r
      while (d < open_tables_.at(i).columns().size()) {
        open_tables_.at(i).columns().at(d).erase(r);
      }
      // Success
      return 0;
    }
    c++;
  }
  // Couldn't find the row to delete
  return -10;
}

void Engine::writeTable(Relation relation) {
  std::ofstream dbfile;
  dbfile.open(relation.title().append(".db"));
  // Writeattributes into relation

  // Columns separated by commas
  // End of Line denoted by "~*"
  // Line:
  // 0: relation.title()
  // 1: relation.attributes()
  // 2-infinity: relation.tuples()
  //
  // write this
}

// TODO: Does this need to delete old table file and make a new one??
// TODO: We can rename from C++ I believe
int Engine::rename_table(std::string TableName, std::string newname) {
  int i = find_table_index(TableName);
  open_tables_.at(i).title(newname);
  // Success
  return 0;
}

int Engine::rename_column(std::string TableName, std::string ColumnName,
                          std::string newname) {
  open_tables_.at(find_table_index(TableName))
      .rename_column(ColumnName, newname);
  return 0;
}
