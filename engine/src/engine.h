// CSCE 315-503
// engine.h

#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include <utility>

#include "parser.h"
#include "attribute.h"

class Engine {
 public:
  // Constructors
  Engine(Parser parser) : parser_(parser) {}

  // Default Constructor
  Engine() : parser_(){};

  // Destructors
  // Default Destructor
  ~Engine(){};

  // Getters
  // Get Table
  // Get Tuple

  // Setters
  // Set Table
  // Set Tuple

  // Commands
  // Show

  // Create Table
  // Returns 0 on success, non-zero on failure
  int createTable(std::string TableName, std::vector<Attribute> attributes);

  // Insert Tuple into Table
  int insertTuple(std::string TableName, std::tuple);
  // Show Table
  int showTable(std::sring TableName);
  // Drop Table
  int dropTable(std::sring TableName);
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

  // Queries
  // Select
  // Union
  // Difference
  // Product
  // Project

 private:
  Parser parser_;
  // Data Structures
};

#endif  // ENGINE_H_
