#include "engine.h"
#include "relation.h"

int engine::find_table(std::string TableName) {
	int i = 0;
	while(i < tables_.size()) {
		if( TableName.compare( tables_.at(i).get_title() ) )
			return i;
		i++;
	}
	return -1;
}

Relation get_table(std::string TableName) {
	int i = find_table(TableName);
	if(i != -1)
		return tables_.at(i);
	else {
		//Don't know how we want to handle not finding table 
	}
}

std::vector<Relation> get_all_tables() {
	return tables_;
}

int engine::createTable(std::string TableName, std::vector<Attributes> attributes, std::vector<Attributes> primarykeys) {
	
	Relation table(TableName, attributes, primarykeys);
	tables_.push_back(table);
	if(find_table(TableName) != -1)
		return 0;
	return -1;
}

int rename_table(std::string TableName, std::string newname) {
	int i = find_table(TableName);
	if(i != -1) {
		tables_.at(i).set_title(newname);
		return 0;
	}
		
	return i;
}

int engine::rename_attribute(std::string TableName, Attribute attribute, std::string newname) {
		int i = find_table(TableName);
		if(i != -1) {
			int num_att = tables_.at(i).get_attributes().size();
			int w = 0;
			while(w < num_att) {
				if( attribute.get_title().compare( tables_.at(i).get_attribute(w).get_title() ) ) {
					tables_.at(i).get_attribute(w).set_title(newname);
					return 0;
				}
				w++;
			}
		}
		
		return -1;
}

private:
	std::vector<Relation> tables_;