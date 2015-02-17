#include "relation.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Column<std::string>> Relation::primary_keys() {
  std::vector<Column<std::string>> primary_keys;
  for (const Column<std::string>& column : columns_) {
    if (column.primary_key()) {
      primary_keys.push_back(column);
    }
  }
  return primary_keys;
}

const std::vector<Column<std::string>> Relation::primary_keys() const {
  std::vector<Column<std::string>> primary_keys;
  for (const Column<std::string>& column : columns_) {
    if (column.primary_key()) {
      primary_keys.push_back(column);
    }
  }
  return primary_keys;
}

std::vector<std::string> Relation::get_row(int i) {
  std::vector<std::string> row;

  // Create row from each column
  for (const Column<std::string>& column : columns_) {
    row.push_back(column[i]);
  }
  return row;
}

const std::vector<std::string> Relation::get_row(int i) const {
  std::vector<std::string> row;

  // Create row from each column
  for (const Column<std::string>& column : columns_) {
    row.push_back(column[i]);
  }
  return row;
}

void Relation::print_row(int i, std::string delimiter) {
  for (const std::string& entry : get_row(i)) {
    std::cout << entry << delimiter;
  }
}

void Relation::print_row(int i, std::string delimiter) const {
  for (const std::string& entry : get_row(i)) {
    std::cout << entry << delimiter;
  }
}

std::vector<Column<std::string>>::iterator Relation::find_column(
    std::string column_name) {
  return std::find_if(std::begin(columns_), std::end(columns_),
                      [&column_name](Column<std::string> column)
                          -> bool { return column.title() == column_name; });
}

int Relation::find_column_index(std::string column_name) {
  return std::distance(std::begin(columns_), find_column(column_name));
}

int Relation::num_rows() const {
  // Return the number of entries in the first column. This should be equal to
  // all columns' number of entries
  if (columns_.size() == 0) {
    return 0;
  } else {
    return columns_.at(0).size();
  }
}

std::vector<std::string> Relation::get_column_titles() {
  std::vector<std::string> column_titles;
  for (Column<std::string> column : columns_) {
    column_titles.push_back(column.title());
  }
  return column_titles;
}

const std::vector<std::string> Relation::get_column_titles() const {
  std::vector<std::string> column_titles;
  for (Column<std::string> column : columns_) {
    column_titles.push_back(column.title());
  }
  return column_titles;
}

std::string Relation::string_column_titles() {
  std::string column_titles = "{ ";
  for (std::string title : get_column_titles()) {
    column_titles = column_titles + title + ' ';
  }
  return (column_titles + "}");
}

std::vector<std::string> Relation::get_column_types() {
  std::vector<std::string> column_types;
  for (const Column<std::string>& column : columns_) {
    column_types.push_back(column.type());
  }
  return column_types;
}

int Relation::append_row(std::vector<std::string> row) {
  if (row.size() != num_cols()) {
    // cannot append row if it doesn't have same number of entries as relation
    // has columns
    return -1;
  } else {
    for (int i = 0; i < row.size(); ++i) {
      columns_[i].insert_entry(row[i]);
    }
  }
}

void Relation::drop_row(int i) {
  for (Column<std::string>& column : columns_) {
    column.erase(i);
  }
}

std::ostream& operator<<(std::ostream& os, const Relation& relation) {
  std::string delimiter = "\t\t";

  os << relation.title() << std::endl;

  for (const Column<std::string>& column : relation.columns()) {
    std::string title;
    if (column.primary_key()) {
      title = "*" + column.title() + "*";
    } else {
      title = column.title();
    }
    os << title << delimiter;
  }
  os << std::endl;

  for (int i = 0; i < relation.num_rows(); ++i) {
    relation.print_row(i, delimiter);
    if (i != (relation.num_rows() - 1)) os << std::endl;
  }

  return os;
}

std::ifstream& operator>>(std::ifstream& is, Relation& relation) {
  // Lines:
  // 0: relation.title()
  // 1: relation.num_rows()
  // 2: relation.num_cols()
  // 3: number of primary keys
  // 4: primary keys (column names if theyre primary key)
  // Columns separated by tabs
  // 5: relation.columns()
  // 6-infinity: columns.entries()

  // delimiter is used to seperate columns
  std::string delimiter = "\t";

  // Line 0: TableName
  std::string relation_title;
  is >> relation_title;
  {
    std::string errmsg = "OpenTable: title: " + relation_title;
    errlog(errmsg);
  }

  int num_rows, num_cols, num_primary_keys;
  // Line 1: Number of Rows
  is >> num_rows;
  // line 2: number of Columns
  is >> num_cols;
  // line 3: number of primary keys
  is >> num_primary_keys;

  // Line 4: Primary Keys
  std::vector<std::string> primary_keys(num_primary_keys);
  for (unsigned int i = 0; i < num_primary_keys; ++i) {
    is >> primary_keys[i];
    std::string errmsg = "OpenTable: Primary Keys: " + primary_keys[i];
    errlog(errmsg);
  }

  // Line 5: Column Names
  std::vector<Column<std::string>> columns(num_cols);
  for (int i = 0; i < num_cols; ++i) {
    is >> columns[i].title();

    // if column title is in primary_keys, then set it as a primary key
    for (const std::string& key_name : primary_keys) {
      if (columns[i].title() == key_name) {
        columns[i].primary_key(true);
      }
    }

    std::string errmsg = "OpenTable: Column Names: " + columns[i].title();
    errlog(errmsg);
  }

  // Line 6-infinity: entries
  for (int j = 0; j < num_rows; ++j) {
    for (int i = 0; i < num_cols; ++i) {
      is >> columns[i];
      std::string errmsg = std::string("OpenTable: Column[") +
                           std::to_string(i) + std::string("][") +
                           std::to_string(j) + std::string("] : ") +
                           columns[i][j];
      errlog(errmsg);
    }
  }

  // Create Relation
  relation = Relation(relation_title, columns);

  return is;
}

std::ofstream& operator<<(std::ofstream& os, const Relation& relation) {
  // Lines:
  // 0: relation.title()
  // 1: relation.num_rows()
  // 2: relation.num_cols()
  // 3: number of primary keys
  // 4: primary keys (column names if theyre primary key)
  // Columns separated by tabs
  // 5: relation.columns()
  // 6-infinity: columns.entries()

  // delimiter is used to seperate columns
  std::string delimiter = "\t";

  // Line 0: TableName
  os << relation.title() << std::endl;

  // Line 1: Number of Rows
  os << relation.num_rows() << std::endl;
  // line 2: number of Columns
  os << relation.num_cols() << std::endl;
  // line 3: number of primary keys
  os << relation.primary_keys().size() << std::endl;

  // Line 4: Primary Keys
  for (const Column<std::string>& column : relation.primary_keys()) {
    os << column.title() << delimiter;
  }
  os << std::endl;

  // Line 5: Column Names
  for (const std::string& title : relation.get_column_titles()) {
    os << title << delimiter;
  }
  os << std::endl;

  // Line 6-infinity: entries
  for (int i = 0; i < relation.num_rows(); ++i) {
    for (const std::string& entry : relation.get_row(i)) {
      os << entry << delimiter;
    }
    os << std::endl;
  }

  return os;
}
