#include "engine.h"
#include "relation.h"

int engine::createTable(std::string TableName, std::vector<Attributes> attributes, std::vector<Attributes> primarykey) {
	
	Relation table(TableName, attributes, primarykey);
	openTable(table);
}

int rename(std::string TableName, Attribute attribute, std::string newname) {
	/*
		Not sure on where TableName is being accessed.
		attribute.set_title(newname);
	*/

}
