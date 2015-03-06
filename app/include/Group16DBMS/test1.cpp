#include "Parser.h"

using namespace std;

Parser p;

void test_update(){
  p.lex("UPDATE animals SET kind == \"cat\" WHERE (kind != \"cat\" && years > 10);");
  p.program();
  p.tokens.clear();

  p.lex("SHOW animals;");
  p.program();
  p.tokens.clear();
}

void test_select1()
{
  p.lex("dogs <- select (kind == \"dog\") animals;");
  p.program();
  p.tokens.clear();
  cout << "\n showing dogs: \n";
  p.lex("SHOW dogs;");
  p.program();
  p.tokens.clear();
}

void test_select2()
{
  p.lex("old_dogs <- select (years > 10) dogs;");
  p.program();
  p.tokens.clear();
  cout << "\n showing old_dogs:\n";
  p.lex("SHOW old_dogs;");
  p.program();
  p.tokens.clear();

}

void test_select3()
{
  p.lex("cats_or_dogs <- dogs + (select (kind == \"cat\") animals);");
  p.program();
  p.tokens.clear();
  p.lex("SHOW cats_or_dogs;");
  p.program();
  p.tokens.clear();
}

void test_select4()
{
  p.lex("test <- select(aname == name && akind != kind) (a*animals);");
  p.program();
  p.tokens.clear();
  p.lex("SHOW test;");
  p.program();
  p.tokens.clear();
}

void test_rename1()
{
  p.lex("an <- rename (aname, kind) animals;");
  p.program();
  p.tokens.clear();
  p.lex("SHOW an;");
  p.program();
  p.tokens.clear();
}

void test_project1()
{
  p.lex("an <- project (kind) animals);");
  p.program();
  p.tokens.clear();
  p.lex("SHOW an;");
  p.program();
  p.tokens.clear();
}

void test_union()
{
  p.lex("test <- animals + animals;");
  p.program();
  p.tokens.clear();
  p.lex("SHOW test;");
  p.program();
  p.tokens.clear();
}

void test_difference()
{
  p.lex("test <- animals - animals;");
  p.program();
  p.tokens.clear();
  p.lex("SHOW test;");
  p.program();
  p.tokens.clear();
}

void test_product()
{
  p.lex("an<- a * animals;");
  p.program();
  p.tokens.clear();
  p.lex("SHOW an;");
  p.program();
  p.tokens.clear();
}

void test_rename_and_project()
{
  p.lex("a <- rename (aname, akind) (project (name, kind) animals));");
  p.program();
  p.tokens.clear();
  p.lex("SHOW a;");
  p.program();
  p.tokens.clear();
}

void test_project_and_select()
{
  p.lex("common_names <- project(name) (select(aname == name && akind != kind) (a * animals));");
  p.program();
  p.tokens.clear();
  p.lex("SHOW common_names;");
  p.program();
  p.tokens.clear();
}

void test_insert_from_relation()
{
  p.lex("INSERT INTO species VALUES FROM RELATION project (kind) animals;");
  p.program();
  p.tokens.clear();
  p.lex("SHOW species;");
  p.program();
  p.tokens.clear();
  p.lex("WRITE species;");
  p.program();
  p.tokens.clear();
}

int main()
{
  p.lex("OPEN animals;");
  p.program();
  p.tokens.clear();

  p.lex("SHOW animals;");
  p.program();
  p.tokens.clear();

  p.lex("OPEN species;");
  p.program();
  p.tokens.clear();

  p.lex("SHOW species;");
  p.program();
  p.tokens.clear();

  //test_update();

  //test_select1();
  //test_select2();
  //test_select3();
  //test_rename1();
  test_project1();
  //test_rename_and_project();
  //test_union();
  //test_product();
  //test_difference();
  //test_select4();
  //test_project_and_select();
  test_insert_from_relation();
}
