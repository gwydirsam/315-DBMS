#include "Parser.h"

#include <string>
#include <iostream>

using namespace std;

Parser::Parser()
{
  database = new Database();
}

Parser::~Parser()
{
  if (database) delete database;
}

Token::Token(string s, int v, options t):token(s), value(v), type(t){}

Attribute::Attribute(bool b, string n, options t, int s):primary(b),
  name(n), type(t), size(s){}

// returns correct enum item for input string
options keyword(string s)
{
  if (s.compare("select")==0) return SELECT;
  if (s.compare("project")==0) return PROJECT;
  if (s.compare("rename")==0) return RENAME;
  if (s.compare("OPEN")==0) return OPEN;
  if (s.compare("CLOSE")==0) return CLOSE;
  if (s.compare("EXIT")==0) return EXIT;
  if (s.compare("SAVE")==0) return SAVE;
  if (s.compare("WRITE")==0) return WRITE;
  if (s.compare("SHOW")==0) return SHOW;
  if (s.compare("CREATE TABLE")==0) return CREATE_TABLE;
  if (s.compare("PRIMARY KEY")==0) return PRIMARY_KEY;
  if (s.compare("UPDATE")==0) return UPDATE;
  if (s.compare("VARCHAR")==0) return VARCHAR;
  if (s.compare("WHERE")==0) return WHERE;
  if (s.compare("SET")==0) return SET;
  if (s.compare("DELETE FROM")==0) return DELETE_FROM;
  if (s.compare("INSERT INTO")==0) return INSERT_INTO;
  if (s.compare("VALUES FROM")==0) return VALUES_FROM;
  if (s.compare("VALUES FROM RELATION")==0) return VALUES_FROM_RELATION;
  return IDENTIFIER;
}

string int_to_str(int i)
{
  stringstream ss;
  ss << i;
  return ss.str();
}

const string text_for_enum(int val)
{
  return options_str[val];
}

// determines if all characters in lit are digits
bool Parser::is_literal_num(string lit)
{
  for (int i = 0; i < lit.length();++i)
    if (!isdigit(lit[i])) return false;

  return true;
}

// determines if lit is encased by double quotes
bool Parser::is_literal_str(string lit)
{
  return lit[0]=='"' && lit[lit.length()-1]=='"';
}

// determines if id is a valid identifier
bool Parser::is_valid_identifier(string id)
{
  bool good = true;
  if (id[0]!='"' && id[id.length()-1]!='"') {
    for (int i = 0; i < id.length(); ++i) {
      good = isalpha(id[i]) || id[i]==' ' || id[i]=='_' || (i!=0 &&
            isdigit(id[i]));
    }

  }

  else {
    for (int i=1; i < id.length()-1;++i) {
      good = isalpha(id[i]) || id[i]==' ' || id[i]=='_'
        || (i!=0 && isdigit(id[i]));
    }
  }
  return good;
}

// removes the first token if appropriate. returns false if unsuccessful.
bool Parser::remove(string s)
{
  if (tokens.size() == 0) return false;
  if (s.compare(tokens.at(0).token)!=0) return false;
  else {
    tokens.erase(tokens.begin());
    return true;
  }
}

// separates input string into tokens
void Parser::lex(string s)
{
  stringstream input(s);
  char ch; // character currently being inspected
  input >> ch;
  while (input.good()){

     if (isdigit(ch)){ // digits; no doubles or negative integers allowed
       input.putback(ch);
       int temp;
       input >> temp;
       tokens.push_back(Token(int_to_str(temp),temp,INTEGER));
     }

     // check for left arrow & other 2 character operators
     else if (ch=='<'||ch=='>'||ch=='='||ch=='!') {
       char c2;
       input >> c2;
       if (c2=='-')
         tokens.push_back(Token("<-", -1, LARROW));
       else if (c2=='=') {
         switch(ch) {
           case '<': tokens.push_back(Token("<=",-1,LEQ));break;
           case '>': tokens.push_back(Token(">=",-1,GEQ));break;
           case '=': tokens.push_back(Token("==",-1,EQ));break;
           case '!': tokens.push_back(Token("!=",-1,NEQ));break;
         }
       }
       else {
        // putback c2 & push back single op for < or >
         input.putback(c2);
         switch (ch) {
            case '<': tokens.push_back(Token("<",-1,LESS));break;
            case '>': tokens.push_back(Token(">",-1,GREATER));break;
            default: break;
         }
       }
     }

     else if (ch == '&' || ch =='|') { // boolean operators
       char c2;
       input >> c2;
       if (ch == c2) {
         string t;
         if (ch == '&') tokens.push_back(Token("&&",-1,AND));
         else tokens.push_back(Token("||",-1,OR));
       }
     }

     else if (isalpha(ch)|| ch == '_') { // keywords and identifiers
       string t(1,ch);
       char c2;
       while (true) {
         input >> noskipws >> c2; //don't skip whitespace
         if (input.eof() || !(isalpha(c2)||c2 ==' '||c2 == '_')) {
            input.putback(c2);
            input >> skipws;
            break;
         }
         t += c2;
         if (t.compare("CREATE TABLE")==0 || t.compare("PRIMARY KEY")==0 ||
             t.compare("DELETE FROM")==0 || t.compare("INSERT INTO")==0 ||
             t.compare("VALUES FROM RELATION")==0)
           break;
         else if (t.at(t.size()-1)==' '&& t.compare("CREATE ")!=0 &&
               t.compare("PRIMARY ")!=0 && t.compare("DELETE ")!=0 &&
               t.compare("INSERT ")!=0 && t.compare("VALUES ")!=0 &&
               t.compare("VALUES FROM ")!=0)
           break;

       }
       if (t[t.size()-1] ==' ') t.pop_back(); // remove extraneous space
       tokens.push_back(Token(t,-1,keyword(t)));
     }

     else if (ch == '"') { // string literals
       string t = "\"";
       char c2;
       while (true) {
         input >> noskipws >> c2;
         if (input.eof() || c2 == '"') {
           t += "\"";
           input >> skipws;
           break;
         }
         t += c2;
        }
        tokens.push_back(Token(t,-1,LITERAL));
     }

     else { // only one character tokens & invalid are left
       string t(1,ch);
       if (ch == '(') tokens.push_back(Token(t,-1,LPAREN));
       else if (ch == ')') tokens.push_back(Token(t,-1,RPAREN));
       else if (ch == ';') tokens.push_back(Token(t,-1,SEMICOLON));
       else if (ch == ',') tokens.push_back(Token(t,-1,COMMA));
       else if (ch == '+') tokens.push_back(Token(t,-1,PLUS));
       else if (ch == '-') tokens.push_back(Token(t,-1,MINUS));
       else if (ch == '*') tokens.push_back(Token(t,-1,TIMES));
       else if (ch != ' ') tokens.push_back(Token(t,-1,INVALID));
     }

     input >> ch;
   } // end of while loop; all tokens have been identified
}

// Grammar parsing functions:
// ---------------------------------------------------------------------------

// digit := 0|...|9
bool Parser::integer(int& val)
{
  val = tokens.at(0).value;
  string s = int_to_str(val);
  if (remove(s) && is_literal_num(s)) {
    return true;
  }

  val = -1;
  return false;
}

// identifier := alpha{(alpha|digit)}
bool Parser::identifier(string& id)
{

  string s = tokens.at(0).token;

  if (remove(s) && is_valid_identifier(s)) {
    id = s;
    return true;
  }

  id = "";
  return false;
}

// literals are literally anything.
bool Parser::literal(string& lit)
{
  lit = tokens.at(0).token;
  remove(lit);
  return true;
}

// attribute type - varchar or integer
bool Parser::type(options& type, int& size)
{
  if (remove("VARCHAR")) {
    type = VARCHAR;
    return remove("(") && integer(size) && remove(")");
  }
  else {
    type = INTEGER;
    return remove("INTEGER");
  }
}

// relation_name := identifier
bool Parser::relation_name(string& id)
{
  return identifier(id);
}

// attribute name :=identifier
bool Parser::attribute_name(string& id)
{
  return identifier(id);
}

// attribute list that also holds types and indicates if primary key
bool Parser::typed_attribute_list(vector<Attribute>& attributes)
{
  bool ret = true;
  do
  {
    string s;
    options t;
    int size;

    ret = attribute_name(s);
    if (!type(t, size)) ret = false;
    attributes.push_back(Attribute(false,s,t,size));
  } while (remove(","));

  return ret;
}

// attribute-list:=attribute-name{,attribute-name}
bool Parser::attribute_list(vector<string>& v)
{
  bool ret = true;
  do
  {
    string s;
    ret = attribute_name(s);
    v.push_back(s);
  } while (remove(","));

  return ret;
}

// used to assist update_cmd
bool Parser::set_list(vector<pair<string, string> >& pairs)
{
  bool ret = true;
  do
  {
    string name, val;
    ret = attribute_name(name) && remove("==") && literal(val);

    pair<string, string> p(name, val);
    pairs.push_back(p);
  } while (remove(","));

  return ret;
}

// literal {,literal}
bool Parser::literal_list(vector<string>& v)
{
  bool ret = true;
  do
  {
    string str;
    ret = literal(str);

    v.push_back(str);
  } while (remove(","));

  return ret;
}

// returns true if valid command call
// command:=(open-cmd|close-cmd|write-cmd|exit-cmd|show-cmd|create-cmd
//       |update-cmd|insert-cmd|delete-cmd)
bool Parser::command()
{
  string s = tokens.at(0).token;
  if (s.compare("OPEN")==0) return open_cmd();
  else if (s.compare("CLOSE")==0) return close_cmd();
  else if (s.compare("WRITE")==0) return write_cmd();
  else if (s.compare("EXIT")==0) return exit_cmd();
  else if (s.compare("SHOW")==0) return show_cmd();
  else if (s.compare("CREATE TABLE")==0) return create_cmd();
  else if (s.compare("UPDATE")==0) return update_cmd();
  else if (s.compare("INSERT INTO")==0) return insert_cmd();
  else if (s.compare("DELETE FROM")==0) return delete_cmd();

  return false;
}

// returns true if valid query call
// query := relation-name <- expr;
bool Parser::query()
{
  if (tokens.size() == 0) return false;
  string destination = tokens.at(0).token;
  Table* table;
  remove(destination);
  destination += ".db";
  remove("<-");
  string s = tokens.at(0).token;
  string t = tokens.at(1).token;

  if (expr(destination, table)) {
    database->add(table);
    return true;
  }

  return false;
}

// Queries & accompanying functions:
// ---------------------------------------------------------------------------

//expr:= atomic-expr|selection|projection|renaming|union|difference|product
bool Parser::expr(string result, Table*& table)
{
  bool ret = false;
  string s  = tokens.at(0).token;
  //check for select, project, rename
  if (s.compare("select")==0||s.compare("project")==0||s.compare("rename")==0) {
    if (s.compare("select")==0) ret = selection(result,table);
    else if (s.compare("project")==0) ret = projection(result,table);
    else if (s.compare("rename")==0) ret = renaming(result,table);
  }

  /*
  //takes care of relation1 <- relation2 case
  else if(!(s.compare("+")==0) && !(s.compare("-")==0) && !(s.compare("*")==0))
    if(is_valid_identifier(s))
        return true;
  */

  //otherwise, get the atomic expr. and call union, difference, or product
  else {
    ret = atomic_expr(result,table);
    string t = tokens.at(0).token;
    if (t.compare("+")==0) {
      Table* table2;
      remove("+");
      ret &= atomic_expr("table2",table2);
      table = database->set_union(table, table2,result);
    }
    else if (t.compare("-")==0) {
      remove("-");
      Table* table2;
      ret &= atomic_expr("table2",table2);
      table = database->set_difference(table,table2,result);
    }
    else if (t.compare("*")==0) {
      remove("*");
      Table* table2;
      ret &= atomic_expr("table2",table2);
      table = database->cross_product(table,table2, result);
    }
    else return false;
  }

  ret &= (table != NULL);
  return ret;
}

// atomic-expr:=relation-name|(expr)
bool Parser::atomic_expr(string result, Table*& table)
{
  bool ret = false;
  if (remove("(")) {
    ret = expr(result, table) && remove(")");
  }
  else {
    string name;
    ret = relation_name(name);

    if (!ret) return ret;

    name += ".db";
    table = database->get_table(name);
  }

  ret &= (table != NULL);
  return ret;
}

// op:= ==|!=|<|>|<=|>=
bool Parser::op(options& t)
{
  string s = text_for_enum(tokens.at(0).type);
  if (s.compare("EQ")==0) {
    t = EQ;
    remove("==");
    return true;
  }
  else if (s.compare("NEQ")==0) {
    t = NEQ;
    remove("!=");
    return true;
  }
  else if (s.compare("LESS")==0) {
    t = LESS;
    remove("<");
    return true;
  }
  else if (s.compare("GREATER")==0) {
    t = GREATER;
    remove(">");
    return true;
  }
  else if (s.compare("LEQ")==0) {
   t = LEQ;
   remove("<=");
   return true;
  }
  else if (s.compare("GEQ")==0) {
    t = GEQ;
    remove(">=");
    return true;
  }

  else return false;
}

// operand:= attribute-name|literal
bool Parser::operand(string& oper)
{
  string s = tokens.at(0).token;
  if (!(is_literal_num(s)||is_literal_str(s))) {
    return attribute_name(oper);
  }

  else oper = s;
  if (is_literal_num(s) || is_literal_str(s)){
    remove(s);
    return true;
  }
  return false;
}

// comparison:=operand op operand |(condition)
bool Parser::comparison(Node*& node)
{
  bool ret = true;

  if (remove("("))
    ret = condition(node) && remove(")");

  else {
    options type;
    string operA, operB;

    ret = operand(operA);

    ret &= op(type) && operand(operB);
    //if (!operand(operB)) ret = false;

    node = new Node(type,options_str[type]);

    if (is_literal_str(operA) || is_literal_num(operA)) {
      node->left = new Node(ATTR, operB);
      node->right = new Node(LITERAL, operA);
    }

    else if (is_literal_str(operB) || is_literal_num(operB)) {
      node->left = new Node(ATTR, operA);
      node->right = new Node(LITERAL, operB);
    }

    else {
        node->left = new Node(ATTR, operA);
        node->right = new Node(ATTR, operB);
    }

  }

  return ret;
}

// conjunction:=comparison {&& comparison}
bool Parser::conjunction(Node*& node)
{
  Node* comp = NULL;
  bool ret = comparison(comp);
  if(!ret) cout << "comparison failed.\n";

  while (remove("&&")) {
   if (node == NULL) {
     node = new Node(AND, "&&");
     node->left = comp;
     ret &= comparison(node->right);
   }
   else {
     Node *next = new Node(AND, "&&");
     next->left = node->right;
     ret &= comparison(next->right);
     node->right = next;
   }
  }

  if (node == NULL)
    node = comp;

  return ret;
}

// condition:=conjunction {|| conjunction}
bool Parser::condition(Node*& node)
{
  Node* conj = NULL;
  bool ret = conjunction(conj);
  if (!ret) cout << "conjunction failed.\n";

  while (remove("||")) {
    if (node == NULL) {
      node = new Node(OR, "||");
      node->left = conj;
      ret &= conjunction(node->right);
    }
    else {
      Node* next = new Node(OR, "||");
      next->left = node->right;
      ret &= conjunction(next->right);
      node->right = next;
    }
  }

  if (node == NULL)
    node = conj;

  return ret;
}

// selection:=select (condition) atomic-expr
bool Parser::selection(string result, Table*& table)
{
  Conditions cond_tree;
  Table* table2;

  bool ret = remove("select") && remove("(");
  ret &= condition(cond_tree.root) && remove(")");
  ret &= atomic_expr("table2", table2);

  // check if condition was successful & atomic_expr was successful
  ret &= (cond_tree.root != NULL) && (table2 != NULL);

  if (ret)
    table = database->select(table2, cond_tree, result);

  ret &= (table != NULL);

  return ret;

}

// projection:= project (attribute-list) atomic-expr
bool Parser::projection(string result, Table*& table)
{
  vector<string> attributes;
  Table* table2;

  bool ret = remove("project") && remove("(");
  ret &= attribute_list(attributes) && remove(")");
  ret &= atomic_expr("table2",table2);

  ret &= (table2 != NULL);
  if (ret){
    table = database->project(table2, attributes, result);
  }
  return ret;
}

// renaming:= rename (attribute-list) atomic-expr
bool Parser::renaming(string result, Table*& table)
{
  vector<string> attributes;
  Table* table2;

  bool ret = remove("rename") && remove("(");
  ret &= attribute_list(attributes) && remove(")")
        && atomic_expr("table2",table2);

  ret &= (table != NULL);
  if (ret)
    table = database->rename(table2, attributes, result);

  return ret;
}

// Commands:
// --------------------------------------------------------------------------

// open-cmd:= OPEN relation-name
bool Parser::open_cmd()
{

  string name;
  bool ret = false;

  ret = remove("OPEN") && relation_name(name) && remove(";");
  name += ".db";

  if (ret) {
    ret &= database->open(name);
  }
  return ret;
}

// close-cmd:= CLOSE relation-name
bool Parser::close_cmd()
{
  string name;
  bool ret = false;

  ret = remove("CLOSE") && relation_name(name) && remove(";");
  name += ".db";
  if (ret)
    ret &= database->close(name);

  return ret;
}

// write-cmd:= WRITE relation-name
bool Parser::write_cmd()
{
  string name;
  bool ret = false;

  ret = remove("WRITE") && relation_name(name) && remove(";");
  name += ".db";
  if (ret)
     ret &= database->write(name);

  return ret;
}

// exit-cmd:= EXIT
bool Parser::exit_cmd()
{
  database->exit_db();
  return true;
}

// show-cmd:= SHOW atomic-expr
// currently only supports SHOW name;
bool Parser::show_cmd()
{
  string name;
  bool ret = false;

  ret = remove("SHOW") && relation_name(name) && remove(";");

  name += ".db";

  if (ret)
    ret &= database->show(name);

  return ret;
}

// create-cmd:= CREATE TABLE relation-name (typed-attribute-list)
//      PRIMARY KEY (attribute-list)
bool Parser::create_cmd()
{
  string name;
  vector<string> primaries;
  vector<Attribute> attributes;
  bool ret = false;

  ret = remove("CREATE TABLE") && relation_name(name);
  if (!remove("(")) ret = false;

  if (!typed_attribute_list(attributes)) ret = false;
  if (!remove(")"))ret = false;
  if (!remove("PRIMARY KEY")) ret = false;
  if (!remove("("))ret = false;
  if (!attribute_list(primaries))ret = false;
  if (!remove(")"))ret = false;
  if (!remove(";")) ret = false;

  //if an attribute is defined as a primary key, update its bool member
  for (int i = 0; i < attributes.size();++i) {
    for (int j = 0; j < primaries.size();++j) {
      if (attributes.at(i).name.compare(primaries.at(j))==0)
        attributes.at(i).primary = true;
    }
  }

  //add .db to file name if necessary
  if (name.length() >= 4 && name.substr(name.length()-3,
        name.length()-1).compare(".db") !=0)
    name += ".db";

  if (ret) {
    ret &= database->create_table(name, attributes);
  }
  return ret;
}

// update-cmd:= UPDATE relation-name SET attribute-name = literal
//    {,attribute-name = literal} WHERE condition
bool Parser::update_cmd()
{
  string name;
  Conditions cond_tree;
  vector<pair<string, string> > updates;

  bool ret = remove("UPDATE") && relation_name(name) && remove("SET") &&
    set_list(updates) && remove("WHERE") && condition(cond_tree.root) &&
    remove(";");

  for (int i = 0; i < updates.size(); ++i) {
    cout << updates[i].first << ", " << updates[i].second << endl;
  }

  name += ".db";
  ret &= (cond_tree.root != NULL);

  if (ret)
    ret &= database->update(name, updates, cond_tree);

  return ret;
}

// insert-cmd:= INSERT INTO relation-name VALUES FROM (literal {, literal}) |
//      INSERT INTO relation-name VALUES FROM RELATION expr
bool Parser::insert_cmd()
{
  string name;
  bool ret = false;

  ret = remove("INSERT INTO") && relation_name(name);
  name += ".db";
  if (remove("VALUES FROM")) {
    vector<string> literals;
    ret = remove("(") && literal_list(literals) && remove(")") && remove(";");
    if (ret) {
      ret = database->insert_into(name, literals);
    }
  }

  else if (remove("VALUES FROM RELATION")) {
    Table* from;
    ret &= expr("from", from) && remove(";");
    ret &= (from != NULL);

    if (ret) {
       ret &= database->insert_into(name, from);
    }
  }

  else ret = false;

  return ret;
}

// delete-cmd:=DELETE FROM relation-name WHERE condition
bool Parser::delete_cmd()
{
  string name;
  Conditions cond_tree;
  bool ret = remove("DELETE FROM") && relation_name(name);
  ret &= remove("WHERE");
  ret &= condition(cond_tree.root);

  ret &= remove(";");

  ret &= (cond_tree.root != NULL);
  if (ret) {
    ret = database->delete_from(name, cond_tree);
  }

  return ret;
}

// Parses the vector of tokens and determines the appropriate function to call
// program:={(query|command)}
bool Parser::program()
{
  bool ret = false;
  if (tokens.size()==0) return ret; //nothing to parse

  // execute appropriate command
  ret = command();

 if(!ret){
    // execute appropriate query
     ret = query();

     if (!ret) {
       tokens.clear();
       return false;
     }
  }

  return ret;
}
