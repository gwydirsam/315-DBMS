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

  const std::vector<std::string> get_row(int i) const;
  void print_row(int i) const;
  void print_row(int i, char delimiter) const;

  std::vector<Column<std::string> >::iterator find_column(
      std::string column_name);

  int find_column_index(std::string column_name) {
    return std::distance(std::begin(columns_), find_column(column_name));
  }

  // Return the number of entries in the first column. This should be equal to
  // all columns' number of entries
  int num_rows() const {
    if (columns_.size() == 0) {
      return 0;
    } else {
      return columns_.at(0).size();
    }
  }
  int num_cols() const { return columns_.size(); }

  std::vector<std::string> get_column_titles() {
    std::vector<std::string> column_titles;
    for (const Column<std::string>& column : columns_) {
      column_titles.push_back(column.title());
    }
    return column_titles;
  }

  std::vector<std::string> get_column_types() {
    std::vector<std::string> column_types;
    for (const Column<std::string>& column : columns_) {
      column_types.push_back(column.type());
    }
    return column_types;
  }

  void drop_row(int i) {
    for (Column<std::string>& column : columns_) {
      column.erase(i);
    }
  }

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

  //  void apped_column(std::string ColumnName, Column<std::string> column) {
  //    columns_[find_column_index(ColumnName)];
  //    for()
  //  }

  // Need to redefine for columns
  // void primarykeys(std::vector<Attribute> primarykeys) {primarykeys_ =
  // primarykeys;}

 private:
  // Data Structures
  // File Descriptor
  std::string title_;
  std::vector<Column<std::string> > columns_;
};

std::ostream& operator<<(std::ostream& os, const Relation& relation);

#endif  // RELATION_H_
