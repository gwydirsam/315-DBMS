#include "relation.h"

std::vector<Column<std::string> >::iterator Relation::find_column(
    std::string column_name) {
  return std::find_if(std::begin(columns_), std::end(columns_),
                      [&column_name](Column<std::string> column)
                          -> bool { return column.title() == column_name; });
}
