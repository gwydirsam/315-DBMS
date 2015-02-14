// CSCE 315-503
// column.h

#ifndef COLUMN_H_
#define COLUMN_H_

#include <vector>
#include <string>

#include "attribute.h"

template <typename std::string>
class Column {
 public:
  // Constructors
  Column(Attribute attribute): title_(attribute.title()), type_(attribute.type()) {}
  Column(std::string title, std::string type) : title_(title), type_(type), entries_(){}
  // Default Constructor
  Column() : title_("INVALID"), type_(), entries_(){};

  // Destructors
  // Default Destructor
  ~Column(){};

  // Getters
  std::string title() { return title_; }
  std::string type() { return type_; }
  std::vector<std::string>& entries() { return entries_; }
  bool primary_key() { return primary_key; }

  // Setters
  void type(std::string type) { type_ = type; }
  void title(std::string title) { title_ = title; }
  void entries(std::vector<std::string> entries) { entries_ = entries; }
  void primary_key(bool primary_key) { primary_key_ = primary_key; }

 private:
  // Data Structures
  std::string title_;
  std::string type_;
  // True if this column is a primary key
  bool primary_key_;
  std::vector<std::string> entries_;
};

#endif  // COLUMN_H_
