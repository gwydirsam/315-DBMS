#include "Table.h"

Table::Table() {}

Table::Table(string n, vector <Attribute> attr): name(n), attributes(attr){}

// returns name of table
string Table::get_name()
{
  return name;
}

// sets name of table
void Table::set_name(string n)
{
  name = n;
}

// returns attribute list for table
vector <Attribute> Table::get_attributes(){
  return attributes;
}

// returns string names of attributes of table
vector <string> Table::get_attribute_names()
{
  vector <string> ret;

  for (int i = 0; i < attributes.size(); ++i)
    ret.push_back(attributes[i].name);

  return ret;
}

// sets attribute names (strings) for table
void Table::set_attribute_names(vector <string> names)
{
  for (int i = 0; i < attributes.size(); ++i)
    attributes[i].name = names[i];
}

// get subset of attributes based on input
vector <Attribute> Table::attribute_subset(vector <string> names)
{
  vector <Attribute> ret;
  vector <string> attr_names = get_attribute_names();

  for (int i = 0; i < attr_names.size(); ++i) {
    for (int j = 0; j < names.size(); ++j) {
      if (attr_names[i] == names[j])
        ret.push_back(attributes[i]);
    }
  }

  return ret;
}

vector <vector <string> > Table::item_subset(vector <string> names)
{
  vector <string> attr_names = get_attribute_names();
  vector <vector <string> > ret;
  vector <string> entry;

  for (int i = 0; i < items.size(); ++i) {
    for (int j = 0; j < attr_names.size(); ++j) {
      for (int k = 0; k < names.size(); ++k) {

        if (attr_names[j].compare(names[k])==0) {
          entry.push_back(items[i][j]);
        }
      }
    }

    ret.push_back(entry);
    entry.clear();
  }

  return ret;
}

// gets the contents of the table
vector <vector <string> > Table::get_items()
{
  return items;
}

// add item entry to end of table
bool Table::insert_item(vector <string> entry)
{
  // insert if valid, otherwise return false
  if(check_types(entry)){ // && check_keys(entry)) {
    items.push_back(entry);
    return true;
  }
  if(!check_types(entry)) cout << "check types failed.\n";
  //if(!check_keys(entry)) cout << "check keys failed.\n";
  return false;
}

// updates item at index with the contents of entry
bool Table::update_item(vector <string> entry, int index)
{
  // make sure entry is proper length
  if(attributes.size() != entry.size())
    return false;

  vector <string> updated = items.at(index);

  cout << entry.size() << endl;
  for (int i = 0; i < entry.size(); ++i) {
    if(entry[i].compare("")!=0){
      updated[i] = entry[i];
    }
  }

  // make sure updated row is valid
  if(check_types(updated)){ // && check_keys(updated)) {
    for(int i = 0; i < updated.size();++i)
      items[index][i] = updated[i];

    return true;
  }

  return false;
}

// remove item at index; auto-updates all other item positions
bool Table::delete_item(int index)
{
  items.erase(items.begin()+index);
}

// makes sure the typing for entry is valid with the table's
bool Table::check_types(vector <string> entry)
{
  // check that entry length is valid
  if (entry.size() != attributes.size()) {
    cout << "Error: wrong entry size. Cannot insert\n";
    return false;
  }

  for (int i = 0; i < entry.size(); ++i) {

    //check if entry[i] is a number
    if (attributes[i].type == INTEGER) {
      for (int j = 0; j < entry[i].length();++j) {
        if (!isdigit(entry[i][j])) { // entry[i][j] is a char in entry[i]
          cout << "Error: Invalid entry type. Cannot insert.\n";
          return false;
        }
      }
    }

    //else, check if varchar
    else if (attributes[i].type == VARCHAR) {
      for (int j = 0; j < entry[i].length(); ++j) {

        //check that char length not exceeded
        if (entry[i].length() > attributes[i].size) {
          cout << "Error: VARCHAR entry is too long. Cannot insert.\n";
          return false;
        }

      }
    }

  }

  return true;
}

// makes sure primary keys for entry line up with table's
bool Table::check_keys(vector <string> entry)
{
  if (entry.size() != attributes.size())
    return false;

  bool ret = true;

  for (int i = 0; i < items.size();++i) {
    bool valid = false;
    for (int j = 0; j < items[i].size(); ++j) {
      if (items[i][j].compare(entry[j])==0 && attributes[i].primary)
        valid = true;
    }

    ret &= valid;
  }

  return ret;
}
