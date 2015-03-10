#ifndef TABLE_H
#define TABLE_H

#include "Parser.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Attribute;
struct Conditions;

struct Table {

  // member variables:
  vector <vector <string> > items; // data rows in the table
  vector <Attribute> attributes; // attributes for the table
  string name;


  Table();
  Table(string n, vector <Attribute> attr);

  string get_name();
  void set_name(string n);

  vector <vector <string> > get_items();

  // add item entry to end of table
  bool insert_item(vector <string> entry);

  // updates item at index with the contents of entry
  bool update_item(vector <string> entry, int index);

  // remove item at index
  bool delete_item(int index);

  // makes sure the typing for entry is valid with the table's
  bool check_types(vector <string> entry);

  // makes sure primary keys for entry line up with table's
  bool check_keys(vector <string> entry);

  vector <Attribute> get_attributes();
  vector <string> get_attribute_names();
  void set_attribute_names(vector <string> names);

  // get subsets of attributes or items based on input
  vector <Attribute> attribute_subset(vector <string> names);
  vector <vector <string> > item_subset(vector <string> names);

};

#endif
