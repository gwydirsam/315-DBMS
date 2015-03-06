#include "Parser.h"

#include <string>
#include <iostream>

using namespace std;
int main()
{
  cout << "\n**CSCE 315-503 Group 16 Database Shell**\n";
  cout << "Group members: Amy Kruzick, Cody Leuschner,"
       << " Jason Krezinski, and Jerego Orlino.\n";
  cout << "Currently unsupported functionality:\n"
       << "\trelation_name <- relation_name;\n"
       << "\tSHOW atomic_expr (currently performs SHOW relation_name)\n";


  string input;
  Parser parser;
  bool b = true;

  // get commands from cin until user exits
  while (true) {
    cout << "Input: ";
    getline(cin, input);
    parser.lex(input);
    b = parser.program();

    if (b) cout << "Result: successful interaction!\n";
    else cout << "An error occurred. Please check the input and try again.\n";

    // clears parser of any leftover tokens;
    // helps prevent crashing if previous statement was invalid.
    parser.tokens.clear();
  }

  return 0;
}
