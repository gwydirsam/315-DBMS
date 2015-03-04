// Rabia Gunonu, Sam Gwydir, Nicolas Juarez, Daniel Koon
// CSCE 315-503
// main.cc

#include <iostream>
#include <memory>

#include "../lib/engine.h"
#include "../lib/column.h"
#include "../lib/relation.h"
#include "../lib/utility.h"
#include "../lib/grammar.h"

int main(int argc, char* argv[]) {
  Engine dbengine;
  Column<std::string> first_col("Scrooge");
  first_col.primary_key(true);
  first_col.insert_entry("bah");
  first_col.insert_entry("hum");
  first_col.insert_entry("bug");
  first_col.insert_entry("foo");
  first_col.insert_entry("bar");

  Column<std::string> second_col("Money");
  second_col.insert_entry("$10");
  second_col.insert_entry("$100");
  second_col.insert_entry("$1000");
  second_col.insert_entry("$10000");
  second_col.insert_entry("$100000");

  Column<std::string> third_col("Scrooge");
  third_col.primary_key(true);
  third_col.insert_entry("1");
  third_col.insert_entry("2");
  third_col.insert_entry("3");
  third_col.insert_entry("4");
  third_col.insert_entry("5");

  Column<std::string> fourth_col("Money");
  fourth_col.insert_entry("Money1");
  fourth_col.insert_entry("Money2");
  fourth_col.insert_entry("Money3");
  fourth_col.insert_entry("Money4");
  fourth_col.insert_entry("Money5");

  Column<std::string> fifth_col("Scrooge");
  fifth_col.primary_key(true);
  fifth_col.insert_entry("1");
  fifth_col.insert_entry("4");
  fifth_col.insert_entry("5");

  Column<std::string> sixth_col("Money");
  sixth_col.insert_entry("Money1");
  sixth_col.insert_entry("Money2");
  sixth_col.insert_entry("Money5");

  Column<std::string> seventh_col("id");
  seventh_col.primary_key(true);
  seventh_col.insert_entry("1");
  seventh_col.insert_entry("2");
  seventh_col.insert_entry("3");
  seventh_col.insert_entry("4");
  seventh_col.insert_entry("5");

  Column<std::string> eighth_col("Name");
  eighth_col.insert_entry("sam");
  eighth_col.insert_entry("rabia");
  eighth_col.insert_entry("nick");
  eighth_col.insert_entry("kade");
  eighth_col.insert_entry("leonardo");

  std::vector<Column<std::string>> columns0;
  std::vector<Column<std::string>> columns1;
  std::vector<Column<std::string>> columns2;
  std::vector<Column<std::string>> columns3;
  std::vector<Column<std::string>> columns4;

  columns0.push_back(first_col);
  columns0.push_back(second_col);

  columns1.push_back(third_col);
  columns1.push_back(fourth_col);

  columns2.push_back(first_col);
  columns2.push_back(fourth_col);

  columns3.push_back(fifth_col);
  columns3.push_back(sixth_col);

  columns4.push_back(seventh_col);
  columns4.push_back(eighth_col);

  dbengine.createNewTable("Test0", columns0);
  dbengine.createNewTable("Test1", columns1);
  dbengine.createNewTable("Test2", columns2);
  dbengine.createNewTable("Test3", columns3);
  dbengine.createNewTable("Test4", columns4);
  dbengine.print_list_open_tables();
  std::cout << std::endl;

  dbengine.execSQL("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");
  dbengine.execSQL(
      "INSERT INTO species VALUES FROM RELATION (project (name, kind) "
      "animals);");
  dbengine.execSQL("WRITE table;");
  dbengine.execSQL("EXIT;");
  dbengine.execSQL(
      "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) "
      "PRIMARY KEY (name, kind);");
  dbengine.execSQL("SHOW animals;");
  dbengine.execSQL("UPDATE species SET name = \"Sam\" WHERE ID == 11;");
  dbengine.execSQL("DELETE FROM animals WHERE extinct == \"false\";");
  dbengine.execSQL(
      " posts  <-   select (Scrooge == \"bah\") (Test0 * Test2)  ;");
  dbengine.execSQL(" posts  <-    Test2  ;");
  dbengine.execSQL(
      "cats_or_dogs <- dogs + (select (kind == \"cat\") animals);");
  dbengine.execSQL("animals <- species * animals;");
  dbengine.execSQL(
      "common_names <- project (name) (select (aname == name && akind != kind) "
      "(a * animals));");
  dbengine.execSQL(
      "a <- rename (aname, akind) (project (name, kind) animals);");

  return 0;
}
