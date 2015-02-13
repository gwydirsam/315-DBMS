#include "engine.h"

#include <iostream>
#include <fstream>

#include "column.h"
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

int Engine::find_table(std::string TableName) {
  int i = 0;
  while (i < open_tables_.size()) {
    if (TableName.compare(open_tables_.at(i).title())) return i;
    i++;
  }
  return -1;
}

Relation Engine::get_table(std::string TableName) {
  int i = find_table(TableName);
  if (i != -1)
    return open_tables_.at(i);
  else {
    // Don't know how we want to handle not finding table
  }
}

int Engine::openTable(std::string TableName) {
  std::string line;
  std::ifstream dbfile;
  dbfile.open(TableName.append(".db"));
  // Read into relation
  dbfile >> line;
  //
  Relation table("DUMMY", {{"INVALID", "INVALID"}}, {{"INVALID", "INVALID"}});
  open_tables_.push_back(table);
  return (open_tables_.size() - 1);
}

void Engine::writeTable(Relation relation) {
  std::ofstream dbfile;
  dbfile.open(relation.title().append(".db"));
  // Writeattributes into relation

  // Columns seprated by commas
  // Line:
  // 0: relation.title()
  // 1: relation.attributes()
  // 2-infinity: relation.tuples() 
  //
  // write this
}


Relation Engine::createNewTable(std::string TableName,
                                std::vector<Column> primarykeys) {
  Relation table(TableName, attributes, primarykeys);
  writeTable(table);
  openTable(TableName);
  return table;
}

int Engine::rename_table(std::string TableName, std::string newname) {
  int i = find_table(TableName);
  if (i != -1) {
    open_tables_.at(i).title(newname);
    return 0;
  }

  return i;
}

int Engine::rename_attribute(std::string TableName, Attribute attribute,
                             std::string newname) {
  int i = find_table(TableName);
  if (i != -1) {
    int num_att = open_tables_.at(i).attributes().size();
    int w = 0;
    while (w < num_att) {
      if (attribute.title().compare(open_tables_.at(i).attribute(w).title())) {
        open_tables_.at(i).attribute(w).title(newname);
        return 0;
      }
      w++;
    }
  }

  return -1;
}
