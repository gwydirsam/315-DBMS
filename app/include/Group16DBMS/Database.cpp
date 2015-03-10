#include "Database.h"

Database::Database(){}

// Adds a table to the vector of currently accessible tables in memory.
bool Database::add(Table* table)
{
  //check if any relations already have table's title
  if (get_table(table->get_name()) != NULL)
    return false;
  else {
    Database::dbms.push_back(*table);
    return true;
  }
}

// creates a table in memory from a file. The file contains a create and insert
// commands that are executed here, which results in an actual table being held
// in memory.
bool Database::open(string name)
{
  bool ret = true;
  // open file
  ifstream file(name.c_str());
  Parser p;
  string str;
  getline(file, str);
  while (file.good() && ret) {
    p.lex(str);
    ret &= p.program();
    getline(file, str);
  }

  if (ret) dbms.push_back(p.database->dbms[0]);
  return ret;
}

// removes a table from memory. NOTE: This does not save the table to a file;
// that must be done with the write command.
bool Database::close(string name)
{
  int index = -1; //where we'll remove
  for (int i = 0; i < dbms.size(); ++i) {
    if (name.compare(dbms[i].get_name())==0) {
      index = i;
      break;
    }
  }

  if (index >= 0) {
    dbms.erase(dbms.begin()+1);
    return true;
  }
  cout << "The requested relation is not open.\n";
  return false;
}

// Saves the current state of a table in memory to a file. This entails
// creating a CREATE TABLE command as well as INSERT INTO commands as needed.
bool Database::write(string name)
{
  if (get_table(name) == NULL) {
    cout << "Table " << name << " was not found.\n";
    return false;
  }

  Table t;
  for (int i = 0; i < dbms.size(); ++i) {
    if (name.compare(dbms[i].get_name())==0)
      t = dbms.at(i);
  }

  ofstream write_file((t.get_name()).c_str());

  if (write_file.is_open()) {

    // will hold primary keys & attributes to write
    string primary = "";
    string attr = "";

    vector <Attribute> attributes = t.get_attributes();
    for (int i = 0; i < attributes.size(); ++i) {
      Attribute a = t.get_attributes()[i];

      // check type correctness
      stringstream temp;
      if (a.type == INTEGER) temp << "INTEGER";
      if (a.type == VARCHAR) temp <<  "VARCHAR(" << a.size << ")";

      // insert comma if appropriate
      if (i == 0) {
        attr += a.name + " " + temp.str();
        if (a.primary)
          primary += a.name;
      }
      else {
        attr += ", " + a.name + " " + temp.str();
        if (a.primary)
          primary += ", " + a.name;
      }
    }

    // insert the CREATE TABLE command:
    string temp_file = t.get_name().substr(0, t.get_name().length()-3);
    write_file << "CREATE TABLE " << temp_file << " (" << attr
      << ") PRIMARY KEY (" << primary << ");\n";

    string entry = "";
    vector <string> entries;

    //insert any INSERT INTO commands necessary:
    for (int e = 0; e < t.get_items().size(); ++e) {
      entries = t.get_items()[e];

      for (int i = 0; i < entries.size(); ++i) {
        string data = entries[i];

        //append quotations if necessary
        if (t.get_attributes()[i].type==VARCHAR)
          data="\"" + data + "\"";
        if (i == 0)
          entry += entries[i];
        else
          entry = entry + ", " + entries[i];
      }

      write_file << "INSERT INTO " << temp_file << " VALUES FROM ("
        << entry << ");\n";

      entry = "";
    }

  }

  write_file.close();
  return true;

}

// prints out the relation specified by name
bool Database::show(string name)
{
  Table* t = get_table(name);

  if (t != NULL) {

    // print attribute names
    cout << t->get_name() << ":\n(";
    vector <string> attr = t->get_attribute_names();
    for(int i = 0; i < attr.size();++i) {
      cout << attr[i];
      if(i < attr.size()-1) cout << ", ";
      else cout << ")\n";
    }

    // print entries
    for (int i = 0; i < t->get_items().size(); ++i) {
      cout << "(";
      vector <string> entry = t->get_items()[i];

      for (int j = 0; j < entry.size(); ++j) {
        cout << entry[j];
        if (j < entry.size()-1) cout << ", ";
        else cout << ")\n";
      }
    }

    return true;
  }

  else {
    cout << "The requested file " << name << " is not a relation.\n";
    return false;
  }
}

// creates an  empty table
bool Database::create_table(string name, vector <Attribute> attr)
{
  // check that this table name doesn't exist already
  if (get_table(name) != NULL) {
    cout << "Error: Table with same name already exists.\n";
    return false;
  }

  dbms.push_back(Table(name, attr));

  return true;
}

// Exits the program.
void Database::exit_db()
{
  cout << "Exiting program.\n";
  exit(0);
}

// updates an entry or entries based on the vector of pairs and the conditions
bool Database::update(string name, vector<pair<string,string> > pairs,
    Conditions cond)
{
  Table *t = get_table(name);
  if (t == NULL){
    cout << "Table " << name << " not found\n";
    return false;
  }

  vector <string> attr = t->get_attribute_names();
  vector <string> updates; //all of the SETs
  bool modified = true;

  // determine what to update:
  for (int i = 0; i < attr.size(); ++i) {
    for (int j = 0; j < pairs.size(); ++j) {
      if (attr[i].compare(pairs[j].first)==0)
        updates.push_back(pairs[j].second);
      else
        updates.push_back(""); // don't update anything for this column
    }
  }

  // update appropriately:
  for (int i = 0; i < t->get_items().size(); ++i) {
    if (cond.evaluate(t, i))
      modified &= t->update_item(updates, i);
  }

  return modified;
}

// insert from another relation (INSERT INTO .. VALUES FROM RELATION ..)
bool Database::insert_into(string name, Table* from)
{
  Table* t = get_table(name);
  if (t == NULL) {
    cout << "Table " << name << " not found.\n";
    return false;
  }

  bool inserted = true;
  for (int i = 0; i < from->get_items().size(); ++i) {
    inserted &= t->insert_item(from->get_items()[i]);
  }

  return inserted;
}

// insert values into relation (INSERT INTO .. VALUES FROM ..)
bool Database::insert_into(string name, vector<string> values)
{
  Table* t = get_table(name);
  if (t == NULL) {
    cout << "Table " << name << " not found.\n";
    return false;
  }

  return t->insert_item(values);
}

// Deletes an entry or entries from a table.
bool Database::delete_from(string name, Conditions cond)
{
  name += ".db";

  Table* t = get_table(name);
  if(t == NULL) {
    cout << "Table " << name << " not found.\n";
    return false;
  }

  vector<int> to_delete;
  bool deleted = false;
  for (int i = 0; i < t->get_items().size(); ++i) {
    if (cond.evaluate(t, i)) {
      to_delete.push_back(i);
    }
  }
  for (int i = 0; i < to_delete.size(); ++i) {
    deleted |= t->delete_item(to_delete[i]-i);
  }

  return deleted;
}

// Selects items from a relation based on the specified conditions
Table* Database::select(Table* table, Conditions cond, string name)
{
  vector <Attribute> selectors = table->get_attributes();
  vector <vector <string> > items = table->get_items();
  Table* result = new Table(name, selectors);

  for (int i = 0; i < items.size();++i) {
    if (cond.evaluate(table,i))
      result->insert_item(items[i]);
  }

  return result;
}

// Computes a subset of a relation.
Table* Database::project(Table* table, vector<string> attr, string name)
{
  vector <Attribute> attr_projectors = table->attribute_subset(attr);
  vector <vector <string> > item_projectors = table->item_subset(attr);

  Table* proj = new Table(name, attr_projectors);

  for (int i = 0; i  < item_projectors.size(); ++i) {
    proj->insert_item(item_projectors[i]);
  }

  return proj;
}

// Renames a relation.
Table* Database::rename(Table* table, vector<string> updates, string name)
{
  vector <Attribute> renamed_attr = table->get_attributes();
  vector <vector <string> > renamed_items = table->get_items();
  Table* renamed = new Table(name, renamed_attr);

  for (int i = 0; i < renamed_items.size(); ++i)
    renamed->insert_item(renamed_items[i]);

  renamed->set_attribute_names(updates);

  return renamed;
}

// atomic-expr + atomic-expr; Computes the union between 2 relations.
Table* Database::set_union(Table* table1, Table* table2, string name)
{
  bool b = union_possible(table1, table2);
  Table* ret;

  if (b) {
    ret = new Table(name, table1->get_attributes());

    cout << "union is possible\n";
    for (int i = 0; i < table1->get_items().size(); ++i) {
      ret->insert_item(table1->get_items()[i]);
    }

    for (int i = 0; i < table2->get_items().size();++i) {
      ret->insert_item(table2->get_items()[i]);
    }
  }

  return ret;

}

// checks that a union between 2 tables is possible
bool Database::union_possible(Table* table1, Table* table2)
{
  vector <Attribute> a1 = table1->get_attributes();
  vector <Attribute> a2 = table2->get_attributes();

  if (a1.size() != a2.size()) return false;

  for (int i = 0; i < a1.size(); ++i){
    if (a1[i].name.compare(a2[i].name) != 0) return false;
    if (a1[i].size != a2[i].size) return false;
    if (a1[i].primary != a2[i].primary) return false;
    if (a1[i].type != a2[i].type) return false;
  }

  return true;
}

// atomic-expr - atomic-expr; Computes the difference between 2 relations.
Table* Database::set_difference(Table* table1, Table* table2, string name)
{
  bool b = union_possible(table1,table2);
  Table* ret = NULL;

  if (b) {
    ret = new Table(name, table1->get_attributes());

    for (int i = 0; i < table1->get_items().size(); ++i) {
      vector<string> current_item = table1->get_items()[i];
      bool ok_to_add = false;

      for (int j = 0; j < current_item.size(); ++j) {
        bool dif = true;
        for(int k = 0; k < table2->get_items().size();++k)
          dif &= (current_item[j].compare(table2->get_items()[k][j]) !=0);

        ok_to_add |= dif;
      }

      if ((table2->get_items().size() ==0) || ok_to_add)
        ret->insert_item(current_item);
    }
  }

  return ret;
}

// atomic-expr * atomic-expr; Computes the Cartesian product of 2 relations.
Table* Database::cross_product(Table* table1, Table* table2, string name)
{
  vector <Attribute> a1 = table1->get_attributes();
  vector <Attribute> a2 = table2->get_attributes();
  a1.insert(a1.end(), a2.begin(), a2.end());

  Table* ret = new Table(name, a1);

  for (int i = 0; i < table1->get_items().size(); ++i) {

    for (int j = 0; j < table2->get_items().size(); ++j) {

      vector <string> result_row = table1->get_items()[i];
      vector <string> temp = table2->get_items()[j];
      result_row.insert(result_row.end(), temp.begin(), temp.end());

      ret->insert_item(result_row);
    }
  }

  return ret;
}

// returns a table if it exists, null otherwise
Table* Database::get_table(string name)
{
  Table* ret = NULL;
  for (int i = 0; i < dbms.size(); ++i) {
    if (dbms.at(i).get_name().compare(name)==0) {
      try {
        ret =  &dbms[i];
      } catch (exception &e) {
        cout << e.what() << endl;
      }

    }
  }

  return ret;
}
