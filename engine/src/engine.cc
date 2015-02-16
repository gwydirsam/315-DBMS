#include "engine.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <functional>

#include "column.h"
#include "relation.h"

/* **********************************************************
   ******************** What's not done *********************

   **********************************************************
   ********************* IDK what to do *********************
   int exitDatabase();
*/

Relation Engine::find_relation(std::string TableName) {
  return open_tables_.at(find_table_index(TableName));
}

std::vector<std::string> Engine::list_open_tables() {
  std::vector<std::string> tables_list;

  for (const Relation& relation : open_tables_) {
    tables_list.push_back(relation.title());
  }

  return tables_list;
}

void Engine::print_list_open_tables() {
  std::cout << "{ ";
  for (const std::string& tablename : list_open_tables()) {
    std::cout << tablename << " ";
  }
  std::cout << "}";
}

// Returns std::end if NOTHING found
std::vector<Relation>::iterator Engine::find_table(std::string TableName) {
  return std::find_if(std::begin(open_tables_), std::end(open_tables_),
                      [TableName](Relation relation)
                          -> bool { return relation.title() == TableName; });
}

int Engine::find_table_index(std::string TableName) {
  if (find_table(TableName) == std::end(open_tables_)) {
    // Return failure
    return -1;
  } else {
    return std::distance(std::begin(open_tables_), find_table(TableName));
  }
}

int Engine::find_tuple_index(std::string TableName,
                             std::vector<std::string> tuple) {
  int i = find_table_index(TableName);
  if (i != -1) {
    std::vector<Column<std::string>> columns = open_tables_.at(i).columns();
    bool equal = false;
    int num_entries = columns.at(0).size();
    int num_com = columns.size();
    int r = 0;
    // iterates through rows
    while (r < num_entries) {
      int c = 0;
      // iterates through columns
      while (c < num_com) {
        if (tuple.at(c).compare(columns.at(c).entries().at(r))) {
          c++;
          equal = true;
        } else {
          c = num_com;
          equal = false;
        }
      }
      if (equal) {
        return r;
      }
    }
    // Could't find Tuple
    return -7;
  }
  // Could'nt find Table
  return -1;
}

Relation Engine::get_table(std::string TableName) {
  return open_tables_.at(find_table_index(TableName));
}

void Engine::Table(std::string TableName, Relation Table) {
  open_tables_.at(find_table_index(TableName)) = Table;
}

int Engine::num_open_tables() { return open_tables_.size(); }

int Engine::openTable(std::string TableName) {
  std::string line;
  std::string title_;
  std::vector<Column<std::string>> columns_;
  bool end_of_line = false;
  bool end_of_file = false;
  std::ifstream dbfile(TableName.append(".db"), std::ios::in);
  // Reads table's title
  dbfile >> title_;
  // Reads in Column Names
  while (!end_of_line) {
    dbfile >> line;
    // Detects end of ColumnName
    if (line == ",") {
      // do nothing
    } else if (line == "~$EOF") {
      end_of_file = true;
      end_of_line = true;
    }
    // Detects EOL
    else if (line == "~$EOL") {
      end_of_line = true;
    }
    // Detects if primary key
    else if (line == "~^") {
      dbfile >> line;
      Column<std::string> column(line, "string", true);
      columns_.push_back(column);
    }
    // Normal Column
    else {
      Column<std::string> column(line, "string", false);
      columns_.push_back(column);
    }
  }
  // Detects EOF
  if (line == "~$EOF") {
    end_of_file = true;
  }

  // Reads in entries TIL EOF
  while (!end_of_file) {
    end_of_line = false;
    int c = 0;
    while (!end_of_line) {
      dbfile >> line;

      // Detects EOF
      if (line == "~$EOF") {
        end_of_file = true;
        end_of_line = true;
      }
      // Detects EOL
      else if (line == "~$EOL") {
        end_of_line = true;
      }
      // Detects end of entry
      else if (line == ",") {
        // do nothing
      } else {
        columns_.at(c).insert_entry(line);
        c++;
      }
    }
  }
  // Adds table to vector of open tables
  Relation table(title_, columns_);
  open_tables_.push_back(table);
  return (num_open_tables());

  // Lines:
  // 0: relation.title()
  // Columns separated by commas
  // End of Line (EOL) denoted by "~$EOL" this is used only on column and
  // entries row
  // if a column is a primary key denoted with "~^ ColumnName"
  // 1: relation.columns()
  // 2-infinity: columns.entries()
  // EOF denoted with "~$EOF"
  // write this
}

int Engine::showTable(std::string TableName) {
  int i = find_table_index(TableName);
  if (i == -1) {
    // Return Failure
    return -1;
  } else {
    int num_com = open_tables_.at(i).num_cols();
    int num_entries = open_tables_.at(i).num_rows();
#ifdef DEBUG
    std::cout << std::endl;
    std::cout << "Relation Title: " << TableName << std::endl;
    std::cout << "Number of Columns: " << num_com << std::endl;
    std::cout << "Number of Rows: " << num_entries << std::endl;
    std::cout << std::endl;
#endif

    std::cout << "Contents of Table: " << TableName << " (" << num_com << " x "
              << num_entries << ")" << std::endl;

    // Prints out column titles
    for (int c = 0; c < num_com; ++c) {
      std::cout << open_tables_.at(i).columns().at(c).title() << "\t";
    }
    std::cout << std::endl;

    // Iterates through rows
    for (int r = 0; r < num_entries; ++r) {
      // Iterates through columns to print row r.
      open_tables_.at(i).print_row(r);
      if (r != (num_entries - 1)) std::cout << std::endl;
    }

    // Success
    return 0;
  }
}

int Engine::showTable(Relation Table) { return showTable(Table.title()); }

Relation Engine::createNewTable(std::string TableName,
                                std::vector<Column<std::string>> columns) {
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
      for (unsigned int c = 0; c < tuple.size(); c++) {
        open_tables_.at(i).columns().at(c).entries().push_back(tuple.at(c));
      }
      // Success
      return 0;
    }
  }
  // Couldn't find Table
  return -1;
}

int Engine::dropTable(std::string TableName) {
  // Right now this is the only way i know how to handle if the Table isn't
  // found.
  int i = find_table_index(TableName);
  if (i != -1) {
    open_tables_.erase(find_table(TableName) - 1);
    // Success
    return 0;
  }
  // Couldn't find Table
  return -1;
}
int Engine::dropTable(Relation Table) { return dropTable(Table.title()); }

// TODO: Needs rewriting with OOP...this is too complex for what it is
int Engine::dropTuple(std::string TableName, std::vector<std::string> tuple) {
  int r = find_tuple_index(TableName, tuple);
  int i = find_table_index(TableName);
  if (r != -7 && r != -1 && i != -1) {
    unsigned int d = 0;
    // iterates through columns to delete entries in row r
    while (d < open_tables_.at(i).columns().size()) {
      open_tables_.at(i).columns().at(d).entries().erase(
          open_tables_.at(i).columns().at(d).entries().begin() + r - 1);
      d++;
    }
    // Success
    return 0;
  }
  // Couldn't find the tuple or table
  return r;
}

void Engine::writeTable(Relation relation) {
  std::ofstream dbfile(relation.title().append(".db"), std::ios::out);
  // Lines:
  // 0: relation.title()
  // Columns separated by commas
  // End of Line (EOL) denoted by "~$EOL" this is used only on column and
  // entries row
  // if a column is a primary key denoted with "~^ ColumnName"
  // 1: relation.columns()
  // 2-infinity: columns.entries()
  // EOF denoted with "~$EOF"
  // write this

  // Writes TableName to file.
  dbfile << relation.title() << "\n";

  // Writing columns to file
  if (relation.columns().size() != 0) {
    for (unsigned int c = 0; c < relation.columns().size(); c++) {
      if (relation.columns().at(c).primary_key()) {
        dbfile << "~^ ";
      }
      dbfile << relation.columns().at(c).title() << " , ";
    }
    dbfile << "~$EOL \n";
  }
  // Writing entries to file.
  if (relation.columns().at(0).entries().size() != 0) {
    for (unsigned int r = 0; r < relation.columns().at(0).entries().size();
         r++) {
      for (unsigned int c = 0; c < relation.columns().size(); c++) {
        dbfile << relation.columns().at(c).entries().at(r);
        dbfile << " , ";
      }
      dbfile << "~$EOL \n";
    }
  }
  dbfile << "~$EOF";
  dbfile.close();
}

int Engine::closeTable(std::string TableName) {
  int i = find_table_index(TableName);
  writeTable(open_tables_.at(i));
  int d = dropTable(TableName);

  return d;
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
  // Success
  return 0;
}

bool Engine::unioncompatible(std::string TableName1, std::string TableName2) {
  Relation table1 = find_relation(TableName1);
  Relation table2 = find_relation(TableName2);

  if ((table1.get_column_titles() == table2.get_column_titles()) &&
      (table1.get_column_types() == table2.get_column_types())) {
    return true;
  } else {
    return false;
  }
}

Relation Engine::project(std::vector<std::string> ColumnNames,
                         std::string TableName) {
  Relation table = find_relation(TableName);
  if (ColumnNames.size() == 0) {
    // Return Empty Relation
    return Relation(TableName);
  } else {
    std::vector<int> column_indexes;
    // Select ColumnNames from TableName
    for (const std::string& column_name : ColumnNames) {
      // Get indexes of columns requested
      column_indexes.push_back(table.find_column_index(column_name));
    }
    // Build new relation from column_indexes
    std::vector<Column<std::string>> selectcolumns;
    for (int i = 0; i < column_indexes.size(); ++i) {
      selectcolumns.push_back(table.get_column(column_indexes[i]));
    }
    return Relation(TableName, selectcolumns);
  }
}

Relation Engine::setunion(std::string TableName1, std::string TableName2) {
  if (!unioncompatible(TableName1, TableName2)) {
    // Return invalid relation
    return Relation();
  } else {
    Relation table1 = find_relation(TableName1);
    Relation table2 = find_relation(TableName2);
    std::vector<Column<std::string>> unioncolumns;
    for (Column<std::string> column : table1.columns()) {
      unioncolumns.push_back(column);
    }
    // not done
    // for(Column<std::string> column : table2.columns()) {
    //  unioncolumns.push_back(column);
    //}
    return Relation("UnionTable", unioncolumns);
  }
}

Relation Engine::setdifference(std::string TableName1, std::string TableName2) {
  if (!unioncompatible(TableName1, TableName2)) {
    // Return invalid relation
    return Relation();
  } else {
    find_relation(TableName1);
    find_relation(TableName2);
  }
}

Relation Engine::setcrossproduct(std::string TableName1,
                                 std::string TableName2) {}

Relation Engine::select(std::vector<std::string> ColumnNames,
                        std::string TableName) {
  Relation table = find_relation(TableName);
  Relation selectTable;
  if (ColumnNames.size() == 0) {
    // table is whole table from TableName
    selectTable = table;
  } else {
    std::vector<int> column_indexes;
    // Select ColumnNames from TableName
    for (const std::string& column_name : ColumnNames) {
      // Get indexes of columns requested
      column_indexes.push_back(table.find_column_index(column_name));
    }
    // Build new relation from column_indexes
    std::vector<Column<std::string>> selectcolumns;
    for (int i = 0; i < column_indexes.size(); ++i) {
      selectcolumns.push_back(table.get_column(column_indexes[i]));
    }
    selectTable = Relation(TableName, selectcolumns);
  }
  return selectTable;
}

Relation Engine::select(std::vector<std::string> ColumnNames,
                        std::string TableName, std::string WhereColumn,
                        std::string WhereEqual) {
  Relation table = find_relation(TableName);
  Relation selectTable;

  if (ColumnNames.size() == 0) {
    // table is whole table from TableName
    selectTable = table;
  } else {
    std::vector<int> column_indexes;
    // Select ColumnNames from TableName
    for (const std::string& column_name : ColumnNames) {
      // Get indexes of columns requested
      column_indexes.push_back(table.find_column_index(column_name));
    }
    // Build new relation from column_indexes
    std::vector<Column<std::string>> selectcolumns;
    for (int i = 0; i < column_indexes.size(); ++i) {
      selectcolumns.push_back(table.get_column(column_indexes[i]));
    }
    selectTable = Relation(TableName, selectcolumns);
  }
  // Now process where clause
  for (int i = (selectTable.num_rows() - 1); i >= 0; --i) {
    std::vector<std::string> current_row = table.get_row(i);
    // if where clause fails, drop row
    // std::cout << current_row[selectTable.find_column_index(WhereColumn)] <<
    // std::endl;
    if (current_row[table.find_column_index(WhereColumn)] != WhereEqual) {
      selectTable.drop_row(i);
    }
  }
  return selectTable;
}
