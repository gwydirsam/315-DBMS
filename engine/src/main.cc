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
  Engine db;

  db.execSQL("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");

  return 0;
}
