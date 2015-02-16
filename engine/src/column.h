// CSCE 315-503
// column.h

#ifndef COLUMN_H_
#define COLUMN_H_

#include <iostream>
#include <vector>
#include <string>
#include <iterator>

template <typename T>
class Column {
 public:
  // Constructors
  Column(std::string title)
      : title_(title), type_(), primary_key_(false), entries_(){};
  Column(std::string title, T type)
      : title_(title), type_(type), primary_key_(false), entries_(){};
  Column(std::string title, T type, std::vector<T> entries)
      : title_(title), type_(type), primary_key_(false), entries_(entries){};
  Column(std::string title, T type, bool primary_key)
      : title_(title), type_(type), primary_key_(primary_key){};
  Column(std::string title, T type, std::vector<T> entries, bool primary_key)
      : title_(title),
        type_(type),
        primary_key_(primary_key),
        entries_(entries){};
  // Default Constructor
  Column() : title_("INVALID"), type_(), primary_key_(false), entries_(){};

  // Destructors
  ~Column(){};

  // Getters
  std::string title() { return title_; }
  T type() { return type_; }
  std::vector<T> entries() { return entries_; }
  bool primary_key() { return primary_key_; }
  int size() { return entries_.size(); }

  // Const Getters
  const std::string& title() const { return title_; }
  const T& type() const { return type_; }
  const std::vector<T>& entries() const { return entries_; }
  const bool& primary_key() const { return primary_key_; }
  int size() const { return entries_.size(); }

  // Setters
  void type(T type) { type_ = type; }
  void title(std::string title) { title_ = title; }
  void entries(std::vector<T> entries) { entries_ = entries; }
  void primary_key(bool primary_key) { primary_key_ = primary_key; }

  void insert_entry(T entry) { entries_.push_back(entry); }

  void append_column(Column<T> column) {
    for (const T& entry : column.entries()) {
      entries_.push_back(entry);
    }
  }

  // Functions
  typename std::vector<T>::iterator erase(int row) {
    return entries_.erase(std::begin(entries_) + row);
  }
  void clear() { entries_.clear(); }

  // Member Operators
  // [] directly accesses entries
  T& operator[](int i) { return entries_[i]; }
  const T& operator[](int i) const { return entries_[i]; }

 private:
  // Data Structures
  std::string title_;
  T type_;
  bool primary_key_;
  std::vector<T> entries_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Column<T>& column) {
  for (const T& entry : column.entries()) {
    os << entry << std::endl;
  }
  return os;
}

#endif  // COLUMN_H_
