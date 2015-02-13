// CSCE 315-503
// relation.h

#ifndef RELATION_H_
#define RELATION_H_

#include <vector>
#include <string>

#include "attribute.h"
#include "sqltypes.h"

// A Relation is our representation of a table
// A relation has a title and contains tuples with each column having a type
class Relation {
 public:
  // Constructors
  Relation(std::string title, std::vector<Attribute> attributes, std::vector<Attribute> primarykeys)
      : title_(title), attributes_(attributes), primarykeys_(primarykeys){};

  // Default Constructor
  Relation() : title_("INVALID"), attributes_(), tuples_(), primarykeys_(){};

  // Destructors
  // Default Destructor
  ~Relation(){};

  // Getters
  std::string title() {return title_;}
  std::vector<Attribute> attributes() {return attributes_;}
  std::vector<Attribute> primarykeys() {return primarykeys_;}
  Attribute attribute(int i) {return attributes_.at(i);}
  Attribute primarykey(int i) {return primarykeys_.at(i);}

  // Setters
  void title(std::string title) {title_ = title;}
  //not sure if these are right...
  //you know for deep copy
  void attributes(std::vector<Attribute> attributes) {attributes_ = attributes;}
  void primarykeys(std::vector<Attribute> primarykeys) {primarykeys_ = primarykeys;}

 private:
  // Data Structures
  // File Descriptor
  std::string title_;
  std::vector<Attribute> attributes_;
  std::vector<Attribute> primarykeys_;
  std::vector<Tuple> tuples_;
};

#endif  // RELATION_H_
