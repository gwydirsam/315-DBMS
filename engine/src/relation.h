// CSCE 315-503
// relation.h

#ifndef RELATION_H_
#define RELATION_H_

#include <vector>
#include <string>
#include <algorithm>

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
  // Relation(Relation& Table)
  //: title_(Table.title()), columns_(Table.columns()){};
  // Default Constructor
  Relation() : title_("INVALID"), columns_(){};

  // Destructors
  // Default Destructor
  ~Relation(){};

  // Getters
  std::string title() { return title_; }
  std::vector<Column<std::string> > columns() { return columns_; }
  // Const Getters
  const std::string& title() const { return title_; }
  const std::vector<Column<std::string> >& columns() const { return columns_; }

  // TODO: redefine
  //  std::vector<Attribute> attributes() {return attributes_;}
  //  std::vector<Attribute> primarykeys() {return primarykeys_;}
  //  Attribute attribute(int i) {return attributes_.at(i);}
  //  Attribute primarykey(int i) {return primarykeys_.at(i);}
  Column<std::string> get_column(int i) { return columns_.at(i); }

  std::vector<std::string> get_row(int i);
  void print_row(int i);
  void print_row(int i, char delimiter);

  std::vector<Column<std::string> >::iterator find_column(
      std::string column_name);

  int find_column_index(std::string column_name) {
    return std::distance(std::begin(columns_), find_column(column_name));
  }

  // Return the number of entries in the first column. This should be equal to
  // all columns' number of entries
  int num_rows() { return columns_[0].size(); }
  int num_cols() { return columns_.size(); }

  // Setters
  void title(std::string title) { title_ = title; }
  // not sure if these are right...
  // you know for deep copy
  void columns(std::vector<Column<std::string> > columns) {
    columns_ = columns;
  }

  // rename column i to newName
  void rename_column(int i, std::string newName) {
    columns_.at(i).title(newName);
  }

  void rename_column(std::string oldName, std::string newName) {
    columns_.at(find_column_index(oldName)).title(newName);
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
