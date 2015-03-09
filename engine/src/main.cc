// Rabia Gunonu, Sam Gwydir, Nicolas Juarez, Daniel Koon
// CSCE 315-503
// main.cc

#include <iostream>
#include <memory>
#include <fstream>

#include <string>
#include <cstring>

#ifdef READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include "../lib/engine.h"
#include "../lib/column.h"
#include "../lib/relation.h"
#include "../lib/utility.h"
#include "../lib/grammar.h"

// shell by default
// run dbengine --file file for scripts
// if your script does not explicitly EXIT, you will drop into a shell
int main(int argc, char* argv[]) {
  // Start Engine
  Engine dbengine;

  if ((argc > 2) && (std::strcmp(argv[1], "--file") == 0)) {
    errlog("Reading SQL Programs from file");

    std::vector<std::string> programs;

    // read file from stdin
    std::string line;
    std::ifstream scriptfile(argv[2]);
    if (scriptfile.is_open()) {
      while (std::getline(scriptfile, line)) {
        // skip empty lines
        if (line.length() > 1) {
          programs.push_back(line);
        }
      }
      scriptfile.close();
    }

// print debug info
#ifdef DEBUG
    errlog("Read Programs:");
    for (std::string prog : programs) {
      std::cout << prog << std::endl;
    }
#endif

    // if there's at least one string
    if (programs.size() > 0) {
      // run script
      for (std::string prog : programs) {
        std::string errstr = "Main: Running: " + prog;
        errlog(errstr);
        if (prog.length() > 1) {
          dbengine.execSQL(prog);
#ifdef READLINE
          add_history(prog.c_str());
    #endif
        }
#ifdef DEBUG
        draw_line();
#endif
      }
    }
    std::cout << "Script Execution Finished." << std::endl;
  }

#ifdef READLINE
  // input and shell_prompt buffer
  char* input, shell_prompt[4096];

  // Configure readline to auto-complete paths when the tab key is hit.
  rl_bind_key('\t', rl_complete);

  for (;;) {
// Create prompt string from user name and current working directory.
#ifdef DEBUG
    snprintf(shell_prompt, sizeof(shell_prompt), "%s@DBshell(DEBUG) > ",
             getenv("USER"));
#else
    snprintf(shell_prompt, sizeof(shell_prompt), "%s@DBshell > ",
             getenv("USER"));
#endif

    // Display prompt and read input (NB: input must be freed after use)...
    input = readline(shell_prompt);

    // Check for EOF.
    if (!input) {
      break;
    }

    // Add input to history.
    add_history(input);

    // parse input
    // check if help
    if (std::strcmp(input, "?") == 0) {
      std::cout << "Want Help? Read the docs. They end in .h and .cc."
                << std::endl;
    } else if (std::strcmp(input, "") == 0) {
      // nothing
    } else {
      dbengine.execSQL(input);
    }

    // Free input.
    free(input);
  }
#endif

#ifndef READLINE
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
#endif

  // dbengine.execSQL("EXIT;");

  return 0;
}
