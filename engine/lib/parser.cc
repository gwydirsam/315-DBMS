#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <boost/algorithm/string.hpp>
#include <functional>

#include "parser.h"
#include "relation.h"
#include "grammar.h"
#include "grammar_objects.h"

// Receives command and returns a string of that command.
std::string Parser::receive_command(std::string command) { return "s";}

// Translate a command to Engine command string.
std::string Parser::translate_command(std::string command) {return "s";}

// Sends the engine command to be executed or executes it here.
int Parser::execSQL(std::string input_string) {
 /* Program program = parse_string(input_string);
  std::cout << program << std::endl;
  
  //checks if query
  //if(Query q = boost::get<Query>(program)) {
  Query q("table", new Expression("select", {"aname", "==", "name", "&&", "akind", "!=", "kind"}))
    // checks if relation is already in views_
	int i = find_view_index(q.relation_name);
	Relation r;
	if(i != -1) {
		r(views_.at(i));
	}
	else {
	  r(q.relation_name);
	}
	
	Expression e = q.expression;
	
	if(e.query == "select") {
	// TODO also what about other select
	  Relation r1 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation r2 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation select = Engine::select(r1, r2);
	}
	
	else if(e.query == "project") {
	// TODO
	  Relation r1 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation r2 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation project = Engine::(r1, r2);
	}
	
	else if(e.query == "rename") {
	 std::string newname = e.argument.at();
	 Relation rename = Engine::rename_table(r, newname);
	}
	
	else if(e.query == "union") {
	  Relation r1 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation r2 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation union = Engine::setunion(r1, r2);
	}
	
	else if(e.query == "difference") {
	  Relation r1 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation r2 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation difference = Engine::setdifference(r1, r2);
	}
	
	else if(e.query == "product") {
	  Relation r1 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation r2 = views_.at.(  find_view_index( e.subexpressions.at() ) );
	  Relation crossproduct = Engine::setcrossproduct(r1, r2);
	}
	// atomic expression
	else {
	  // TODO
	}
	
  }
  //command
  else {
  }
  */
  return -1;
}

// Breaks a string into a vector of strings where each string in the vector is
// one word (space separated) from the original strings
std::vector<std::string> Parser::tokenize(std::string query) {
  std::vector<std::string> tokens;
  boost::split(tokens, query, boost::is_any_of("\t "));
  return tokens;
}

// finding views
Relation& Parser::find_relation(std::string TableName) {
  return views_.at(find_view_index(TableName));
}
// Returns std::end if NOTHING found
std::vector<Relation>::iterator Parser::find_view(std::string TableName) {
return std::find_if(std::begin(views_), std::end(views_),
                    [TableName](Relation relation)
                        -> bool { return relation.title() == TableName; });
}

int Parser::find_view_index(std::string TableName) {
  if (find_view(TableName) == std::end(views_)) {
    // Return failure
    return -1;
  } else {
  return std::distance(std::begin(views_), find_view(TableName));
  }
}
