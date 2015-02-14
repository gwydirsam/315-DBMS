// CSCE 315-503
// engine.h

#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include <functional>

#include "attribute.h"
#include "sqltypes.h"
#include "relation.h"

class Engine {
 public:
  // Constructors
  // Default Constructor
  Engine(){};

  // Destructors
  // Default Destructor
  ~Engine(){};

  // Finders
  // Find Table
  // Returns the index of where the table is. Returns -1 if failed to find.
  int find_table(std::string TableName);
  // Find Column
  int find_column(std::string TableName, std::string ColumnName);
  int find_column(Relation Table, std::string ColumnName);

  // Getters
  // Get Table
  Relation get_table(std::string TableName);
  // Get All Tables
  std::vector<Relation> open_tables() { return open_tables_; }
  // Get Tuple
  Tuple get_tuple(std::string TableName, int id);

  // Setters
  // Set Table
  void Table(std::string TableName, Relation Table);
  // Set Tuple

  // Commands
  // Open
  int openTable(std::string TableName);

  // Show
  // Show Table
  int showTable(std::string TableName);
  int showTable(Relation Table);

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
  // Exec DML
  // Returns 0 on success, non-zero on failure
  // DML string is a valid string based on the grammar
  int execDML(std::string DML);

  // Write table to filename TableName.db
  // Returns 0 on success, non-zero on failure
  void writeTable(Relation relation);
  // Delete File Descriptor and Write table to filename TableName.db
  // Returns 0 on success, non-zero on failure
  int closeTable(std::string TableName);
  // Exit
  int exitDatabase();

  // Queries

  // Rename
  // Return 0 on success, non-zero on failure
  int rename_table(std::string TableName, std::string newname);
  int rename_column(std::string TableName, Column<std::string> Column,
                    std::string newname);

  // Select
  // Select in TableName where Function takes a tuple and returns a bool,
  // return vector of tuples where function is true
  std::vector<Tuple> select(std::string TableName,
                            std::function<bool(Tuple)> function);

  // Project
  // return vector of tuples from tablename with only Attributes attributes
  std::vector<Tuple> project(std::string TableName,
                             std::vector<Attribute> attributes);

  // Set Union
  // if Union-Compatible
  Relation setunion(std::string TableName1, std::string TableName2);

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
