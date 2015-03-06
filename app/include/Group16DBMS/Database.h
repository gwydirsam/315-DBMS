#ifndef DATABASE_H
#define DATABASE_H

#include "Parser.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Attribute;
struct Table;
struct Conditions;
struct Parser;

// A Database object represents a collection of Tables(relations)
// and can modify or show their contents.
class Database {
  public:
    vector <Table> dbms;

    Database();

    // adds relation to db
    bool add(Table* table);

    // commands:
    bool open(string name);
    bool close(string name);
    bool write(string name);
    bool show(string name);
    bool create_table(string name, vector <Attribute> attr);
    void exit_db();
    bool update(string name, vector<pair<string, string> > pairs,
        Conditions cond);
    bool insert_into(string name, Table* from);
    bool insert_into(string name, vector<string> values);
    bool delete_from(string name, Conditions cond);

    // relational algebra:
    Table* select(Table* table, Conditions cond, string name);
    Table* project(Table* table, vector <string> attr, string name);
    Table* rename(Table* table, vector <string> updates, string name);
    Table* set_union(Table* table1, Table* table2, string name);
    bool union_possible(Table* table1, Table* table2);
    Table* set_difference(Table* table1, Table* table2, string name);
    Table* cross_product(Table* table1, Table* table2, string name);
    Table* get_table(string name);
};

#endif
