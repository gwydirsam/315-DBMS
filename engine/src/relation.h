// CSCE 315-503
// relation.h

#ifndef RELATION_H_
#define RELATION_H_

#include <vector>
#include <utlity>
#include <string>

#include "attribute.h"

// A Relation is our representation of a table
// A relation has a title and contains tuples with each column having a type
class Relation {
 public:
  // Constructors
  Relation(std::string title, std::tuple attributes)
      : title_(title), attributes_(attributes){};

  // Default Constructor
  Relation() : title_("INVALID"), attributes_(), tuples_(){};

  // Destructors
  // Default Destructor
  ~Relation(){};

  // Getters

  // Setters

 private:
  // Data Structures
  std::string title_;
  std::tuple attributes_;
  std::vector<std::tuple> tuples_;
};

#endif  // RELATION_H_
