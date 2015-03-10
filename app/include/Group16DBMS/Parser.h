#ifndef PARSER_H
#define PARSER_H

#include "Database.h"
#include "Conditions.h"
#include "Table.h"

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Database;
struct Node;
struct Conditions;
struct Table;


enum options{
  // keywords
  SELECT, PROJECT, RENAME, OPEN, CLOSE, EXIT, SAVE, WRITE, SHOW,
  CREATE_TABLE, PRIMARY_KEY, UPDATE, VARCHAR, WHERE, SET, DELETE_FROM,
  INSERT_INTO, VALUES_FROM, VALUES_FROM_RELATION, INTEGER, IDENTIFIER,
  LITERAL, ATTR, INVALID,
  // symbols
  LARROW, LPAREN, RPAREN, EQ, LESS, GREATER, LEQ, GEQ, NEQ, PLUS,
  MINUS, TIMES, AND, OR, SEMICOLON, COMMA
};

const string options_str[] = {"SELECT", "PROJECT", "RENAME", "OPEN", "CLOSE",
  "EXIT", "SAVE", "WRITE", "SHOW", "CREATE_TABLE", "PRIMARY_KEY", "UPDATE",
  "VARCHAR","WHERE","SET","DELETE_FROM", "INSERT_INTO","VALUES_FROM",
  "VALUES_FROM_RELATION", "INTEGER","IDENTIFIER","LITERAL", "ATTR", "INVALID",
  "LARROW", "LPAREN", "RPAREN", "EQ", "LESS", "GREATER", "LEQ", "GEQ",
  "NEQ", "PLUS", "MINUS","TIMES","AND","OR","SEMICOLON", "COMMA"};


options keyword(string s);
struct Parser;

struct Token{
  string token; // what the user entered for the token
  int value; // only used if token is an integer; -1 otherwise
  options type; // what kind of Token is it?

  Token(string s, int v, options t);
};

struct Attribute {
  bool primary; // is this attribute a primary key?
  string name; // name of attribute
  options type; // VARCHAR or INTEGER
  int size; // for varchar

  Attribute (bool b, string n, options t, int s);
};


struct Parser {
  public:
    vector<Token> tokens;

    //RDBMS database;
    Database *database;
    Parser();
    ~Parser();

    void lex(string s);
    bool program();

  private:
    bool command();
    bool query();
    bool is_literal_str(string lit);
    bool is_literal_num(string lit);
    bool is_valid_identifier(string id);
    bool remove(string s);

    bool integer(int& val);
    bool type(options& t, int& size);
    bool identifier(string& id);
    bool literal(string &lit);
    bool relation_name(string& id);
    bool attribute_name(string &id);
    bool typed_attribute_list(vector<Attribute>& attributes);
    bool attribute_list(vector<string>& v);
    bool set_list(vector<pair<string, string> >& pairs);
    bool literal_list(vector<string>& v);

    // Queries:
    bool selection(string result, Table*& table);
    bool projection(string result, Table*& table);
    bool renaming(string result, Table*& table);
    bool relation_union();
    bool difference();
    bool product();
    bool expr(string result, Table*& table);
    bool atomic_expr(string result, Table*& table);
    bool op(options& t);
    bool operand(string& oper);
    bool comparison(Node*& node);
    bool conjunction(Node*& node);
    bool condition(Node*& node);

    // Commands:
    bool open_cmd();
    bool close_cmd();
    bool write_cmd();
    bool exit_cmd();
    bool show_cmd();
    bool create_cmd();
    bool update_cmd();
    bool insert_cmd();
    bool delete_cmd();
};

#endif
