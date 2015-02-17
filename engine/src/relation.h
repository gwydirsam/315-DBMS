// CSCE 315-503
// relation.h

#ifndef RELATION_H_
#define RELATION_H_

#include <vector>
#include <string>
#include <algorithm>

#include "column.h"
#include "utility.h"

// A Relation is our representation of a table
// A relation has a title and contains tuples with each column having a type
class Relation {
 public:
  // Constructors
  Relation(std::string title) : title_(title), columns_(){};
  Relation(std::string title, std::vector<Column<std::string> > columns)
      : title_(title), columns_(columns){};
  // Default Constructor
  Relation() : title_("INVALID"), columns_(){};

  // Destructors
  ~Relation(){};

  // Getters
  std::string& title() { return title_; }
  std::vector<Column<std::string> >& columns() { return columns_; }
  std::vector<Column<std::string> > primary_keys();

  // Const Getters
  const std::string& title() const { return title_; }
  const std::vector<Column<std::string> >& columns() const { return columns_; }
  const std::vector<Column<std::string> > primary_keys() const;

  Column<std::string> get_column(int i) { return columns_.at(i); }
  std::vector<std::string> get_row(int i);

  const Column<std::string> get_column(int i) const { return columns_.at(i); }
  const std::vector<std::string> get_row(int i) const;

  // Setters
  void title(std::string title) { title_ = title; }
  void columns(std::vector<Column<std::string> > columns) {
    columns_ = columns;
  }

  // Printers
  // Print row seperated by tabs
  void print_row(int i);
  // Print row seperated by delimiter
  void print_row(int i, char delimiter);

  void print_row(int i) const;
  void print_row(int i, char delimiter) const;

  // Finders
  std::vector<Column<std::string> >::iterator find_column(
      std::string column_name);

  int find_column_index(std::string column_name);

  // Statistics
  int num_rows() const;
  int num_cols() const { return columns_.size(); }

  // Return vector of string title
  std::vector<std::string> get_column_titles();

  // Return string of titles
  std::string string_column_titles();

  // Return vector of columns type
  std::vector<std::string> get_column_types();

  // Drop
  void drop_row(int i);

  // Rename
  // rename column i to newName
  void rename_column(int i, std::string newName) {
    columns_.at(i).title(newName);
  }

  void rename_column(std::string oldName, std::string newName) {
    columns_.at(find_column_index(oldName)).title(newName);
  }

 private:
  // Data Structures
  std::string title_;
  std::vector<Column<std::string> > columns_;
};

std::ostream& operator<<(std::ostream& os, const Relation& relation);

#endif  // RELATION_H_
