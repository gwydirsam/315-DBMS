// CSCE 315-503
// engine.h

#ifndef ENGINE_H_
#define ENGINE_H_

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
