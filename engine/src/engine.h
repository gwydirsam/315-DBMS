// CSCE 315-503
// engine.h

#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include <utility>
#include <functional>

#include "attribute.h"

class Engine {
 public:
  // Constructors
  // Later
  //Engine(Parser parser) : parser_(parser) {}

  // Default Constructor
  Engine(){};

  // Destructors
  // Default Destructor
  ~Engine(){};

  // Getters
  // Get Table
  std::vector<std::tuple> table(std::string TableName);
  // Get Tuple
  std::tuple table(std::string TableName, int id);

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
  int createTable(std::string TableName, std::vector<Attribute> attributes, std::vector<Attribute> primarykeys);

  // Update Table

  // Insert Tuple into Table
  int insertTuple(std::string TableName, std::tuple);
  // Drop Table
  int dropTable(std::string TableName);
  // Delete Tuple in Table
  int dropTuple(std::string TableName, std::tuple);
  // Exec DML
  // Returns 0 on success, non-zero on failure
  // DML string is a valid string based on the grammar
  int execDML(std::string DML);

  // Write table to filename TableName.db
  // Returns 0 on success, non-zero on failure
  int writeTable(std::string TableName);
  // Delete File Descriptor and Write table to filename TableName.db
  // Returns 0 on success, non-zero on failure
  int closeTable(std::string TableName);
  // Exit
  int exitDatabase();

  // Queries

  // Select
  // Select in TableName where Function takes a tuple and returns a bool,
  // return vector of tuples where function is true
  std::vector<std::tuple> select(std::string TableName, std::function<bool(std::Tuple)> function);

  // Project
  // return vector of tuples from tablename with only Attributes attributes
  std::vector<std::tuple> project(std::string TableName, std::vector<Attribute> attributes);

  // Rename
  // Return 0 on success, non-zero on failure
  // Rename attribute attribute to newname in TableName
  int rename(std::string TableName, Attribute attribute, std::string newname);

  // Set Union
  // if Union-Compatible
  std::vector<std::tuple> setunion(std::string TableName1, std::string TableName2);

  // Set Difference
  // if Union-Compatible
  std::vector<std::tuple> setdifference(std::string TableName1, std::string TableName2);

  // Set Cross Product
  std::vector<std::tuple> setcrossproduct(std::string TableName1, std::string TableName2);

 private:
  //  Parser parser_;
  // Data Structures
};

#endif  // ENGINE_H_
