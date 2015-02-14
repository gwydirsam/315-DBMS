#include "engine.h"

#include <iostream>
#include <fstream>

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

int Engine::find_table(std::string TableName) {
  int i = 0;
  while (i < open_tables_.size()) {
    if (TableName.compare(open_tables_.at(i).title())) return i;
    i++;
  }
  // Couldn't find Table
  return -1;
}

int Engine::find_column(std::string TableName, std::string ColumnName) {
  int i = find_table(TableName);
  if (i != -1) {
    int num_com = open_tables_.at(i).columns().size();
    int c = 0;
    while (c < num_com) {
      if (ColumnName.compare(open_tables_.at(i).columns().at(c).title())) {
        return c;
      }
      c++;
    }
    // Couldn't find Column
    return -2;
  }
  // Couldn't find Table
  return -1;
}

int Engine::find_column(Relation Table, std::string ColumnName) {
  int num_com = Table.columns().size();
  int c = 0;
  while (c < num_com) {
    if (ColumnName.compare(Table.columns().at(c).title())) {
      return c;
    }
    c++;
  }
  // Couldn't find Column
  return -2;
}

Relation Engine::get_table(std::string TableName) {
  int i = find_table(TableName);
  if (i != -1)
    return open_tables_.at(i);
  else {
    // Don't know how we want to handle not finding table
  }
}

void Engine::Table(std::string TableName, Relation Table) {
  int i = find_table(TableName);
  open_tables_.at(i) = Relation(Table);
}

int Engine::openTable(std::string TableName) {
  std::string line;
  std::ifstream dbfile;
  dbfile.open(TableName.append(".db"));
  // Read into relation
  dbfile >> line;
  //
  Relation table;
  open_tables_.push_back(table);
  return (open_tables_.size() - 1);
}

int Engine::showTable(std::string TableName) {
  int i = find_table(TableName);
  if (i != -1) {
    int num_com = open_tables_.at(i).columns().size();
    int num_entries = open_tables_.at(i).columns().at(0).entries().size();
    std::cout << "Contents of Table " << TableName << "\n";
    // Prints out columns
    for (int c = 0; c < num_com; c++) {
      std::cout << "" << open_tables_.at(i).columns().at(c) << "\t";
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
  int i = find_table(TableName);
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
        open_tables_.at(i).columns().at(c).entries().push_back(tuples.at(c));
      }
      // Success
      return 0;
    }
  }
  // Couldn't find Table
  return -1
}

int Engine::dropTable(std::string TableName) {
  int i = find_table(TableName);
  if (i != -1) {
    open_tables_.erase(i);
    // Success
    return 0;
  }
  // Couldn't find Table
  return -1;
}
int Engine::dropTable(Relation Table) { return dropTable(Table.title()); }

int Engine::dropTuple(std::string TableName, std::vector<std::string> tuple) {
  int i = find_table(TableName);
  bool equal = false;
  if (i != -1) {
    int num_entries = open_tables_.at(i).columns().at(0).entries().size();
    int num_com = open_tables_.at(i).columns().size();
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
          open_tables_.at(i).columns().at(d).entries().erase(r);
        }
        // Success
        return 0;
      }
      c++;
    }
    // Couldn't find the row to delete
    return -10;
  }
  // Couldn't find Table
  return -1;
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

// Does this need to delete old table file and make a new one???
int Engine::rename_table(std::string TableName, std::string newname) {
  int i = find_table(TableName);
  if (i != -1) {
    open_tables_.at(i).title(newname);
    // Success
    return 0;
  }
  // Couldn't find Table
  return -1;
}

int Engine::rename_column(std::string TableName, Column<std::string> Column,
                          std::string newname) {
  int i = find_table(TableName);
  if (i != -1) {
    int c = find_column(open_tables_.at(i), Column.title());
    if (c != -2) {
      open_tables_.at(i).columns().at(c).title(newname);
      // Success
      return 0;
    }
    // Couldn't find Column
    return -2;
  }
  // Couldn't find Table
  return -1;
}
