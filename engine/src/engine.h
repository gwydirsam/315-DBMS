// CSCE 315-503
// engine.h

#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include <functional>

#include "sqltypes.h"
#include "relation.h"
#include "utility.h"

class Engine {
 public:
  // Constructors
  Engine() { errlog("Engine: Creating New Engine"); }

  // Destructors
  ~Engine();

  // Finders
  // Find Table
  Relation find_relation(std::string TableName);
  // Returns an iterator
  //TODO: sould probably be private
  std::vector<Relation>::iterator find_table(std::string TableName);
  // Returns the index of where the table is. Returns -1 if failed to find.
  int find_table_index(std::string TableName);
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
  void Table(std::string TableName, Relation Table);

  // Commands
  // Open
  int openTable(std::string TableName);

  // Create Table
  Relation createNewTable(std::string TableName,
                          std::vector<Column<std::string> > columns);

  // Update Table

  // Insert Tuple into Table
  int insertTuple(std::string TableName, std::vector<std::string> tuple);

  // Drop Table
  int dropTable(std::string TableName);
  int dropTable(Relation Table);

  // Delete Tuple in Table
  int dropTuple(std::string TableName, std::vector<std::string> tuple);

  // Exec SQL
  // return 0 on success
  int execSQL(std::string DML);

  // Write table to filename TableName.db
  void writeTable(Relation relation);

  // Delete table from open_tables_ and Write table to filename TableName.db
  int closeTable(std::string TableName);

  // Exit
  void exitDatabase(){};

  // Queries

  // Rename
  // Return 0 on success, non-zero on failure
  int rename_table(std::string TableName, std::string newname);
  int rename_column(std::string TableName, std::string Column,
                    std::string newname);

  // Select
  // Select in TableName where Function takes a tuple and returns a bool,
  // return vector of tuples where function is true

  // If ColumnNames is empty, interpret as *, or all
  // where is passed as a lambda function returning a bool and taking a column
  // name and a value
  Relation select(std::vector<std::string> ColumnNames, std::string TableName);
  Relation select(std::vector<std::string> ColumnNames, std::string TableName,
                  std::string WhereColumn, std::string WhereEqual);

  // Project
  // return vector of tuples from tablename with only Attributes attributes
  Relation project(std::vector<std::string> ColumnNames, std::string TableName);

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
  Relation setdifference(std::string TableName1, std::string TableName2);

  // Set Cross Product
  Relation setcrossproduct(std::string TableName1, std::string TableName2);

 private:
  // Data Structures
  std::vector<Relation> open_tables_;
};

#endif  // ENGINE_H_
