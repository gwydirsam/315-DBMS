#include "Conditions.h"

using namespace std;

Node::Node():literal(""), type(-1), left(NULL), right(NULL) {}

Node::Node(int t, string s)
  :literal(s), type(t), flipped(false), left(NULL), right(NULL){}

// evaluates a condition tree at a certain row with values from a table
bool Node::evaluate(Table* t, int row)
{
  if (!is_op()) return false;

  //recurse if this node is an AND or OR node
  if (type == AND){
    return left->evaluate(t, row) && right->evaluate(t, row);
  }
  if (type == OR){
    return left->evaluate(t, row) || right->evaluate(t, row);
  }

  string item, comparison;

  Node *attrib, *lit;

  if ((left->type==ATTR) && (right->type==LITERAL||right->type== ATTR)) {
    attrib = left;
    lit = right;
  }
  else if ((right->type==ATTR) && left->type==LITERAL) {
    attrib = right;
    lit = left;

    if (!flipped) flip();
  }
  else return false;

  // get first string to compare:
  int column = -1;

  for (int i = 0; i < t->get_attributes().size(); ++i) {
    if (t->get_attribute_names()[i].compare(attrib->literal)==0){
      column = i;
      break;
    }
  }

  if (column == -1) return false;

  item = t->get_items()[row][column];

  //get second string:
  column = -1;
  if (lit->type == ATTR) {
    for (int i = 0; i < t->get_attributes().size();++i) {
      if (t->get_attribute_names()[i].compare(lit->literal)==0) {
        column = i;
        break;
      }
    }

    if (column == -1) return false;
    comparison = t->get_items()[row][column];
  }
  else comparison = lit->literal;

  // compare based on node type
  // no need for breaks since these all return values
  switch(type) {
    case GREATER: return compare(item, comparison) > 0;

    case LESS: return compare(item, comparison) < 0;

    case GEQ: return compare(item, comparison) >= 0;

    case LEQ: return compare(item, comparison) <= 0;

    case NEQ: if (comparison[0]=='"' && comparison[comparison.length()-1]=='"')
                comparison = comparison.substr(1,comparison.length()-2);
              if (item[0]=='"' && item[item.length()-1]=='"')
                item = item.substr(1, item.length()-2);
              return item.compare(comparison) != 0;

    case EQ: if (comparison[0]=='"' && comparison[comparison.length()-1]=='"')
               comparison = comparison.substr(1, comparison.length()-2);
             if (item[0]=='"' && item[item.length()-1]=='"')
               item = item.substr(1,item.length()-2);
             return item.compare(comparison) == 0;
    default: return false;
  }

}

bool Node::is_op()
{
  return type == GREATER || type == LESS || type == EQ || type == GEQ
              || type == LEQ || type == NEQ || type == AND || type == OR;
}

bool Node::is_int(string str)
{
  for (char c : str) {
    if (!isdigit(c))
      return false;
  }

  return true;
}

void Node::flip()
{
  flipped = true;

  if (type == GREATER) {
    type = LESS;
    return;
  }
  if (type == LESS) {
    type = GREATER;
    return;
  }

  if (type == GEQ) {
    type = LEQ;
    return;
  }

  if (type == LEQ) {
    type = GEQ;
    return;
  }
}

int Node::compare(string a, string b)
{
  int first, second;
  stringstream streamA, streamB;

  streamA << a;
  streamB << b;

  streamA >> first;
  streamB >> second;

  return first-second;
}

Conditions::Conditions()
{
  root = NULL;
}

bool Conditions::evaluate(Table* t, int row)
{
  return root->evaluate(t, row);
}
