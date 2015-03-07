#include "engine.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "column.h"
#include "relation.h"
#include "utility.h"
#include "grammar.h"
#include "grammar_objects.h"

Engine::Engine() {
  boost::filesystem::path tabledir(boost::filesystem::absolute("tables"));
  if (boost::filesystem::exists(tabledir)) {
    errlog("Engine: Tables Directory Exists");
  } else {
    errlog("Engine: Creating Tables Directory");
    // boost::filesystem::absolute(tabledir);
    boost::filesystem::create_directory(tabledir);
  }
  errlog("Engine: Creating New Engine");
}

Engine::~Engine() {
  errlog("Engine: Shutting Down Database Engine");
  exitEngine();
}

void Engine::exitEngine() {
  errlog("Engine: Writing all open tables to disk");
  for (const Relation& relation : open_tables_) {
    std::string errstring = "Engine: Writing " + relation.title() + ".db";
    errlog(errstring);
    writeTable(relation);
  }
  errlog("Engine: Done writing tables to disk");
  endlog();
}

Relation& Engine::find_relation_or_view(std::string TableName) {
  if (find_table_index(TableName) == -1) {
    // no open table found.
    std::string errmsg = "Engine: Table " + TableName + " Not Found";
    errlog(errmsg);
  } else {
    return find_relation(TableName);
  }
  if (find_view_index(TableName) == -1) {
    // no open table found.
    std::string errmsg = "Engine: View " + TableName + " Not Found";
    errlog(errmsg);
  } else {
    return find_view(TableName);
  }
}

Relation& Engine::find_relation(std::string TableName) {
  return open_tables_.at(find_table_index(TableName));
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

Relation& Engine::find_view(std::string TableName) {
  return open_views_.at(find_view_index(TableName));
}

// Returns std::end if NOTHING found
std::vector<Relation>::iterator Engine::find_view_table(std::string TableName) {
  return std::find_if(std::begin(open_views_), std::end(open_views_),
                      [TableName](Relation relation)
                          -> bool { return relation.title() == TableName; });
}

int Engine::find_view_index(std::string TableName) {
  if (find_view_table(TableName) == std::end(open_views_)) {
    // Return failure
    return -1;
  } else {
    return std::distance(std::begin(open_views_), find_view_table(TableName));
  }
}

int Engine::find_tuple_index(std::string TableName,
                             std::vector<std::string> tuple) {
  int i = find_table_index(TableName);
  if (i != -1) {
    std::vector<Column<std::string>> columns = open_tables_.at(i).columns();
    bool equal = false;
    int num_entries = (int)columns.at(0).size();
    int num_com = (int)columns.size();
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

std::vector<std::string> Engine::list_open_tables() {
  std::vector<std::string> tables_list;

  for (const Relation& relation : open_tables_) {
    tables_list.push_back(relation.title());
  }

  return tables_list;
}

int Engine::num_open_tables() { return (int)open_tables_.size(); }

void Engine::print_list_open_tables() {
  std::cout << "{ ";
  for (const std::string& tablename : list_open_tables()) {
    std::cout << tablename << " ";
  }
  std::cout << "}";
}

void Engine::set_table(std::string TableName, Relation Table) {
  open_tables_.at(find_table_index(TableName)) = Table;
}

int Engine::openTable(std::string TableName) {
  std::string directory = "tables/";
  std::string filename = TableName.append(".db");
  std::string filepath = directory + filename;

  // Open filepath
  std::ifstream dbfile(filepath, std::ios::in);

  // If file doesn't exist return -1
  if (!dbfile.good()) {
    std::string errmsg =
        "openTable: File Doesn't Exist (Probably need to create the "
        "directory): " +
        filepath;
    errlog(errmsg);
    return -1;
  }

  // Create Table
  Relation table;

  // Create table by reading in file
  dbfile >> table;

  // Adds table to vector of open tables
  open_tables_.push_back(table);
  return (num_open_tables());
}

Relation Engine::createNewTable(std::string TableName,
                                std::vector<Column<std::string>> columns) {
  Relation table(TableName, columns);
  writeTable(table);
  openTable(TableName);
  return table;
}

Relation Engine::createNewTable(std::string TableName,
                                std::vector<std::string> typed_attribute_list,
                                std::vector<std::string> primary_keys) {
  std::vector<Column<std::string>> columns;

  // create columns
  // we skip the types
  for (unsigned int i = 0; i < typed_attribute_list.size(); i += 2) {
    columns.push_back(Column<std::string>(typed_attribute_list[i]));
  }
  // set primary keys
  for (Column<std::string>& col : columns) {
    for (std::string key_title : primary_keys) {
      if (col.title() == key_title) {
        std::string errstr = "Found Primary Key: " + key_title;
        errlog(errstr);
        col.primary_key(true);
      }
    }
  }

  // call normal createNewTable
  return createNewTable(TableName, columns);
}

Relation Engine::updateTable(std::string TableName,
                             std::vector<std::string> attribute_value_list,
                             std::vector<std::string> condition) {
  Relation relation = find_relation_or_view(TableName);
  // do stuff
  return relation;
}

int Engine::insertTuple(Relation& relation, std::vector<std::string> tuple) {
  if (relation.num_cols() < (int)tuple.size()) {
    // Error -3 tuple row is larger than number of columns
    return -3;
  } else if (relation.num_cols() > (int)tuple.size()) {
    // Error -4 tuple row is smaller than number of columns
    // This may be changed later where it adds the default value to the
    // columns with no value.
    return -4;
  } else {
    relation.append_row(tuple);
    // Success
    return 0;
  }
}

int Engine::insertTuple(std::string TableName, std::vector<std::string> tuple) {
  return insertTuple(find_relation_or_view(TableName), tuple);
}

int Engine::insertTuple(std::string TableName, Relation relation) {
  for (int i = 0; i < relation.num_rows(); ++i) {
    if ((insertTuple(find_relation_or_view(TableName), relation.get_row(i))) ==
        -1) {
      return -1;
    }
  }
  return 0;
}

int Engine::dropTable(std::string TableName) {
  return dropTable(find_relation(TableName));
}

int Engine::dropTable(Relation Table) {
  if ((find_table_index(Table.title())) == -1) {
    // Couldn't find Table
    return -1;
  } else {
    // Found Table
    open_tables_.erase(find_table(Table.title()));
    return 0;
  }
}

int Engine::deleteFrom(Relation& Table, std::vector<std::string> Conditions) {
#ifdef DEBUG
  std::cerr << Table << std::endl;
#endif

  if ((int)Conditions.size() == 0) {
    // don't delete anything
    // also log this.
    std::string errstring =
        "Engine: Delete From: " + Table.title() + " had no conditions";
    errlog(errstring);
    return 0;
  } else {
    // Break down conditions
    std::vector<std::string> column_names;
    std::vector<std::string> literals;
    std::vector<std::string> ops;
    for (unsigned int i = 0; i < Conditions.size(); ++i) {
      if ((Conditions[i] == "OR") || (Conditions[i] == "AND") ||
          (Conditions[i] == "==") || (Conditions[i] == "!=") ||
          (Conditions[i] == "<") || (Conditions[i] == ">") ||
          (Conditions[i] == "<=") || (Conditions[i] == ">=")) {
        ops.push_back(Conditions[i]);
      } else {
        column_names.push_back(Conditions[i]);
        // column names are followed by a literal
        literals.push_back(Conditions[++i]);
      }
    }
    std::string errmsg = "Engine: Delete From Column Names : ";
    for (std::string str : column_names) {
      errmsg += str + " ";
    }
    errlog(errmsg);
    errmsg = "Engine: Delete From Condition Ops : ";
    for (std::string str : ops) {
      errmsg += str + " ";
    }
    errlog(errmsg);
    errmsg = "Engine: Delete From Condition Literals : ";
    for (std::string str : literals) {
      errmsg += str + " ";
    }
    errlog(errmsg);

    std::vector<int> column_indexes;
    // Delete From Conditions from relation
    for (std::string column_name : column_names) {
      // Get indexes of columns requested
      int i = (Table.find_column_index(column_name));
      if (i >= 0) {
        column_indexes.emplace_back(i);
      }
    }
    errmsg = "Engine: Delete From Column Indexes : ";
    for (int i : column_indexes) {
      errmsg += std::to_string(i) + " ";
    }
    errlog(errmsg);

    // Add empty columns from table
    std::vector<Column<std::string>> selectcolumns;
    for (Column<std::string> col : Table.columns()) {
      selectcolumns.push_back(
          Column<std::string>(col.title(), col.type(), col.primary_key()));
    }

    // Now process conditions
    for (int i : column_indexes) {
      for (int j = 0; j < Table.num_rows(); ++j) {
        std::string errmsg = "Engine: Delete From: Table.num_rows() = " +
                             std::to_string(Table.num_rows());
        errlog(errmsg);
        std::vector<std::string> current_row = Table.get_row(j);
        for (unsigned int k = (ops.size() - 1); k > (ops.size() - literals.size());
             --k) {
          std::string errstr = "Engine: Delete From: Conditions Loop: i=" +
                               std::to_string(i) + " j=" + std::to_string(j) +
                               " k=" + std::to_string(k);
          errlog(errstr);
          errstr = "Engine: Delete From: Performing: " + current_row[i] + " " +
                   ops[k] + " " + literals[(ops.size() - 1) - k];
          errlog(errstr);
          // need to fix these maybe with lexical_cast
          // if (ops[i] == "OR") {
          //   if (current_row[i] || literals[k - 2]) {
          //     selectTable.append_row(current_row);
          //   }
          // } else if (ops[i] == "AND") {
          //   if (current_row[i] && literals[k - 2]) {
          //     selectTable.append_row(current_row);
          //   }
          // } else
          if (ops[k] == "==") {
            if (current_row[i] == literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Dropping row.");
              // j----, drop row j--, then decrement, because theyre is one less
              // row.
              Table.drop_row(j--);
#ifdef DEBUG
              std::cout << std::endl << Table << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not dropping row.");
            }
          } else if (ops[k] == "!=") {
            if (current_row[i] != literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Dropping row.");
              Table.drop_row(j--);
#ifdef DEBUG
              std::cout << std::endl << Table << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not dropping row.");
            }
          } else if (ops[k] == "<") {
            if (current_row[i] < literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Dropping row.");
              Table.drop_row(j--);
#ifdef DEBUG
              std::cout << std::endl << Table << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not dropping row.");
            }
          } else if (ops[k] == ">") {
            if (current_row[i] > literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Dropping row.");
              Table.drop_row(j--);
#ifdef DEBUG
              std::cout << std::endl << Table << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not dropping row.");
            }
          } else if (ops[k] == "<=") {
            if (current_row[i] <= literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Dropping row.");
              Table.drop_row(j--);
#ifdef DEBUG
              std::cout << std::endl << Table << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not dropping row.");
            }
          } else if (ops[k] == ">=") {
            if (current_row[i] >= literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Dropping row.");
              Table.drop_row(j--);
#ifdef DEBUG
              std::cout << std::endl << Table << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not dropping row.");
            }
          } else {
            std::string errmsg = "Engine: Delete From: Illegal Op: " + ops[k];
            errlog(errmsg);
#ifdef DEBUG
            std::cout << std::endl << Table << std::endl;
#endif
          }
        }
      }
    }
#ifdef DEBUG
    std::cout << std::endl << Table << std::endl;
#endif
  }

  return 0;
}

int Engine::deleteFrom(std::string TableName,
                       std::vector<std::string> Conditions) {
  return deleteFrom(find_relation_or_view(TableName), Conditions);
}

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

int Engine::execSQL(std::string input_string) {
  std::string errstr = "Engine execSQL: " + input_string;
  errlog(errstr);
  Program program = parse_string(input_string);
  std::cout << program << std::endl;
  std::cout << std::endl;

  // execute
  execute_program(*this, program);

#ifdef DEBUG
  errstr = "Engine: execSQL: Open Tables (" +
           std::to_string(open_tables_.size()) + "): ";
  errlog(errstr);
  for (Relation table : open_tables_) {
    std::cerr << table << std::endl;
  }
  errstr = "Engine: execSQL: Open Views (" +
           std::to_string(open_views_.size()) + "): ";
  errlog(errstr);
  for (Relation table : open_views_) {
    std::cerr << table << std::endl;
  }
#endif
  errstr = "Engine execSQL Finished: " + input_string;
  errlog(errstr);
  endlog();

  return 0;
}

void Engine::writeTable(Relation relation) {
  // Create filepath
  std::string directory = "tables/";
  std::string filename = relation.title() + ".db";
  std::string filepath = directory + filename;

  // Open filepath
  std::ofstream dbfile(filepath, std::ios::out);

  // Write relation to dbfile
  dbfile << relation;

  dbfile.close();
}

void Engine::addView(Relation relation) { open_views_.push_back(relation); }

int Engine::closeTable(Relation relation) {
  std::string errstr = "Engine: Close Table: " + relation.title();
  errlog(errstr);

  writeTable(relation);
  return dropTable(relation);
}

int Engine::closeTable(std::string TableName) {
  return closeTable(find_relation(TableName));
}

Relation Engine::rename_table(Relation table, std::string newname) {
  table.title(newname);
  return table;
}

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

Relation Engine::rename_column(Relation relation, std::string ColumnName,
                               std::string newname) {
  relation.rename_column(ColumnName, newname);
  // Success
  return relation;
}

Relation Engine::select(std::vector<std::string> Conditions,
                        Relation relation) {
  Relation table(relation);
#ifdef DEBUG
  std::cerr << table << std::endl;
#endif

  if ((int)Conditions.size() == 0) {
    // table is whole table from relation
    return (Relation((table.title() + "-Select"), table.columns()));
  } else {
    // Break down conditions
    std::vector<std::string> column_names;
    std::vector<std::string> literals;
    std::vector<std::string> ops;
    for (unsigned int i = 0; i < Conditions.size(); ++i) {
      if ((Conditions[i] == "OR") || (Conditions[i] == "AND") ||
          (Conditions[i] == "==") || (Conditions[i] == "!=") ||
          (Conditions[i] == "<") || (Conditions[i] == ">") ||
          (Conditions[i] == "<=") || (Conditions[i] == ">=")) {
        ops.push_back(Conditions[i]);
      } else {
        column_names.push_back(Conditions[i]);
        // column names are followed by a literal
        literals.push_back(Conditions[++i]);
      }
    }
    std::string errmsg = "Engine: Select Column Names : ";
    for (std::string str : column_names) {
      errmsg += str + " ";
    }
    errlog(errmsg);
    errmsg = "Engine: Select Condition Ops : ";
    for (std::string str : ops) {
      errmsg += str + " ";
    }
    errlog(errmsg);
    errmsg = "Engine: Select Condition Literals : ";
    for (std::string str : literals) {
      errmsg += str + " ";
    }
    errlog(errmsg);

    std::vector<int> column_indexes;
    // Select Conditions from relation
    for (std::string column_name : column_names) {
      // Get indexes of columns requested
      int i = (table.find_column_index(column_name));
      if (i >= 0) {
        column_indexes.emplace_back(i);
      }
    }
    errmsg = "Engine: Select Column Indexes : ";
    for (int i : column_indexes) {
      errmsg += std::to_string(i) + " ";
    }
    errlog(errmsg);

    // Add empty columns from table
    std::vector<Column<std::string>> selectcolumns;
    for (Column<std::string> col : table.columns()) {
      selectcolumns.push_back(
          Column<std::string>(col.title(), col.type(), col.primary_key()));
    }

    Relation selectTable(table.title() + "-Select", selectcolumns);
    // Now process conditions
    for (int i : column_indexes) {
      for (int j = 0; j < table.num_rows(); ++j) {
        std::string errmsg = "Engine: Select: table.num_rows() = " +
                             std::to_string(table.num_rows());
        errlog(errmsg);
        std::vector<std::string> current_row = table.get_row(j);
        for (unsigned int k = (ops.size() - 1); k > (ops.size() - literals.size());
             --k) {
          std::string errstr = "Engine: Select: Conditions Loop: i=" +
                               std::to_string(i) + " j=" + std::to_string(j) +
                               " k=" + std::to_string(k);
          errlog(errstr);
          errstr = "Engine: Select: Performing: " + current_row[i] + " " +
                   ops[k] + " " + literals[(ops.size() - 1) - k];
          errlog(errstr);
          // need to fix these maybe with lexical_cast
          // if (ops[i] == "OR") {
          //   if (current_row[i] || literals[k - 2]) {
          //     selectTable.append_row(current_row);
          //   }
          // } else if (ops[i] == "AND") {
          //   if (current_row[i] && literals[k - 2]) {
          //     selectTable.append_row(current_row);
          //   }
          // } else
          if (ops[k] == "==") {
            if (current_row[i] == literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Appending row.");
              selectTable.append_row(current_row);
#ifdef DEBUG
              std::cout << std::endl << selectTable << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not appending row.");
            }
          } else if (ops[k] == "!=") {
            if (current_row[i] != literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Appending row.");
              selectTable.append_row(current_row);
#ifdef DEBUG
              std::cout << std::endl << selectTable << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not appending row.");
            }
          } else if (ops[k] == "<") {
            if (current_row[i] < literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Appending row.");
              selectTable.append_row(current_row);
#ifdef DEBUG
              std::cout << std::endl << selectTable << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not appending row.");
            }
          } else if (ops[k] == ">") {
            if (current_row[i] > literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Appending row.");
              selectTable.append_row(current_row);
#ifdef DEBUG
              std::cout << std::endl << selectTable << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not appending row.");
            }
          } else if (ops[k] == "<=") {
            if (current_row[i] <= literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Appending row.");
              selectTable.append_row(current_row);
#ifdef DEBUG
              std::cout << std::endl << selectTable << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not appending row.");
            }
          } else if (ops[k] == ">=") {
            if (current_row[i] >= literals[(ops.size() - 1) - k]) {
              errlog("Condition returned true. Appending row.");
              selectTable.append_row(current_row);
#ifdef DEBUG
              std::cout << std::endl << selectTable << std::endl;
#endif
            } else {
              errlog("Condition returned false. Not appending row.");
            }
          } else {
            std::string errmsg = "Engine: Select: Illegal Op: " + ops[k];
            errlog(errmsg);
#ifdef DEBUG
            std::cout << std::endl << selectTable << std::endl;
#endif
          }
        }
      }
    }
    return selectTable;
  }
}

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
    for (int i = 0; i < (int)column_indexes.size(); ++i) {
      selectcolumns.push_back(table.get_column(column_indexes[i]));
    }
    selectTable = Relation(TableName, selectcolumns);
  }
  return selectTable;
}

// Relation Engine::select(std::vector<std::string> ColumnNames,
//                         Relation relation) {
//   Relation table = relation;
//   Relation selectTable;
//   if (ColumnNames.size() == 0) {
//     // table is whole table from relation
//     selectTable = table;
//   } else {
//     std::vector<int> column_indexes;
//     // Select ColumnNames from relation
//     for (const std::string& column_name : ColumnNames) {
//       // Get indexes of columns requested
//       column_indexes.push_back(table.find_column_index(column_name));
//     }
//     // Build new relation from column_indexes
//     std::vector<Column<std::string>> selectcolumns;
//     for (int i = 0; i < (int)column_indexes.size(); ++i) {
//       selectcolumns.push_back(table.get_column(column_indexes[i]));
//     }
//     selectTable = Relation(table.title(), selectcolumns);
//   }
//   return selectTable;
// }

Relation Engine::select(std::vector<std::string> ColumnNames,
                        std::string TableName, std::string WhereColumn,
                        std::string WhereEqual) {
  Relation table = find_relation(TableName);
  Relation selectTable;

  if ((int)ColumnNames.size() == 0) {
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
    for (int i = 0; i < (int)column_indexes.size(); ++i) {
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

Relation Engine::select(std::vector<std::string> ColumnNames, Relation relation,
                        std::string WhereColumn, std::string WhereEqual) {
  Relation table = relation;
  Relation selectTable;

  if ((int)ColumnNames.size() == 0) {
    // table is whole table from relation
    selectTable = table;
  } else {
    std::vector<int> column_indexes;
    // Select ColumnNames from relation
    for (const std::string& column_name : ColumnNames) {
      // Get indexes of columns requested
      column_indexes.push_back(table.find_column_index(column_name));
    }
    // Build new relation from column_indexes
    std::vector<Column<std::string>> selectcolumns;
    for (int i = 0; i < (int)column_indexes.size(); ++i) {
      selectcolumns.push_back(table.get_column(column_indexes[i]));
    }
    selectTable = Relation(table.title(), selectcolumns);
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

Relation Engine::project(std::vector<std::string> ColumnNames,
                         Relation relation) {
  Relation table = relation;
  if (ColumnNames.size() == 0) {
    // Return Empty Relation
    return Relation("Project-" + table.title());
  } else {
    std::vector<int> column_indexes;
    // Select ColumnNames from TableName
    for (const std::string& column_name : ColumnNames) {
      // Get indexes of columns requested
      column_indexes.push_back(table.find_column_index(column_name));
    }
    // Build new relation from column_indexes
    std::vector<Column<std::string>> selectcolumns;
    for (int i = 0; i < (int)column_indexes.size(); ++i) {
      selectcolumns.push_back(table.get_column(column_indexes[i]));
    }
    return Relation(("Project-" + table.title()), selectcolumns);
  }
}

Relation Engine::project(std::vector<std::string> ColumnNames,
                         std::string TableName) {
  return project(ColumnNames, find_relation_or_view(TableName));
}

bool Engine::unioncompatible(Relation table1, Relation table2) {
  if ((table1.get_column_titles() == table2.get_column_titles()) &&
      (table1.get_column_types() == table2.get_column_types())) {
    return true;
  } else {
    return false;
  }
}

bool Engine::unioncompatible(std::string TableName1, std::string TableName2) {
  return unioncompatible(find_relation(TableName1), find_relation(TableName2));
}

Relation Engine::setunion(Relation Table1, Relation Table2) {
  if (!unioncompatible(Table1, Table2)) {
    // Return invalid relation
    return Relation();
  } else {
    // Perform Union
    std::vector<Column<std::string>> unioncolumns;
    for (Column<std::string> column : Table1.columns()) {
      unioncolumns.push_back(column);
    }
    for (Column<std::string> t2column : Table2.columns()) {
      unioncolumns[Table2.find_column_index(t2column.title())].append_column(
          t2column);
    }
    return Relation("UnionTable", unioncolumns);
  }
}

Relation Engine::setunion(std::string TableName1, std::string TableName2) {
  return setunion(find_relation(TableName1), find_relation(TableName2));
}
Relation Engine::setunion(std::string TableName1, Relation TableName2) {
  return setunion(find_relation(TableName1), TableName2);
}
Relation Engine::setunion(Relation TableName1, std::string TableName2) {
  return setunion(TableName1, find_relation(TableName2));
}

Relation Engine::setdifference(Relation Table1, Relation Table2) {
  Relation difference("DifferenceTable");
  if (!unioncompatible(Table1, Table2)) {
    // Return invalid relation
    return difference;
  } else {
    // Create Columns for Difference Relation
    std::vector<Column<std::string>> diffcolumns;
    for (Column<std::string> column : Table1.columns()) {
      diffcolumns.push_back(Column<std::string>(column.title()));
    }
    // Put columns into difference
    difference.columns(diffcolumns);

    // Perform difference
    // iterate through rows in table 1
    for (int i = 0; i < Table1.num_rows(); ++i) {
      // set false before for each row
      bool rowfound = false;

      // iterate through rows in table 2
      // if row is found rowfound will become true
      for (int j = 0; j < Table2.num_rows(); ++j) {
        rowfound = rowfound || (Table1.get_row(i) == Table2.get_row(j));
      }

      // If row was not found, put it in difference
      if (!rowfound) difference.append_row(Table1.get_row(i));
    }

    return difference;
  }
}

Relation Engine::setdifference(std::string TableName1, std::string TableName2) {
  return setdifference(find_relation(TableName1), find_relation(TableName2));
}

Relation Engine::setdifference(Relation TableName1, std::string TableName2) {
  return setdifference(TableName1, find_relation(TableName2));
}

Relation Engine::setdifference(std::string TableName1, Relation TableName2) {
  return setdifference(find_relation(TableName1), TableName2);
}

Relation Engine::setcrossproduct(Relation Table1, Relation Table2) {
  Relation crossproduct("CrossProductTable");
  // Create Columns for crossproduct Relation
  std::vector<Column<std::string>> crosscolumns;
  for (Column<std::string> column : Table1.columns()) {
    crosscolumns.push_back(Column<std::string>(column.title()));
  }
  for (Column<std::string> col2 : Table2.columns()) {
    // Columns must have unique names, if not, rename the second one
    bool unique = true;
    for (Column<std::string> col1 : crosscolumns) {
      if (col1.title() == col2.title()) {
        unique = false;
        crosscolumns.push_back(
            Column<std::string>(col2.title() + "-" + Table2.title()));
        break;
      }
    }
    if (unique) crosscolumns.push_back(Column<std::string>(col2.title()));
  }

  // Put columns into crossproduct
  crossproduct.columns(crosscolumns);

  // Perform cross product
  // iterate through rows in table 1
  for (int i = 0; i < Table1.num_rows(); ++i) {
    // iterate through rows in table 2
    for (int j = 0; j < Table2.num_rows(); ++j) {
      std::vector<std::string> row = Table1.get_row(i);
      std::vector<std::string> t2row = Table2.get_row(j);
      row.insert(std::end(row), std::begin(t2row), std::end(t2row));
      crossproduct.append_row(row);
    }
  }

  return crossproduct;
}

Relation Engine::setcrossproduct(std::string TableName1,
                                 std::string TableName2) {
  return setcrossproduct(find_relation(TableName1), find_relation(TableName2));
}

Relation Engine::setcrossproduct(Relation TableName1, std::string TableName2) {
  return setcrossproduct(TableName1, find_relation(TableName2));
}

Relation Engine::setcrossproduct(std::string TableName1, Relation TableName2) {
  return setcrossproduct(find_relation(TableName1), TableName2);
}

void Engine::showTable(Relation table) { std::cout << table << std::endl; }
void Engine::showTable(std::string TableName) { showTable(find_relation_or_view(TableName)); }
