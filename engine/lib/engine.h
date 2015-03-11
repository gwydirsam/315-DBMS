// CSCE 315-503
// engine.h

#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include <functional>
#include <string>

#include "sqltypes.h"
#include "relation.h"
#include "utility.h"

class Engine {
 public:
  // Constructors
  Engine();

  // Destructors
  ~Engine();

  void exitEngine();

  // Finders
  // Find table or view, returns a relation, wherever it finds it.
  Relation& find_relation_or_view(std::string TableName);
  // Find Table
  Relation& find_relation(std::string TableName);
  // Returns an iterator
  // TODO: should probably be private
  std::vector<Relation>::iterator find_table(std::string TableName);
  // Returns the index of where the table is. Returns -1 if failed to find.
  int find_table_index(std::string TableName);

  // Find Table
  Relation& find_view(std::string TableName);
  // Returns an iterator
  // TODO: should probably be private
  std::vector<Relation>::iterator find_view_table(std::string TableName);
  // Returns the index of where the table is. Returns -1 if failed to find.
  int find_view_index(std::string TableName);

  int find_tuple_index(std::string TableName, std::vector<std::string> tuple);

  // Getters
  // Get All Tables
  std::vector<Relation> open_tables() { return open_tables_; }
  // List Tables
  std::vector<std::string> list_open_tables();
  int num_open_tables();
  void print_list_open_tables();

  // Setters
  // Set Table
  void set_table(std::string TableName, Relation Table);

  // Commands
  // Open
  int openTable(std::string TableName);

  // Create Table
  Relation createNewTable(std::string TableName,
                          std::vector<Column<std::string>> columns);
  Relation createNewTable(std::string TableName,
                          std::vector<std::string> typed_attribute_list,
                          std::vector<std::string> primary_keys);

  // Update Table
  Relation updateTable(std::string TableName, std::vector<std::string> attribute_value_list, std::vector<std::string> condition);

  // Insert Tuple into Table
  int insertTuple(Relation& relation, std::vector<std::string> tuple);
  int insertTuple(std::string TableName, std::vector<std::string> tuple);
  int insertTuple(std::string TableName, Relation relation);

  // Drop Table
  int dropTable(std::string TableName);
  int dropTable(Relation Table);

  // Drop View
  int dropView(std::string TableName);
  int dropView(Relation Table);

  // Delete From
  int deleteFrom(Relation& Table, std::vector<std::string> Conditions);
  int deleteFrom(std::string TableName, std::vector<std::string> Conditions);

  // Delete Tuple in Table
  int dropTuple(std::string TableName, std::vector<std::string> tuple);

  // Exec SQL
  // return 0 on success
  int execSQL(const std::string& input_string);

  // Write table to filename TableName.db
  void writeTable(Relation relation);
  void writeTable(std::string TableName);

  // Add view to open_views
  void addView(Relation relation);

  // Delete table from open_tables_ and Write table to filename TableName.db
  int closeTable(std::string TableName);
  int closeTable(Relation relation);

  // Queries

  // Rename
  Relation rename_table(Relation table, std::string newname);
  // Return 0 on success, non-zero on failure
  int rename_table(std::string TableName, std::string newname);
  int rename_column(std::string TableName, std::string Column,
                    std::string newname);
  Relation rename_column(Relation& relation, std::string Column,
                         std::string newname);

  // Select
  // Select in TableName where Function takes a tuple and returns a bool,
  // return vector of tuples where function is true

  // If ColumnNames is empty, interpret as *, or all
  // where is passed as a lambda function returning a bool and taking a column
  // name and a value
  Relation select(std::vector<std::string> Conditions, Relation relation);
  Relation select(std::vector<std::string> ColumnNames, std::string TableName);
  // Relation select(std::vector<std::string> ColumnNames, Relation relation);
  Relation select(std::vector<std::string> ColumnNames, std::string TableName,
                  std::string WhereColumn, std::string WhereEqual);
  Relation select(std::vector<std::string> ColumnNames, Relation relation,
                  std::string WhereColumn, std::string WhereEqual);

  // Project
  // return vector of tuples from tablename with only Attributes attributes
  Relation project(std::vector<std::string> ColumnNames, std::string TableName);
  Relation project(std::vector<std::string> ColumnNames, Relation relation);

  // Set Union
  // return true if union compatible
  bool unioncompatible(Relation TableName1, Relation TableName2);
  bool unioncompatible(std::string TableName1, std::string TableName2);

  // if Union-Compatible
  Relation setunion(Relation TableName1, Relation TableName2);
  Relation setunion(std::string TableName1, std::string TableName2);
  Relation setunion(Relation TableName1, std::string TableName2);
  Relation setunion(std::string TableName1, Relation TableName2);

  // Set Difference
  // if Union-Compatible
  Relation setdifference(Relation Table1, Relation Table2);
  Relation setdifference(std::string TableName1, std::string TableName2);
  Relation setdifference(Relation TableName1, std::string TableName2);
  Relation setdifference(std::string TableName1, Relation TableName2);

  // Set Cross Product
  Relation setcrossproduct(Relation Table1, Relation Table2);
  Relation setcrossproduct(std::string TableName1, std::string TableName2);
  Relation setcrossproduct(Relation TableName1, std::string TableName2);
  Relation setcrossproduct(std::string TableName1, Relation TableName2);

  // Show Table
  void showTable(Relation table);
  void showTable(std::string TableName);

 private:
  // Data Structures
  std::vector<Relation> open_tables_;
  std::vector<Relation> open_views_;
};

#endif  // ENGINE_H_
