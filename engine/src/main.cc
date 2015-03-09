// Rabia Gunonu, Sam Gwydir, Nicolas Juarez, Daniel Koon
// CSCE 315-503
// main.cc

#include <iostream>
#include <memory>

#include <string>
#include <cstring>

#include "../lib/engine.h"
#include "../lib/column.h"
#include "../lib/relation.h"
#include "../lib/utility.h"
#include "../lib/grammar.h"

std::vector<std::string> ReadSTDIN() {
  errlog("Reading SQL Programs from stdin");

  std::vector<std::string> programs;

  // read file from stdin
  std::string line;
  while (std::getline(std::cin, line)) {
    // skip empty lines
    if (line.length() > 1) {
      programs.push_back(line);
    }
  }

// print debug info
#ifdef DEBUG
  errlog("Read Programs:");
  for (std::string prog : programs) {
    std::cout << prog << std::endl;
  }
#endif

  return programs;
}

// shell by default
// run dbengine --stdin < file for scripts
// if your script does not explicitly EXIT, you will drop into a shell
int main(int argc, char* argv[]) {
  // Start Engine
  Engine dbengine;

  if ((argc > 1) && (std::strcmp(argv[1], "--stdin") == 0)) {
    // if used with --stdin read stdinput
    std::vector<std::string> stdinprograms = ReadSTDIN();

    // if there's at least one string
    if (stdinprograms.size() > 0) {
      // run script
      for (std::string prog : stdinprograms) {
        std::string errstr = "Main: Running: " + prog;
        errlog(errstr);
        if (dbengine.execSQL(prog) != 0) {
          std::cerr << "Parse Failed" << std::endl;
        }
      }
      draw_line();
      std::cout << "Script Execution Finished." << std::endl;
      std::cout.clear();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  // run shell
  errlog("Starting DBMS Shell.");
  std::cout << "Group 15 DBMS Shell (^D to Finish)" << std::endl;

  std::string input;
  std::cout << "> ";
  while (std::getline(std::cin, input)) {
    // TODO check if valid here
    if (input == "EXIT;") {
      break;
    }
    if (dbengine.execSQL(input) != 0) {
      std::cerr << "Parse Failed" << std::endl;
    }
    input = "";
    std::cout << "> ";
  }

  dbengine.execSQL("EXIT;");

  return 0;
}
