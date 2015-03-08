#include "command.h"

#include <boost/algorithm/string.hpp>
#include <boost/fusion/adapted.hpp>

#include "../engine.h"

#include "../utility.h"

std::ostream& operator<<(std::ostream& os, Command const& ss) {
  os << ss.command << "||";
  os << ss.relation_name;
  os << "( ";
  for (std::string entry : ss.typed_attribute_list) {
    os << entry << " ";
  }
  os << ") ";
  os << "( ";
  for (std::string entry : ss.attribute_list) {
    os << entry << " ";
  }
  os << ") ";
  os << "( ";
  for (std::string entry : ss.attribute_value_list) {
    os << entry << " ";
  }
  os << ") ";
  os << "( ";
  os << ss.condition;
  os << ") ";
  os << "( ";
  for (std::string entry : ss.literal_list) {
    os << entry << " ";
  }
  os << ") ";
  os << ss.expression;
  return os;
}

void execute_command(Engine& db, std::string command, std::string relation_name,
                     std::vector<std::string> condition, Relation view,
                     std::vector<std::string> typed_attribute_list,
                     std::vector<std::string> attribute_list,
                     std::vector<std::string> attribute_value_list,
                     std::vector<std::string> literal_list) {
  std::string errmsg = "Grammar: Execute Command: " + command + " ";
  errmsg += relation_name + " ";
  for (std::string cond : condition) {
    errmsg += cond + " ";
  }
  errmsg += "|";
  errmsg += view.title() + "|";
  for (std::string arg : typed_attribute_list) {
    errmsg += arg + " ";
  }
  errmsg += "|";
  for (std::string arg : attribute_list) {
    errmsg += arg + " ";
  }
  errmsg += "|";
  for (std::string arg : attribute_value_list) {
    errmsg += arg + " ";
  }
  errmsg += "|";
  for (std::string arg : literal_list) {
    errmsg += arg + " ";
  }
  errmsg += "|";
  errlog(errmsg);

  if (command == "OPEN") {
    db.openTable(relation_name);
  } else if (command == "CLOSE") {
    db.closeTable(relation_name);
  } else if (command == "WRITE") {
    db.writeTable(relation_name);
  } else if (command == "EXIT") {
    db.exitEngine();
  } else if (command == "SHOW") {
    db.showTable(view);
  } else if (command == "CREATE TABLE") {
    db.createNewTable(relation_name, typed_attribute_list, attribute_list);
  } else if (command == "UPDATE") {
    db.updateTable(relation_name, attribute_value_list, condition);
  } else if (command == "INSERT INTO") {
    if (literal_list.size() > 0) {
      std::string errstr = "Execute Command: Literal list size: " +
                           std::to_string(literal_list.size());
      errlog(errstr);
      db.insertTuple(relation_name, literal_list);
    } else {
      std::string errstr = "Execute Command: View: " + view.title();
      errlog(errstr);
      db.insertTuple(relation_name, view);
    }
  } else if (command == "DELETE FROM") {
    db.deleteFrom(relation_name, condition);
  }
}
