#include "relation.h"

std::vector<Column<std::string> > Relation::primary_keys() {
  std::vector<Column<std::string> > primary_keys;
  for (const Column<std::string>& column : columns_) {
    if (column.primary_key()) {
      primary_keys.push_back(column);
    }
  }
  return primary_keys;
}

const std::vector<Column<std::string> > Relation::primary_keys() const {
  std::vector<Column<std::string> > primary_keys;
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

std::vector<Column<std::string> >::iterator Relation::find_column(
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
