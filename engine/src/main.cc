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

  dbengine.execSQL("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");
  dbengine.execSQL("INSERT INTO species VALUES FROM RELATION (project (name, kind) animals);");
  dbengine.execSQL("WRITE table;");
  dbengine.execSQL("EXIT;");
  dbengine.execSQL("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
  dbengine.execSQL("SHOW animals;");
  dbengine.execSQL("UPDATE species SET name = \"Sam\" WHERE ID == 11;");
  dbengine.execSQL("DELETE FROM animals WHERE extinct == \"false\";");
  dbengine.execSQL(" posts  <-   select (aname == name && akind != kind) (a * animals)  ;");
  dbengine.execSQL(" posts  <-    animals  ;");
  dbengine.execSQL("cats_or_dogs <- dogs + (select (kind == \"cat\") animals);");
  dbengine.execSQL("animals <- species * animals;");
  dbengine.execSQL("common_names <- project (name) (select (aname == name && akind != kind) (a * animals));");
  dbengine.execSQL("a <- rename (aname, akind) (project (name, kind) animals);");

  return 0;
}
