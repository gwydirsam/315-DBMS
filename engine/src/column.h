// CSCE 315-503
// column.h

#ifndef COLUMN_H_
#define COLUMN_H_

#include <vector>
#include <string>

template <typename T>
class Column {
 public:
  // Constructors
  Column(std::string title, T type)
      : title_(title), type_(type), entries_(), primary_key_(false){};
  Column(std::string title, T type, std::vector<T> entries)
      : title_(title), type_(type), , entries_(entries), primary_key_(false){};
  Column(std::string title, T type, std::vector<T> entries, bool primary_key)
      : title_(title),
        type_(type),
        entries_(entries),
        primary_key_(primary_key){};
  Column(Column& column)
      : title_(column.title()),
        type_(column.type()),
        entries_(column.entries()),
        primary_key_(column.primary_key()){};
  // Default Constructor
  Column() : title_("INVALID"), type_(), entries_(){};

  // Destructors
  // Default Destructor
  ~Column(){};

  // Getters
  std::string title() { return title_; }
  T type() { return type_; }
  std::vector<T>& entries() { return entries_; }
  bool primary_key() { return primary_key; }

  // Setters
  void type(T type) { type_ = type; }
  void title(std::string title) { title_ = title; }
  void entries(std::vector<T> entries) { entries_ = entries; }
  void primary_key(bool primary_key) { primary_key_ = primary_key; }

 private:
  // Data Structures
  std::string title_;
  T type_;
  // True if this column is a primary key
  bool primary_key_;
  std::vector<T> entries_;
};

#endif  // COLUMN_H_
