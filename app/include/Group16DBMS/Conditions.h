#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "Parser.h"
//#include "Table.h"

#include <string>
#include <vector>

using namespace std;

struct Table;

struct Node {

  // member variables:
  string literal;
  int type; // corresponds to 'options' enum
  bool flipped;

  // pointers to children
  Node* left;
  Node* right;

  // constructors:
  Node(int t, string s);
  Node();

  bool evaluate(Table* t, int row);

  bool is_op();
  bool is_int(string str);
  void flip();
  int compare(string a, string b);

};

// represents a condition as a binary tree
struct Conditions {
  public:
    Conditions();
    bool evaluate(Table* t, int row);

  // private:
    Node* root;
};

#endif
