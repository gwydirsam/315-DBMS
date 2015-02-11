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
  Relation(std::string title, std::vector<Attribute> attributes, std::vector<Attribute> primarykey)
      : title_(title), attributes_(attributes), primarykey_(primarykey){};

  // Default Constructor
  Relation() : title_("INVALID"), attributes_(), tuples_(), primarykey_(){};

  // Destructors
  // Default Destructor
  ~Relation(){};

  // Getters

  // Setters

 private:
  // Data Structures
  // File Descriptor
  std::string title_;
  std::vector<Attribute> attributes_;
  std::vector<Attribute> primarykey_;
  std::vector<SQLTypes> tuples_;
};

#endif  // RELATION_H_
