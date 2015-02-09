// CSCE 315-503
// engine.h

#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>

#include "parser.h"

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
  int createTable(String TableName,
              std::vector<std::pair<SQLTYPE, String> > attributes);
  // Insert Tuple into Table
  // Show Table
  // Drop Table
  // Delete Tuple in Table

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
