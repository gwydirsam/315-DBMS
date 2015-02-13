#include "engine.h"
#include "relation.h"

/* **********************************************************
   **********************************************************
   ******************** What's not done *********************

   //could do if i knew what format we were going to read in / write out
   int writeTable(std::string TableName);
   int closeTable(std::string TableName);
   int showTable(std::string TableName);

   **********************************************************
   **********************************************************
   ********************* IDK what to do *********************

   // Setters
   // Set Table
   // Set Tuple
   //anything dealing with tuples is throwing me cause IDK what they are being
   used for at the moment.

   std::tuple table(std::string TableName, int id);
   int insertTuple(std::string TableName, std::tuple);
   int dropTable(std::string TableName);
   int dropTuple(std::string TableName, std::tuple);
   int execDML(std::string DML);
   int exitDatabase();
   std::vector<std::tuple> select(std::string TableName,
   std::function<bool(std::Tuple)> function);
   std::vector<std::tuple> project(std::string TableName, std::vector<Attribute>
   attributes);
   std::vector<std::tuple> setunion(std::string TableName1, std::string
   TableName2);
   std::vector<std::tuple> setdifference(std::string TableName1, std::string
   TableName2);
   std::vector<std::tuple> setcrossproduct(std::string TableName1, std::string
   TableName2);

   **********************************************************
   **********************************************************
   **********************************************************
*/

int find_table(std::string TableName) {
  int i = 0;
  while (i < tables_.size()) {
    if (TableName.compare(tables_.at(i).get_title())) return i;
    i++;
  }
  return -1;
}

Relation get_table(std::string TableName) {
  int i = find_table(TableName);
  if (i != -1)
    return tables_.at(i);
  else {
    // Don't know how we want to handle not finding table
  }
}

int createTable(std::string TableName,
                        std::vector<Attribute> attributes,
                        std::vector<Attribute> primarykeys) {
  Relation table(TableName, attributes, primarykeys);
  openTable(table);
  // TODO This should return success of constructor
  if (find_table(TableName) != -1) return 0;
  return -1;
}

int rename_table(std::string TableName, std::string newname) {
  int i = find_table(TableName);
  if (i != -1) {
    tables_.at(i).set_title(newname);
    return 0;
  }

  return i;
}

int rename_attribute(std::string TableName, Attribute attribute,
                             std::string newname) {
  int i = find_table(TableName);
  if (i != -1) {
    int num_att = tables_.at(i).get_attributes().size();
    int w = 0;
    while (w < num_att) {
      if (attribute.get_title().compare(
              tables_.at(i).get_attribute(w).get_title())) {
        tables_.at(i).get_attribute(w).set_title(newname);
        return 0;
      }
      w++;
    }
  }

  return -1;
}
