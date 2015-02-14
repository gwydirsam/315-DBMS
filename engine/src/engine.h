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

  // Find Table
  // Right now returns the index of where the table is. Returns -1 if failed to
  // find.
  // TODO: Should this look in only open_tables? or should it search the db files?
  int find_table(std::string TableName);

  // Getters
  // Get Table
  Relation get_table(std::string TableName);
  // Get All Tables
  std::vector<Relation> open_tables() { return open_tables_; }
  // Get Tuple
  Tuple get_tuple(std::string TableName, int id);

  // Setters
  // Set Table
  // Set Tuple

  // Commands
  // Open
  int openTable(std::string TableName);

  // Show
  // Show Table
  int showTable(std::string TableName);

  // Create Table
  // Returns 0 on success, non-zero on failure
  Relation createNewTable(std::string TableName, std::vector<Column<std::string> > attributes);

  // Update Table

  // Insert Tuple into Table
  int insertTuple(std::string TableName, std::vector<std::string> tuple);
  // Drop Table
  int dropTable(std::string TableName);
  // Delete Tuple in Table
  int dropTuple(std::string TableName, Tuple tuple);
  // Exec DML
  // Returns 0 on success, non-zero on failure
  // DML string is a valid string based on the grammar
  int execDML(std::string DML);

  // Write table to filename TableName.db
  // Returns 0 on success, non-zero on failure
  int writeTable(Relation relation);
  // Delete File Descriptor and Write table to filename TableName.db
  // Returns 0 on success, non-zero on failure
  int closeTable(std::string TableName);
  // Exit
  int exitDatabase();

  // Queries

  // Rename
  // Return 0 on success, non-zero on failure
  int rename_table(std::string TableName, std::string newname);
  // Rename Attribute attribute to newname in TableName
  int rename_attribute(std::string TableName, Attribute attribute,
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
