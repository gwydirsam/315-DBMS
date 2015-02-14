// CSCE 315-503
// relation.h

#ifndef RELATION_H_
#define RELATION_H_

#include <vector>
#include <string>

#include "column.h"
#include "sqltypes.h"

// A Relation is our representation of a table
// A relation has a title and contains tuples with each column having a type
class Relation {
 public:
  // Constructors
  Relation(std::string title) : title_(title), columns_(){};
  Relation(std::string title, std::vector<Column<std::string> > columns)
      : title_(title), columns_(columns){};
  // Shouldn't need to define our own copy constructor
  //Relation(Relation& Table)
  //: title_(Table.title()), columns_(Table.columns()){};
  // Default Constructor
  Relation() : title_("INVALID"), columns_(){};

  // Destructors
  // Default Destructor
  ~Relation(){};

  // Getters
  std::string title() { return title_; }
  std::vector<Column<std::string> > columns() { return columns_; }
  // TODO: redefine
  //  std::vector<Attribute> attributes() {return attributes_;}
  //  std::vector<Attribute> primarykeys() {return primarykeys_;}
  //  Attribute attribute(int i) {return attributes_.at(i);}
  //  Attribute primarykey(int i) {return primarykeys_.at(i);}

  std::vector<std::string> get_row(int i);

  // Setters
  void title(std::string title) { title_ = title; }
  // not sure if these are right...
  // you know for deep copy
  void columns(std::vector<Column<std::string> > columns) {
    columns_ = columns;
  }

  // Need to redefine for columns
  // void primarykeys(std::vector<Attribute> primarykeys) {primarykeys_ =
  // primarykeys;}

 private:
  // Data Structures
  // File Descriptor
  std::string title_;
  std::vector<Column<std::string> > columns_;
};

#endif  // RELATION_H_
